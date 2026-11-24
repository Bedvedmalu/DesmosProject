#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QPointF>
#include <QPair>

class Viewport
{
public:
    Viewport();

    QPointF worldToScreen(const QPointF &point) const;

    QPointF screenToWorld(const QPointF &point) const;

    void panBy(double delta_X, double delta_Y);

    QPair<double, double> getVisibleXRange() const;

    QPair<double, double> getVisibleYRange() const;

    void setSize(int newWidth, int newHeight);

    void reset();

    double getScale() const;

    QPointF getCenter() const;

    void zoomAt(QPointF cursorPosition, double zoom);

private:
    double scale = 50;

    double centerX = 0;

    double centerY = 0;

    int width = 800;

    int height = 600;

    const double minScale = 0.0001;

    const double maxScale = 10000;

};

#endif
