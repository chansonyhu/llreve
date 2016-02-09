#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <vector>

namespace sexpr {

template <typename T> class SExpr {
  public:
    virtual void serialize(std::ostream &os, size_t indent) const = 0;
    virtual ~SExpr() = default;
    SExpr() = default;
    SExpr(const SExpr &sExpr) = default;
};

template <typename T> class Value : public SExpr<T> {
  public:
    explicit Value(T val) : val(std::move(val)) {}
    void serialize(std::ostream &os, size_t /*unused*/) const override {
        os << val;
    }
    T val;
};

template <typename T> class Apply : public SExpr<T> {
  public:
    Apply(T fun, std::vector<std::unique_ptr<const SExpr<T>>> args)
        : fun(std::move(fun)), args(std::move(args)) {}
    void serialize(std::ostream &os, size_t indent) const override {
        os << "(" << fun;
        std::vector<std::string> atomicOps = {
            "+", "-",   "*",        "<=",     "<",     ">",  ">=",
            "=", "not", "distinct", "select", "store", "ite", "div"};
        std::vector<std::string> forceIndentOps = {"assert", "and"};
        bool atomicOp = std::find(atomicOps.begin(), atomicOps.end(), fun) !=
                        atomicOps.end();
        bool simpleOp = args.size() <= 1 &&
                        std::find(forceIndentOps.begin(), forceIndentOps.end(),
                                  fun) == forceIndentOps.end();
        bool inv = fun.substr(0, 3) == "INV";
        if (atomicOp || simpleOp || inv) {
            for (auto &arg : args) {
                os << " ";
                arg->serialize(os, indent);
            }
        } else {
            for (auto &arg : args) {
                os << std::endl;
                os << std::string(indent + 3, ' ');
                arg->serialize(os, indent + 3);
            }
        }
        os << ")";
    }
    T fun;
    std::vector<std::unique_ptr<const SExpr<T>>> args;
};

template <typename T> class List : public SExpr<T> {
  public:
    explicit List(std::vector<std::unique_ptr<const SExpr<T>>> elements)
        : elements(std::move(elements)) {}
    void serialize(std::ostream &os, size_t indent) const override {
        os << "(";
        auto it = elements.begin();
        auto e = elements.end();
        if (it != e) {
            (*it)->serialize(os, indent + 1);
            ++it;
            for (; it != e; ++it) {
                os << std::endl;
                os << std::string(indent + 1, ' ');
                (*it)->serialize(os, indent + 1);
            }
        }
        os << ")";
    }
    T fun;
    std::vector<std::unique_ptr<const SExpr<T>>> elements;
};

template <typename T> class Comment : public SExpr<T> {
  public:
    explicit Comment(std::string val) : val(std::move(val)) {}
    void serialize(std::ostream &os, size_t /*unused*/) const override {
        os << "; " << val;
    }
    std::string val;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const SExpr<T> &val) {
    val.serialize(os, 0);
    return os;
}

} // namespace sexpr