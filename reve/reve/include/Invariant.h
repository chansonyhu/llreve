/*
 * This file is part of
 *    llreve - Automatic regression verification for LLVM programs
 *
 * Copyright (C) 2016 Karlsruhe Institute of Technology
 *
 * The system is published under a BSD license.
 * See LICENSE (distributed with this file) for details.
 */

#pragma once

#include "FreeVariables.h"
#include "Memory.h"
#include "MonoPair.h"
#include "Opts.h"
#include "PathAnalysis.h"
#include "Program.h"
#include "SMT.h"

enum class InvariantAttr { MAIN, PRE, NONE };

auto invariant(int StartIndex, int EndIndex,
               std::vector<smt::SortedVar> InputArgs,
               std::vector<smt::SortedVar> EndArgs, ProgramSelection SMTFor,
               std::string FunName, FreeVarsMap freeVarsMap) -> smt::SMTRef;
auto mainInvariant(int EndIndex, std::vector<smt::SortedVar> FreeVars,
                   std::string FunName) -> smt::SMTRef;
auto invariantDeclaration(int BlockIndex, std::vector<smt::SortedVar> FreeVars,
                          ProgramSelection For, std::string FunName,
                          const llvm::Type *resultType)
    -> MonoPair<smt::SMTRef>;
auto mainInvariantDeclaration(int BlockIndex,
                              std::vector<smt::SortedVar> FreeVars,
                              ProgramSelection For, std::string FunName)
    -> smt::SharedSMTRef;
auto invariantName(int Index, ProgramSelection For, std::string FunName,
                   InvariantAttr attr = InvariantAttr::NONE,
                   uint32_t VarArgs = 0) -> std::string;

auto invariantArgs(std::vector<smt::SortedVar> freeVars, ProgramSelection prog,
                   InvariantAttr attr) -> size_t;
