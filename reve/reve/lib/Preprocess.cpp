/*
 * This file is part of
 *    llreve - Automatic regression verification for LLVM programs
 *
 * Copyright (C) 2016 Karlsruhe Institute of Technology
 *
 * The system is published under a BSD license.
 * See LICENSE (distributed with this file) for details.
 */

#include "Preprocess.h"

#include "CFGPrinter.h"
#include "Helper.h"
#include "InferMarks.h"
#include "InlinePass.h"
#include "InlinePass.h"
#include "InstCombine.h"
#include "MonoPair.h"
#include "PathAnalysis.h"
#include "RemoveMarkPass.h"
#include "RemoveMarkRefsPass.h"
#include "SplitEntryBlockPass.h"
#include "UniqueNamePass.h"
#include "Unroll.h"

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/ADCE.h"
#include "llvm/Transforms/Scalar/SimplifyCFG.h"
#include "llvm/Transforms/Utils/UnifyFunctionExitNodes.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::string;
using llvm::ErrorOr;

vector<MonoPair<PreprocessedFunction>>
preprocessFunctions(MonoPair<shared_ptr<llvm::Module>> modules,
                    PreprocessOpts opts) {
    vector<MonoPair<PreprocessedFunction>> processedFuns;
    auto funs = zipFunctions(*modules.first, *modules.second);
    for (auto funPair : funs.get()) {
        auto results1 = preprocessFunction(*funPair.first, "1", opts);
        auto results2 = preprocessFunction(*funPair.second, "2", opts);
        processedFuns.push_back(
            makeMonoPair(PreprocessedFunction(funPair.first, results1),
                         PreprocessedFunction(funPair.second, results2)));
    }
    return processedFuns;
}

ErrorOr<std::vector<MonoPair<llvm::Function *>>>
zipFunctions(llvm::Module &mod1, llvm::Module &mod2) {
    std::vector<MonoPair<llvm::Function *>> funs;
    int size1 = 0;
    int size2 = 0;
    for (auto &fun : mod1) {
        if (!fun.isDeclaration()) {
            ++size1;
        }
    }
    for (auto &fun : mod2) {
        if (!fun.isDeclaration()) {
            ++size2;
        }
    }
    if (size1 != size2) {
        logWarning("Number of functions is not equal\n");
    }
    if (SMTGenerationOpts::getInstance().DisableAutoCoupling) {
        for (const auto functionPair :
             SMTGenerationOpts::getInstance().CoupledFunctions) {
            llvm::Function *fun1 = mod1.getFunction(functionPair.first);
            if (fun1 == nullptr) {
                logError("Could not find function '" + functionPair.first +
                         "' in first module\n");
                exit(1);
            }
            llvm::Function *fun2 = mod2.getFunction(functionPair.second);
            if (fun2 == nullptr) {
                logError("Could not find function '" + functionPair.second +
                         "' in second module\n");
                exit(1);
            }
            if (fun1->isDeclaration() != fun2->isDeclaration()) {
                logError("Function '" + functionPair.first +
                         "' and function '" + functionPair.second +
                         "' need to be either both declarations or both "
                         "definitions\n");
                exit(1);
            }
            if (!fun1->isDeclaration()) {
                funs.push_back({fun1, fun2});
            }
        }
    } else {
        for (auto &Fun1 : mod1) {
            if (Fun1.isDeclaration()) {
                continue;
            }
            llvm::Function *fun2 = mod2.getFunction(Fun1.getName());
            if (!fun2) {
                logWarning("No corresponding function for " + Fun1.getName() +
                           "\n");
                continue;
            }
            llvm::Function *fun1 = &Fun1;
            funs.push_back(makeMonoPair(fun1, fun2));
        }
    }
    return ErrorOr<std::vector<MonoPair<llvm::Function *>>>(funs);
}

AnalysisResults preprocessFunction(llvm::Function &fun, string prefix,
                                   PreprocessOpts opts) {
    auto fpm =
        std::make_unique<llvm::legacy::FunctionPassManager>(fun.getParent());
    fpm->add(llvm::createUnifyFunctionExitNodesPass());

    fpm->add(new InlinePass());
    fpm->add(llvm::createPromoteMemoryToRegisterPass()); // mem2reg
    fpm->add(llvm::createLoopSimplifyPass());
    fpm->add(llvm::createCFGSimplificationPass());
    fpm->add(new SplitBlockPass());

    MarkAnalysis *markAnalysis = new MarkAnalysis();
    InferMarksAnalysis *inferMarkAnalysis = new InferMarksAnalysis();
    fpm->add(inferMarkAnalysis);
    fpm->add(markAnalysis);
    if (!opts.InferMarks) {
        fpm->add(new RemoveMarkRefsPass());
    }
    fpm->add(new InstCombinePass());
    fpm->add(llvm::createAggressiveDCEPass());
    fpm->add(llvm::createConstantPropagationPass());
    // Passes need to have a default ctor
    UniqueNamePass::Prefix = prefix;
    fpm->add(new UniqueNamePass()); // prefix register names
    if (opts.ShowMarkedCFG) {
        fpm->add(new CFGViewerPass()); // show marked cfg
    }
    if (!opts.InferMarks) {
        fpm->add(new RemoveMarkPass());
    }
    PathAnalysis *pathAnalysis = new PathAnalysis();
    pathAnalysis->InferMarks = opts.InferMarks;
    fpm->add(pathAnalysis);
    if (opts.ShowCFG) {
        fpm->add(new CFGViewerPass()); // show cfg
    }
    fpm->add(llvm::createVerifierPass());
    // FPM.addPass(llvm::PrintFunctionPass(errs())); // dump function
    fpm->doInitialization();
    fpm->run(fun);
    if (opts.InferMarks) {
        return AnalysisResults(inferMarkAnalysis->BlockMarkMap,
                               pathAnalysis->PathsMap);
    } else {
        return AnalysisResults(markAnalysis->BlockMarkMap,
                               pathAnalysis->PathsMap);
    }
}
