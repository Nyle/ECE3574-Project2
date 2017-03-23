#ifndef ENVIRONMENTPROCDURES_HPP
#define ENVIRONMENTPROCDURES_HPP

#include <functional>
#include <vector>
#include "expression.hpp"

class Environment;

// Functions to be stored in the environment
typedef std::function<Expression(Args args, Environment &env)> EnvFunc;


extern EnvFunc NotFn, SubFn, DivFn, DefineFn, BeginFn, IfFn, DrawFn, PointFn,
    LineFn, ArcFn, SinFn, CosFn, ArctanFn;

EnvFunc makeBinaryBoolFn(std::function<bool(bool,bool)> func);
EnvFunc makeCmpFn(std::function<bool(float,float)> func);
EnvFunc makePlusMulFn(std::function<float(float,float)> func);

#endif // ENVIRONMENTPROCDURES_HPP
