#ifndef GRAPHCANVAS_H
#define GRAPHCANVAS_H

#include <QWidget>

#include "graphrenderer.h"
#include "viewport.h"

class FunctionRepository;

class GraphCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit GraphCanvas(QWidget* parent = nullptr);
    void resetView();
    void setRepository(FunctionRepository* repository);
    void requestRedraw();
    void clearSelection();

signals:
    void cursorPositionChanged(double x, double y);

protected:
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void drawSelection(QPainter& painter);
    void panTo(const QPointF& position);

    bool isDragging = false;
    QPointF pressPosition;
    QPointF lastMousePosition;
    FunctionRepository* repository = nullptr;
    std::optional<GraphSelection> selection;
    const double zoom = 1.15;
    Viewport viewport;
    GraphRenderer renderer;
};

#endif
