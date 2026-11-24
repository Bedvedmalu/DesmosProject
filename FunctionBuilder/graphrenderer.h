#ifndef GRAPHRENDERER_H
#define GRAPHRENDERER_H

#include "viewport.h"

#include <QColor>
#include <QPen>
#include <QString>
#include <QPainter>
#include <QPainterPath>

#include <vector>
#include <optional>

class GraphFunction;

struct GraphSelection
{
    int functionId;
    double x;
};

class GraphRenderer
{
public:
    GraphRenderer();

    void render(QPainter &painter, const Viewport &viewport, std::vector<GraphFunction>* functions = nullptr);

    std::optional<GraphSelection> pickFunction(const QPointF& cursor, const Viewport& viewport, const QSize& size, std::vector<GraphFunction>& functions);

private:
    QPainterPath functionPath(GraphFunction& function, const Viewport& viewport, int firstPixel, int lastPixel, int height);
    void drawBackground(QPainter &painter);

    void drawGrid(QPainter &painter, const Viewport &viewport);

    void drawAxes(QPainter &painter, const Viewport &viewport);

    void drawAxisLabels(QPainter &painter, const Viewport &viewport);

    void drawFunction(QPainter &painter, GraphFunction &function, const Viewport &viewport);

    double calculateGridStep(double scale);
};

#endif
