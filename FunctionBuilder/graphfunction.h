
#ifndef GRAPHFUNCTION_H
#define GRAPHFUNCTION_H

#include <QString>
#include <QColor>

#include <memory>
#include <map>

#include "muparserevaluator.h"

class GraphFunction
{
public:
    GraphFunction(int new_id, QString new_expression, QColor new_color, bool new_visible);

    GraphFunction(const GraphFunction& other);
    GraphFunction& operator=(const GraphFunction& other);

    GraphFunction(GraphFunction&& other) noexcept = default;
    GraphFunction& operator=(GraphFunction&& other) noexcept = default;

    int getId() const;

    bool setExpression(QString expr);
    const QString& getExpression() const;

    void setColor(QColor new_color);
    QColor getColor() const;

    void setVisibility(bool visibility);
    bool isVisible() const;

    bool setParameter(char name, const FunctionParameter& value);
    bool setParameterValue(char name, double value);
    std::map<char, FunctionParameter> getParameters() const;

    double evaluate(double x);

    bool isValid() const;
    QString getError() const;

private:
    int id;
    QString expression;
    QColor color;
    bool visible;

    std::unique_ptr<MuParserEvaluator> evaluator;
};

#endif
