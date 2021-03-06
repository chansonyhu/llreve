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

#include <functional>
#include <iostream>
#include <vector>

#include "Program.h"

// Monomorphic pair
// Monomorphic refers to the fact that both elements have the same type
template <typename T> struct MonoPair {
    T first;
    T second;

    MonoPair(const T &first, const T &second) : first(first), second(second) {}

    template <typename T1, typename = std::enable_if_t<
                               std::is_convertible<const T1 &, T>::value>>
    MonoPair(const MonoPair<T1> &p) : first(p.first), second(p.second) {}

    MonoPair(const MonoPair &p) = default;

    MonoPair &operator=(const MonoPair &p) = default;

    MonoPair(MonoPair &&p) = default;

    MonoPair &operator=(MonoPair &&p) = default;

    template <typename T1, class = typename std::enable_if<
                               std::is_convertible<T1, T>::value>::type>
    MonoPair(T1 &&first, T1 &&second)
        : first(std::forward<T1>(first)), second(std::forward<T1>(second)) {}

    template <typename T1>
    MonoPair(
        MonoPair<T1> &&p,
        typename std::enable_if<std::is_convertible<T1, T>::value>::type * = 0)
        : first(std::forward<T1>(p.first)), second(std::forward<T1>(p.second)) {
    }

    template <typename NewT>
    MonoPair<NewT> map(std::function<NewT(T)> f) const {
        return {f(first), f(second)};
    }

    void forEach(std::function<void(T)> f) const & {
        f(first);
        f(second);
    }
    void forEach(std::function<void(T)> f) && {
        f(std::forward<T>(first));
        f(std::forward<T>(second));
    }

    void indexedForEach(std::function<void(T, int)> f) const {
        f(first, 1);
        f(second, 2);
    }

    void indexedForEachProgram(std::function<void(T, Program)> f) const {
        f(first, Program::First);
        f(second, Program::Second);
    }
};

// This weird template magic is stolen from libc++
template <class _Tp> struct __make_pair_return_impl { typedef _Tp type; };
template <class _Tp>
struct __make_pair_return_impl<std::reference_wrapper<_Tp>> {
    typedef _Tp &type;
};
template <class _Tp> struct __make_pair_return {
    typedef
        typename __make_pair_return_impl<typename std::decay<_Tp>::type>::type
            type;
};

template <typename T>
MonoPair<typename __make_pair_return<T>::type> makeMonoPair(T &&first,
                                                            T &&second) {
    return MonoPair<typename __make_pair_return<T>::type>(
        std::forward<T>(first), std::forward<T>(second));
}

template <typename A, typename B, typename C>
MonoPair<C> zipWith(MonoPair<A> pairA, MonoPair<B> pairB,
                    std::function<C(A, B)> f) {
    return {f(pairA.first, pairB.first), f(pairA.second, pairB.second)};
}

template <typename A, typename B>
MonoPair<std::pair<A, B>> zip(MonoPair<A> pairA, MonoPair<B> pairB) {
    return zipWith<A, B, std::pair<A, B>>(
        pairA, pairB,
        [](A a, B b) -> std::pair<A, B> { return std::make_pair(a, b); });
}

template <typename A>
void appendTo(std::vector<A> &to, MonoPair<std::vector<A>> pair) {
    to.insert(to.end(), pair.first.begin(), pair.first.end());
    to.insert(to.end(), pair.second.begin(), pair.second.end());
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const MonoPair<T> &p) {
    os << "(";
    os << p.first;
    os << ", ";
    os << p.second;
    os << ")";
    return os;
}

template <typename T>
bool operator<(const MonoPair<T> &lhs, const MonoPair<T> &rhs) {
    if (lhs.first == rhs.first) {
        return lhs.second < rhs.second;
    }
    return lhs.first < rhs.first;
}

template <typename T>
bool operator==(const MonoPair<T> lhs, const MonoPair<T> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}
