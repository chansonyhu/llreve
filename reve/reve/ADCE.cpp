//===- ADCE.cpp - Code to perform dead code elimination -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Aggressive Dead Code Elimination pass.  This pass
// optimistically assumes that all instructions are dead until proven otherwise,
// allowing it to eliminate dead computations that other DCE passes do not
// catch, particularly involving loop computations.
//
//===----------------------------------------------------------------------===//

#include "ADCE.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Transforms/Scalar.h"
using namespace llvm;

#define DEBUG_TYPE "adce"

STATISTIC(NumRemoved, "Number of instructions removed");

static bool aggressiveDCE(Function& F) {
  SmallPtrSet<Instruction*, 32> Alive;
  SmallVector<Instruction*, 128> Worklist;

  // Collect the set of "root" instructions that are known live.
  for (auto &BB : F) {
      for (Instruction &I : BB) {
          if (isa<TerminatorInst>(I) || isa<DbgInfoIntrinsic>(I) ||
              I.mayHaveSideEffects()) {
              Alive.insert(&I);
              Worklist.push_back(&I);
          }
      }
  }

  // Propagate liveness backwards to operands.
  while (!Worklist.empty()) {
    Instruction *Curr = Worklist.pop_back_val();
    for (Use &OI : Curr->operands()) {
      if (Instruction *Inst = dyn_cast<Instruction>(OI))
        if (Alive.insert(Inst).second)
          Worklist.push_back(Inst);
    }
  }

  // The inverse of the live set is the dead set.  These are those instructions
  // which have no side effects and do not influence the control flow or return
  // value of the function, and may therefore be deleted safely.
  // NOTE: We reuse the Worklist vector here for memory efficiency.
  for (auto &BB : F) {
      for (Instruction &I : BB) {
          if (!Alive.count(&I)) {
              Worklist.push_back(&I);
              I.dropAllReferences();
          }
      }
  }

  for (Instruction *&I : Worklist) {
    ++NumRemoved;
    I->eraseFromParent();
  }

  return !Worklist.empty();
}

PreservedAnalyses ADCEPass::run(Function &F) {
  if (aggressiveDCE(F))
    return PreservedAnalyses::none();
  return PreservedAnalyses::all();
}