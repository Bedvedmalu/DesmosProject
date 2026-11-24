#include "viewport.h"

using namespace std;

Viewport::Viewport() {}

QPointF Viewport::worldToScreen(const QPointF &point) const {
    double x_new = width / 2.0 + scale * (point.x() - centerX);
    double y_new = height / 2.0 - scale * (point.y() - centerY);

    return QPointF(x_new, y_new);
}

QPointF Viewport::screenToWorld(const QPointF &point) const {
    double x_new = centerX + (point.x() - width / 2.0) / scale;
    double y_new = centerY + (height / 2.0 - point.y()) / scale;

    return QPointF(x_new, y_new);
}

void Viewport::panBy(double delta_X, double delta_Y)  {
    centerX -= delta_X/scale;
    centerY += delta_Y/scale;
}


QPair<double, double> Viewport::getVisibleXRange() const {
    return {centerX - width / (scale * 2), centerX + width / (scale * 2)};
}

QPair<double, double> Viewport::getVisibleYRange() const {
    return {centerY - height / (scale * 2), centerY + height / (scale * 2)};
}

void Viewport::setSize(int newWidth, int newHeight) {
    height = newHeight;
    width = newWidth;
}

void Viewport::reset() {
    centerX = 0;
    centerY = 0;
    scale = 50;
}

double Viewport::getScale() const {
    return scale;
}

QPointF Viewport::getCenter() const {
    return QPointF(centerX, centerY);
}

void Viewport::zoomAt(QPointF cursorPosition, double zoom) {
    QPointF math_Position = screenToWorld(cursorPosition);
     scale *= zoom;
    if ((scale < minScale) || (scale > maxScale)) {
            scale /= zoom;
    }

    centerX = math_Position.x() - (cursorPosition.x() - width / 2.0) / scale;
    centerY = math_Position.y() + (cursorPosition.y() - height / 2.0) / scale;
}
