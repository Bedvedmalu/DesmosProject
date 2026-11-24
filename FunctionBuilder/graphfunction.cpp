
#include "graphfunction.h"

#include <utility>

GraphFunction::GraphFunction(
    int new_id,
    QString new_expression,
    QColor new_color,
    bool new_visible)
    : id(new_id),
    expression(new_expression),
    color(new_color),
    visible(new_visible),
    evaluator(std::make_unique<MuParserEvaluator>())
{
    evaluator->setExpression(expression.toStdString());
}

GraphFunction::GraphFunction(const GraphFunction& other)
    : GraphFunction(other.id,
                    other.expression,
                    other.color,
                    other.visible)
{
    for (const auto& [name, value] : other.getParameters())
        evaluator->setParameter(name, value);
}


GraphFunction& GraphFunction::operator=(const GraphFunction& other) {
    if (this == &other)
        return *this;

    GraphFunction copy(other);

    id = copy.id;
    expression = std::move(copy.expression);
    color = copy.color;
    visible = copy.visible;
    evaluator = std::move(copy.evaluator);

    return *this;
}

int GraphFunction::getId() const {
    return id;
}

bool GraphFunction::setExpression(QString expr) {
    expression = expr;

    return evaluator->setExpression(
        expression.toStdString()
        );
}

const QString& GraphFunction::getExpression() const {
    return expression;
}

void GraphFunction::setColor(QColor new_color) {
    color = new_color;
}

QColor GraphFunction::getColor() const {
    return color;
}

void GraphFunction::setVisibility(bool visibility) {
    visible = visibility;
}

bool GraphFunction::isVisible() const {
    return visible;
}

bool GraphFunction::setParameter(char name, const FunctionParameter& value) {
    return evaluator->setParameter(name, value);
}

bool GraphFunction::setParameterValue(char name, double value) {
    return evaluator->setParameterValue(name, value);
}

std::map<char, FunctionParameter> GraphFunction::getParameters() const {
    return evaluator->getParameters();
}

double GraphFunction::evaluate(double x) {
    return evaluator->evaluate(x);
}

bool GraphFunction::isValid() const {
    return evaluator->isValid();
}

QString GraphFunction::getError() const {
    return QString::fromStdString(
        evaluator->getError()
        );
}
