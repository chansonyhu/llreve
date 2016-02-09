#pragma once

#include "SMT.h"

#include <string>

#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include <unistd.h>

#define logError(Message) logError_(Message, __FILE__, __LINE__)
#define logWarning(Message) logWarning_(Message, __FILE__, __LINE__)
#define logErrorData(Message, El) logErrorData_(Message, El, __FILE__, __LINE__)
#define logWarningData(Message, El)                                            \
    logWarningData_(Message, El, __FILE__, __LINE__)

template <typename Str>
auto logError_(Str message, const char *file, int line) -> void {
    if (isatty(fileno(stdout))) {
        llvm::errs() << "\x1b[31;1mERROR\x1b[0m\x1b[1m (" << file << ":" << line
                     << "): " << message << "\x1b[0m";
    } else {
        llvm::errs() << "ERROR: " << message;
    }
}

template <typename Str>
auto logWarning_(Str message, const char *file, int line) -> void {
    if (isatty(fileno(stdout))) {
        llvm::errs() << "\x1b[33;1mWARNING\x1b[0m\x1b[1m (" << file << ":"
                     << line << "): " << message << "\x1b[0m";
    } else {
        llvm::errs() << "WARNING: " << message;
    }
}

template <typename Str, typename A>
auto logErrorData_(Str message, A &el, const char *file, int line) -> void {
    logError_(message, file, line);
    el.print(llvm::errs());
    llvm::errs() << "\n";
}

template <typename Str, typename A>
auto logWarningData_(Str message, A &el, const char *file, int line) -> void {
    logWarning_(message, file, line);
    el.print(llvm::errs());
    llvm::errs() << "\n";
}

auto instrNameOrVal(const llvm::Value *val, const llvm::Type *ty)
    -> smt::SMTRef;
auto typeSize(llvm::Type *ty) -> int;
template <typename T> smt::SMTRef resolveGEP(T &gep) {
    std::vector<smt::SMTRef> args;
    args.push_back(instrNameOrVal(gep.getPointerOperand(),
                                  gep.getPointerOperand()->getType()));
    const auto type = gep.getSourceElementType();
    std::vector<llvm::Value *> indices;
    for (auto ix = gep.idx_begin(), e = gep.idx_end(); ix != e; ++ix) {
        indices.push_back(*ix);
        const auto size = typeSize(llvm::GetElementPtrInst::getIndexedType(
            type, llvm::ArrayRef<llvm::Value *>(indices)));
        if (size == 1) {
            args.push_back(instrNameOrVal(*ix, (*ix)->getType()));
        } else {
            args.push_back(
                smt::makeBinOp("*", smt::name(std::to_string(size)),
                               instrNameOrVal(*ix, (*ix)->getType())));
        }
    }
    return std::make_shared<smt::Op>("+", args);
}

template <typename Key, typename Val>
auto unionWith(std::map<Key, Val> mapA, std::map<Key, Val> mapB,
               std::function<Val(Val, Val)> combine) -> std::map<Key, Val> {
    for (auto pair : mapB) {
        if (mapA.find(pair.first) == mapA.end()) {
            mapA.insert(pair);
        } else {
            mapA.at(pair.first) = combine(mapA.at(pair.first), pair.second);
        }
    }
    return mapA;
}

template <typename KeyA, typename KeyB, typename Val>
auto transpose(std::map<KeyA, std::map<KeyB, Val>> map)
    -> std::map<KeyB, std::map<KeyA, Val>> {
    std::map<KeyB, std::map<KeyA, Val>> mapResult;
    for (auto it : map) {
        for (auto innerIt : it.second) {
            mapResult[innerIt.first][it.first] = innerIt.second;
        }
    }
    return mapResult;
}

template <typename T>
auto mergePathFuns(std::map<int, std::map<int, std::vector<T>>> a,
                   std::map<int, std::map<int, std::vector<T>>> b)
    -> std::map<int, std::map<int, std::vector<T>>> {
    auto merge = [](
        std::map<int, std::vector<T>> mapA,
        std::map<int, std::vector<T>> mapB) -> std::map<int, std::vector<T>> {
        return unionWith<int, std::vector<T>>(
            mapA, mapB, [](std::vector<T> a, std::vector<T> b) {
                a.insert(a.end(), b.begin(), b.end());
                return a;
            });
    };
    return unionWith<int, std::map<int, std::vector<T>>>(a, b, merge);
}

auto filterVars(int program, std::vector<std::string> vars)
    -> std::vector<std::string>;

auto argSort(std::string arg) -> std::string;
