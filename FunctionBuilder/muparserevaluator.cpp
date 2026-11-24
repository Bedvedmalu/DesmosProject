#include "muparserevaluator.h"

#include <cmath>
#include <limits>
#include <utility>

MuParserEvaluator::MuParserEvaluator()
{
    parser.DefineVar("x", &x);
    parser.DefineConst("pi", std::acos(-1.0));
}

bool MuParserEvaluator::setExpression(const std::string& expression)
{
    valid = false;
    activeParameters.clear();
    errorMessage.clear();

    if (expression.find_first_not_of(" \t\r\n") == std::string::npos)
        return false;

    for (auto i = expression.find('='); i != std::string::npos; i = expression.find('=', i + 1)) {
        if ((i == 0 || std::string("=<>!").find(expression[i - 1]) == std::string::npos)
            && (i + 1 == expression.size() || expression[i + 1] != '=')) {
            errorMessage = "Введите выражение для y без присваивания.";
            return false;
        }
    }

    try {
        parser.SetExpr(expression);
        const auto variables = parser.GetUsedVar();
        std::set<char> names;
        for (const auto& entry : variables) {
            const auto& name = entry.first;
            if (name == "x")
                continue;
            if (name.size() != 1 || !((name[0] >= 'a' && name[0] <= 'z')
                                      || (name[0] >= 'A' && name[0] <= 'Z'))) {
                errorMessage = "Имя параметра должно состоять из одной латинской буквы.";
                return false;
            }
            const char key = name[0];
            names.insert(key);
            auto [it, inserted] = parameters.try_emplace(key);
            if (inserted)
                parser.DefineVar(name, &it->second.value);
        }

        parser.Eval();
        if (parser.GetNumResults() != 1) {
            errorMessage = "В карточке должно быть одно выражение.";
            return false;
        }
        activeParameters = std::move(names);
        valid = true;
    } catch (const mu::Parser::exception_type& error) {
        errorMessage = error.GetMsg();
    }
    return valid;
}

double MuParserEvaluator::evaluate(double xValue)
{
    if (valid) {
        x = xValue;
        try {
            return parser.Eval();
        } catch (const mu::Parser::exception_type&) {
        }
    }
    return std::numeric_limits<double>::quiet_NaN();
}

bool MuParserEvaluator::setParameter(char name, const FunctionParameter& parameter)
{
    if (!activeParameters.count(name) || !std::isfinite(parameter.minimum)
        || !std::isfinite(parameter.maximum) || !std::isfinite(parameter.value)
        || parameter.minimum >= parameter.maximum
        || !std::isfinite(parameter.maximum - parameter.minimum)
        || parameter.value < parameter.minimum || parameter.value > parameter.maximum)
        return false;
    parameters.at(name) = parameter;
    return true;
}

bool MuParserEvaluator::setParameterValue(char name, double value)
{
    if (!activeParameters.count(name))
        return false;
    auto parameter = parameters.at(name);
    parameter.value = value;
    return setParameter(name, parameter);
}

std::map<char, FunctionParameter> MuParserEvaluator::getParameters() const
{
    std::map<char, FunctionParameter> result;
    for (char name : activeParameters)
        result.emplace(name, parameters.at(name));
    return result;
}
