#include "graphrenderer.h"
#include "graphfunction.h"

#include <cmath>
#include <algorithm>

using namespace std;

GraphRenderer::GraphRenderer() {}


void GraphRenderer::drawBackground(QPainter &painter) {
    painter.fillRect(painter.viewport(), QColor("#111923"));
}

double GraphRenderer::calculateGridStep(double scale) {
    double targetStep = 60.0 / scale;
    double power = pow(10.0, floor(log10(targetStep)));
    double normalized = targetStep / power;

    double multiplier;

    if (normalized < sqrt(2)) {
        multiplier = 1.0;
    } else if (normalized < sqrt(10.0)) {
        multiplier = 2.0;
    } else if (normalized < sqrt(50)) {
        multiplier = 5.0;
    } else {
        multiplier = 10.0;
    }

    return multiplier * power;
}

void GraphRenderer::drawGrid(QPainter &painter, const Viewport &viewport) {
    double step = calculateGridStep(viewport.getScale());
    QPair<double, double> xRange = viewport.getVisibleXRange();
    QPair<double, double> yRange = viewport.getVisibleYRange();

    QRect area = painter.viewport();

    painter.save();
    painter.setPen(QPen(QColor("#34465D"), 1));

    int startIndex = ceil(xRange.first / step);
    int endIndex = floor(xRange.second / step);

    for (int i = startIndex; i <= endIndex; ++i) {
        if (i == 0) continue;

        double x = i * step;
        QPointF screenPointX = viewport.worldToScreen(QPointF(x, 0));

        painter.drawLine(QPointF(screenPointX.x(), 0), QPointF(screenPointX.x(), area.height()));

    }

    startIndex = ceil(yRange.first / step);
    endIndex = floor(yRange.second / step);

    for (int j = startIndex; j <= endIndex; ++j) {
        if (j == 0) continue;

        double y = j * step;
        QPointF screenPointY = viewport.worldToScreen(QPointF(0, y));

        painter.drawLine(QPointF(0, screenPointY.y()), QPointF(area.width(), screenPointY.y()));
    }

    painter.restore();
}

void GraphRenderer::drawAxisLabels(QPainter &painter, const Viewport &viewport) {
    double step = calculateGridStep(viewport.getScale());

    QPair<double, double> xRange = viewport.getVisibleXRange();
    QPair<double, double> yRange = viewport.getVisibleYRange();

    QPointF center = viewport.worldToScreen(QPointF(0, 0));

    QRect area = painter.viewport();

    if (area.width() < 60 || area.height() < 20) return;
    painter.save();

    painter.setPen(QColor("#CBD5E1"));

    QFont font = painter.font();
    font.setPointSize(9);
    painter.setFont(font);

    double labelY = clamp(center.y() + 5.0, 0.0, area.height() - 20.0);
    double labelX = clamp(center.x() + 8.0, 0.0, area.width() - 60.0);

    int startIndex = ceil(xRange.first / step);
    int endIndex = floor(xRange.second / step);

    for (int i = startIndex; i <= endIndex; ++i) {
        if (i == 0) continue;

        double x = i * step;
        QPointF screenPointX = viewport.worldToScreen(QPointF(x, 0));
        QRectF textRect(screenPointX.x() - 30, labelY, 60, 20);
        painter.drawText(textRect, Qt::AlignCenter, QString::number(x, 'g', 6));
    }

    startIndex = ceil(yRange.first / step);
    endIndex = floor(yRange.second / step);

    for (int j = startIndex; j <= endIndex; ++j) {
        if (j == 0) continue;

        double y = j * step;
        QPointF screenPointY = viewport.worldToScreen(QPointF(0, y));
        QRectF textRect(labelX, screenPointY.y() - 10, 60, 20);
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, QString::number(y, 'g', 6));
    }

    painter.restore();
}

void GraphRenderer::drawAxes(QPainter &painter, const Viewport &viewport) {
    QPointF center = viewport.worldToScreen(QPointF(0, 0));

    QRect area = painter.viewport();

    painter.save();

    painter.setPen(QPen(QColor("#E2E8F0"), 2));

    painter.drawLine(QPointF(0, center.y()), QPointF(area.width(), center.y()));
    painter.drawLine(QPointF(center.x(), 0), QPointF(center.x(), area.height()));

    painter.restore();
}


QPainterPath GraphRenderer::functionPath(GraphFunction& function, const Viewport& viewport,
                                         int firstPixel, int lastPixel, int height)
{
    QPainterPath path;
    bool hasPrevious = false;
    QPointF previous;
    for (int px = firstPixel; px <= lastPixel; px += 2) {
        double x = viewport.screenToWorld(QPointF(px, 0)).x();
        const auto point = viewport.worldToScreen({x, function.evaluate(x)});
        if (!std::isfinite(point.y()) || std::abs(point.y()) > 100000.0) {
            hasPrevious = false;
            continue;
        }
        bool continuous = hasPrevious;
        if (continuous && std::abs(point.y() - previous.y()) > std::max(12.0, height * 0.05)) {
            double midX = viewport.screenToWorld({px - 1.0, 0}).x();
            double midY = viewport.worldToScreen({midX, function.evaluate(midX)}).y();
            continuous = std::isfinite(midY)
                      && std::abs(midY - (previous.y() + point.y()) / 2.0)
                         <= std::max(2.0, std::abs(point.y() - previous.y()) * 0.15);
        }
        if (continuous)
            path.lineTo(point);
        else
            path.moveTo(point);
        previous = point;
        hasPrevious = true;
    }
    return path;
}

void GraphRenderer::drawFunction(QPainter& painter, GraphFunction& function, const Viewport& viewport)
{
    if (!function.isVisible() || !function.isValid())
        return;
    const auto area = painter.viewport();
    painter.save();
    painter.setClipRect(area);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(function.getColor(), 2));
    painter.drawPath(functionPath(function, viewport, 0, area.width(), area.height()));
    painter.restore();
}

std::optional<GraphSelection> GraphRenderer::pickFunction(const QPointF& cursor,
        const Viewport& viewport, const QSize& size, std::vector<GraphFunction>& functions)
{
    constexpr int radius = 8;
    const int left = std::max(0, (int(std::floor(cursor.x())) - radius - 2) / 2 * 2);
    const int right = std::min(size.width(), int(std::ceil(cursor.x())) + radius + 2);
    double bestSquared = radius * radius;
    std::optional<GraphSelection> best;
    for (auto& f : functions) {
        if (!f.isVisible() || !f.isValid() || f.getColor().alpha() == 0)
            continue;
        const auto path = functionPath(f, viewport, left, right, size.height());
        QPointF previous;
        for (int i = 0; i < path.elementCount(); ++i) {
            const auto element = path.elementAt(i);
            const QPointF end(element.x, element.y);
            if (element.isLineTo()) {
                const auto direction = end - previous;
                const double lengthSquared = QPointF::dotProduct(direction, direction);
                const double t = std::clamp(QPointF::dotProduct(cursor - previous, direction)
                                            / lengthSquared, 0.0, 1.0);
                const auto projected = previous + direction * t;
                const double x = viewport.screenToWorld(projected).x();
                const auto onCurve = viewport.worldToScreen({x, f.evaluate(x)});
                const auto delta = cursor - onCurve;
                const double distance = QPointF::dotProduct(delta, delta);
                if (distance <= bestSquared) {
                    bestSquared = distance;
                    best = GraphSelection{f.getId(), x};
                }
            }
            previous = end;
        }
    }
    return best;
}

void GraphRenderer::render(QPainter &painter, const Viewport &viewport, std::vector<GraphFunction>* functions)
{
    drawBackground(painter);
    drawGrid(painter, viewport);
    drawAxes(painter, viewport);

    if (functions) {
        for (GraphFunction& function : *functions) {
            drawFunction(painter, function, viewport);
        }
    }

    drawAxisLabels(painter, viewport);
}
