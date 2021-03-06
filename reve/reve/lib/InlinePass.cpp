/*
 * This file is part of
 *    llreve - Automatic regression verification for LLVM programs
 *
 * Copyright (C) 2016 Karlsruhe Institute of Technology
 *
 * The system is published under a BSD license.
 * See LICENSE (distributed with this file) for details.
 */

#include "InlinePass.h"
#include "Helper.h"
#include "llvm/CodeGen/IntrinsicLowering.h"
#include "llvm/IR/Constants.h"
#include "llvm/Transforms/Utils/Cloning.h"

llvm::PreservedAnalyses InlinePass::run(llvm::Function &fun,
                                        llvm::FunctionAnalysisManager &fam) {
    std::vector<llvm::Instruction *> toDelete;
    std::vector<llvm::CallInst *> toBeInlined;
    for (auto &bb : fun) {
        for (auto &instr : bb) {
            if (auto inlineCall = llvm::dyn_cast<llvm::CallInst>(&instr)) {
                auto fun = inlineCall->getCalledFunction();
                // It is possible that we do not have a representation of the
                // function,
                // (in case of indirect function invocation) so we need to check
                // the return value:
                if (fun) {
                    if (fun->getName() == "__inlineCall") {
                        if (auto callInst = llvm::dyn_cast<llvm::CallInst>(
                                inlineCall->getOperand(0))) {
                            for (auto user : inlineCall->users()) {
                                user->replaceUsesOfWith(inlineCall, callInst);
                            }
                            toDelete.push_back(inlineCall);
                            toBeInlined.push_back(callInst);
                        }
                    }
                    if (fun->hasFnAttribute(llvm::Attribute::AlwaysInline)) {
                        toBeInlined.push_back(inlineCall);
                    }
                }
            }
        }
    }

    for (auto instr : toDelete) {
        instr->eraseFromParent();
    }
    for (auto instr : toBeInlined) {
        llvm::InlineFunctionInfo InlineInfo;
        llvm::InlineFunction(instr, InlineInfo);
    }
    return llvm::PreservedAnalyses::none();
}
