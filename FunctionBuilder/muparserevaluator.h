#ifndef MUPARSEREVALUATOR_H
#define MUPARSEREVALUATOR_H

#include <map>
#include <set>
#include <string>


#pragma push_macro("_UNICODE")
#pragma push_macro("_T")
#undef _UNICODE
#undef _T
#include <muParser.h>
#pragma pop_macro("_T")
#pragma pop_macro("_UNICODE")

struct FunctionParameter
{
    double minimum = -10.0;
    double maximum = 10.0;
    double value = 1.0;
};

class MuParserEvaluator
{
public:
    MuParserEvaluator();
    MuParserEvaluator(const MuParserEvaluator&) = delete;
    MuParserEvaluator& operator=(const MuParserEvaluator&) = delete;

    bool setExpression(const std::string& expression);
    double evaluate(double xValue);
    bool setParameter(char name, const FunctionParameter& parameter);
    bool setParameterValue(char name, double value);
    std::map<char, FunctionParameter> getParameters() const;

    bool isValid() const { return valid; }
    const std::string& getError() const { return errorMessage; }

private:
    std::map<char, FunctionParameter> parameters;
    std::set<char> activeParameters;
    double x = 0.0;
    mu::Parser parser;
    bool valid = false;
    std::string errorMessage;
};

#endif
