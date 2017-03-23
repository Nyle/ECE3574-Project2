#include "environmentprocedures.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"
#include "expression.hpp"
#include <sstream>
#include <cmath>
#include <tuple>

enum Arity {Nullary, Unary, Binary, Ternary, M_ary, Any};

// Throws an error if the number of elements in args doesn't line up with the
// arity
void arity(Arity a, Args args) {
    size_t nargs = args.size();
    if ((a == Nullary && nargs == 0) || (a == Unary && nargs == 1) ||
        (a == Binary && nargs == 2) || (a == Ternary && nargs == 3) ||
        (a == M_ary && nargs >= 1) || (a == Any)) {
        return;
    } 
    std::stringstream stream;
    stream << "Error: expected " << (
        a == Nullary ? "0 arguments " : a == Unary ? "1 argument  " :
        a == Binary ? "2 arguments " : a == Ternary ? "3 arguments " :
        a == M_ary ? ">= 1 arguments " : "undefined number of arguments "
        ) << "but got " << nargs; 
    throw InterpreterSemanticError(stream.str());
}

EnvFunc makeBinaryBoolFn(std::function<bool(bool,bool)> func) {
    return [func](Args args, Environment &env) {
        arity(M_ary, args);
        bool res = args[0].getbool(env);
        for(size_t i = 1; i < args.size(); i++) {
            res = func(res, args[i].getbool(env));
        }
        return Expression(res);
    };
}

EnvFunc makeCmpFn(std::function<bool(float,float)> func) {
    return [func](Args args, Environment &env) {
        arity(Binary, args);
        return Expression(func(args[0].getnumber(env),
                                     args[1].getnumber(env)));
    };
}

EnvFunc makePlusMulFn(std::function<float(float,float)> func) {
    return [func](Args args, Environment &env) {
        arity(M_ary, args);
        double res = args[0].getnumber(env);
        for(size_t i = 1; i < args.size(); i++) {
            res = func(res, args[i].getnumber(env));
        }
        return Expression(res);
    };
}

EnvFunc NotFn = [](Args args, Environment &env) {
    arity(Unary, args);
    return Expression(!args[0].getbool(env));
};

EnvFunc SubFn = [](Args args, Environment &env) {
    if (args.size() == 1) {// Instead this should be the negative operator
        return Expression(-1 * args[0].getnumber(env));
    }
    arity(Binary, args);
    return Expression(args[0].getnumber(env) -
                      args[1].getnumber(env));
};

EnvFunc DivFn = [](Args args, Environment &env) {
    arity(Binary, args);
    return Expression(args[0].getnumber(env) /
                      args[1].getnumber(env));
};
    
EnvFunc DefineFn = [](Args args, Environment &env) {
    arity(Binary, args);
    Expression res = args[1].eval(env);
    env.define(args[0].getsymbol(), res);
    return res;
};

EnvFunc BeginFn = [](Args args, Environment &env) {
    Expression result;
    for(auto const &arg: args) {
        result = arg.eval(env);
    }
    return result;
};

EnvFunc IfFn = [](Args args, Environment &env) {
    arity(Ternary, args);
    return args[0].getbool(env) ?
        args[1].eval(env) : args[2].eval(env);
};

EnvFunc DrawFn = [](Args args, Environment &env) {
    arity(M_ary, args);
    for (auto const &arg: args) {
        env.addToDraw(arg.getdrawable(env));
    }
    return Expression();
};

EnvFunc PointFn = [](Args args, Environment &env) {
    arity(Binary, args);
    return Expression(std::make_tuple(args[0].getnumber(env),
                                      args[1].getnumber(env)));
};

EnvFunc LineFn = [](Args args, Environment &env) {
    arity(Binary, args);
    return Expression(args[0].getpoint(env), args[1].getpoint(env));
};

EnvFunc ArcFn = [](Args args, Environment &env) {
    arity(Ternary, args);
    return Expression(args[0].getpoint(env), args[1].getpoint(env),
                      args[2].getnumber(env));
};

EnvFunc SinFn = [](Args args, Environment &env) {
    arity(Unary, args);
    return Expression(sin(args[0].getnumber(env)));
};

EnvFunc CosFn = [](Args args, Environment &env) {
    arity(Unary, args);
    return Expression(cos(args[0].getnumber(env)));
};

EnvFunc ArctanFn = [](Args args, Environment &env) {
    arity(Binary, args);
    return Expression(atan2(args[0].getnumber(env), args[1].getnumber(env)));
};
