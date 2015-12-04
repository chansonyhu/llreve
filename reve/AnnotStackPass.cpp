#include "AnnotStackPass.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"

#include <iostream>
#include <set>

llvm::PreservedAnalyses AnnotStackPass::run(llvm::Function &F,
                                            llvm::FunctionAnalysisManager *AM) {
    int StackIndex = -1;
    (void)AM;
    std::set<llvm::Value *> StackOps;
    for (auto &Block : F) {
        for (auto &Inst : Block) {
            if (auto AllocaInst = llvm::dyn_cast<llvm::AllocaInst>(&Inst)) {
                StackOps.insert(AllocaInst);
                StackIndex -= typeSize(AllocaInst->getAllocatedType());
                markStackInstruction(*AllocaInst, "reve.stack_pointer",
                                     StackIndex);
            } else if (auto GetElementPtr =
                           llvm::dyn_cast<llvm::GetElementPtrInst>(&Inst)) {
                if (StackOps.find(GetElementPtr->getPointerOperand()) !=
                    StackOps.end()) {
                    StackOps.insert(GetElementPtr);
                }
            } else if (auto CastInst = llvm::dyn_cast<llvm::CastInst>(&Inst)) {
                if (StackOps.find(CastInst->getOperand(0)) != StackOps.end()) {
                    StackOps.insert(CastInst);
                }
            } else if (auto LoadInst = llvm::dyn_cast<llvm::LoadInst>(&Inst)) {
                if (StackOps.find(LoadInst->getPointerOperand()) !=
                    StackOps.end()) {
                    StackOps.insert(LoadInst);
                }
            } else if (auto StoreInst =
                           llvm::dyn_cast<llvm::StoreInst>(&Inst)) {
                if (StackOps.find(StoreInst->getPointerOperand()) !=
                    StackOps.end()) {
                    StackOps.insert(StoreInst);
                }
            }
        }
    }
    for (auto StackOp : StackOps) {
        if (auto Inst = llvm::dyn_cast<llvm::Instruction>(StackOp)) {
            markStackInstruction(*Inst, "reve.stackop", 0);
        }
    }
    return llvm::PreservedAnalyses::none();
}

void markStackInstruction(llvm::Instruction &Inst, std::string MetadataName,
                          int Pointer) {
    llvm::LLVMContext &Ctxt = Inst.getContext();
    llvm::MDNode *N = llvm::MDNode::get(
        Ctxt,
        llvm::MDString::get(Ctxt, "(- " + std::to_string(-Pointer) + ")"));
    Inst.setMetadata(MetadataName, N);
}

int typeSize(llvm::Type *Ty) {
    if (auto IntTy = llvm::dyn_cast<llvm::IntegerType>(Ty)) {
        if (IntTy->getBitWidth() == 32 || IntTy->getBitWidth() == 64 ||
            IntTy->getBitWidth() == 8) {
            return 1;
        }
        llvm::errs() << "Unsupported integer bitwidth: " << IntTy->getBitWidth()
                     << "\n";
    }
    if (auto StructTy = llvm::dyn_cast<llvm::StructType>(Ty)) {
        int Size = 0;
        for (auto ElTy : StructTy->elements()) {
            Size += typeSize(ElTy);
        }
        return Size;
    }
    if (auto ArrayTy = llvm::dyn_cast<llvm::ArrayType>(Ty)) {
        return static_cast<int>(ArrayTy->getNumElements()) *
               typeSize(ArrayTy->getElementType());
    }
    if (llvm::isa<llvm::PointerType>(Ty)) {
        return 1;
    }
    llvm::errs() << "Couldn't calculate size of type\n";
    Ty->print(llvm::errs());
    llvm::errs() << "\n";
    return 0;
}
