#include "graphcanvas.h"
#include "functionrepository.h"

#include <QApplication>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QWheelEvent>
#include <algorithm>
#include <cmath>

GraphCanvas::GraphCanvas(QWidget* parent) : QWidget(parent)
{
    setMouseTracking(true);
}

void GraphCanvas::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    renderer.render(painter, viewport, repository ? &repository->getRepository() : nullptr);
    drawSelection(painter);
}

void GraphCanvas::drawSelection(QPainter& painter)
{
    if (!selection || !repository)
        return;
    auto* f = repository->getFunctionById(selection->functionId);
    if (!f || !f->isValid() || !f->isVisible() || f->getColor().alpha() == 0)
        return;
    const double x = selection->x;
    const double y = f->evaluate(x);
    const QPointF pixel = viewport.worldToScreen({x, y});
    if (!std::isfinite(y) || !QRectF(rect()).contains(pixel))
        return;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2));
    painter.setBrush(f->getColor());
    painter.drawEllipse(pixel, 5.5, 5.5);

    const QString text = QString("(%1, %2)").arg(QString::number(x, 'g', 7),
                                                 QString::number(y, 'g', 7));
    const auto fm = painter.fontMetrics();
    QRectF box(0, 0, fm.horizontalAdvance(text) + 16, fm.height() + 8);
    const double left = pixel.x() + 10 + box.width() <= width()
                      ? pixel.x() + 10 : pixel.x() - 10 - box.width();
    const double top = pixel.y() >= box.height() + 10
                     ? pixel.y() - 10 - box.height() : pixel.y() + 10;
    box.moveTo(std::clamp(left, 0.0, std::max(0.0, width() - box.width())),
               std::clamp(top, 0.0, std::max(0.0, height() - box.height())));
    painter.setPen(QPen(QColor("#8091A8"), 1));
    painter.setBrush(QColor("#202936"));
    painter.drawRoundedRect(box, 5, 5);
    painter.setPen(Qt::white);
    painter.drawText(box, Qt::AlignCenter, text);
}

void GraphCanvas::wheelEvent(QWheelEvent* event)
{
    const int delta = event->angleDelta().y();
    if (delta)
        viewport.zoomAt(event->position(), delta > 0 ? zoom : 1.0 / zoom);
    update();
    event->accept();
}

void GraphCanvas::resetView()
{
    viewport.reset();
    update();
}

void GraphCanvas::setRepository(FunctionRepository* newRepository)
{
    repository = newRepository;
    clearSelection();
}

void GraphCanvas::clearSelection()
{
    selection.reset();
    update();
}

void GraphCanvas::requestRedraw()
{
    if (selection) {
        auto* f = repository->getFunctionById(selection->functionId);
        if (!f || !f->isVisible() || !f->isValid() || f->getColor().alpha() == 0)
            selection.reset();
    }
    update();
}

void GraphCanvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
        return QWidget::mousePressEvent(event);
    isDragging = false;
    pressPosition = lastMousePosition = event->position();
    event->accept();
}

void GraphCanvas::panTo(const QPointF& position)
{
    if (!isDragging && (position - pressPosition).manhattanLength() < QApplication::startDragDistance())
        return;
    isDragging = true;
    const QPointF delta = position - lastMousePosition;
    lastMousePosition = position;
    viewport.panBy(delta.x(), delta.y());
    update();
}

void GraphCanvas::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
        panTo(event->position());
    const QPointF world = viewport.screenToWorld(event->position());
    emit cursorPositionChanged(world.x(), world.y());
    event->accept();
}

void GraphCanvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
        return QWidget::mouseReleaseEvent(event);
    panTo(event->position());
    if (!isDragging && repository) {
        selection = renderer.pickFunction(event->position(), viewport, size(), repository->getRepository());
        update();
    }
    isDragging = false;
    event->accept();
}

void GraphCanvas::resizeEvent(QResizeEvent* event)
{
    viewport.setSize(event->size().width(), event->size().height());
    QWidget::resizeEvent(event);
}
