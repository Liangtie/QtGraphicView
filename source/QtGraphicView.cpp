#include <QBrush>
#include <QContextMenuEvent>
#include <QDebug>
#include <string>

#include "QtGraphicView/QtGraphicView.hpp"

#include <qbrush.h>
#include <qcolor.h>

#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QMenu>

#include "QtGraphicView/FlowStyle.h"
#include "QtGraphicView/FlowStyleCollection.h"

inline auto stringToColor(const std::string& str)
{
    return QColor(QString::fromStdString(str));
}

QtGridGraphicView::QtGridGraphicView(QGraphicsScene* scene, QMenu* menu, QWidget* parent)
    : QGraphicsView(parent)
    , scene_(scene)
    , menu_(menu)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(
        QColor(QString::fromStdString(FLowStyleCollection::defaultStyle().flowViewStyle().BackgroundColor)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    // setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    QGraphicsView::setScene(scene_);
}

QtGridGraphicView::~QtGridGraphicView() {}

void QtGridGraphicView::contextMenuEvent(QContextMenuEvent* event)
{
    if (itemAt(event->pos())) {
        QGraphicsView::contextMenuEvent(event);
        return;
    }
    if (!menu_)
        return;
    menu_->exec(event->globalPos());
}

void QtGridGraphicView::wheelEvent(QWheelEvent* event)
{
    QPoint delta = event->angleDelta();

    if (delta.y() == 0) {
        event->ignore();
        return;
    }

    double const d = delta.y() / std::abs(delta.y());

    if (d > 0.0)
        scaleUp();
    else
        scaleDown();
    update();
}

void QtGridGraphicView::scaleUp()
{
    double const step = 1.2;
    double const factor = std::pow(step, 1.0);

    QTransform t = transform();

    if (t.m11() > 2.0)
        return;

    scale(factor, factor);
}

void QtGridGraphicView::scaleDown()
{
    double const step = 1.2;
    double const factor = std::pow(step, -1.0);

    scale(factor, factor);
}

void QtGridGraphicView::setStyleCollection(std::shared_ptr<FLowStyleCollection> style)
{
    if (!style)
        return;

    styleCollection_ = std::move(style);

    setBackgroundBrush(QColor(QString::fromStdString(styleCollection_->flowViewStyle().BackgroundColor)));
}

void QtGridGraphicView::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_Shift:
            setDragMode(QGraphicsView::RubberBandDrag);
            break;

        default:
            break;
    }

    QGraphicsView::keyPressEvent(event);
}

void QtGridGraphicView::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_Shift:
            setDragMode(QGraphicsView::ScrollHandDrag);
            break;

        default:
            break;
    }
    QGraphicsView::keyReleaseEvent(event);
}

void QtGridGraphicView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        clickPos_ = mapToScene(event->pos());
    }
}

void QtGridGraphicView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
    if (scene().mouseGrabberItem() == nullptr && event->buttons() == Qt::LeftButton) {
        // Make sure shift is not being pressed
        if ((event->modifiers() & Qt::ShiftModifier) == 0) {
            QPointF difference = clickPos_ - mapToScene(event->pos());
            setSceneRect(sceneRect().translated(difference.x(), difference.y()));
        }
    }
}

void QtGridGraphicView::drawBackground(QPainter* painter, const QRectF& r)
{
    QGraphicsView::drawBackground(painter, r);
    auto drawGrid = [&](double gridStep)
    {
        QRect windowRect = rect();
        QPointF tl = mapToScene(windowRect.topLeft());
        QPointF br = mapToScene(windowRect.bottomRight());

        double left = std::floor(tl.x() / gridStep - 0.5);
        double right = std::floor(br.x() / gridStep + 1.0);
        double bottom = std::floor(tl.y() / gridStep - 0.5);
        double top = std::floor(br.y() / gridStep + 1.0);

        // vertical lines
        for (int xi = int(left); xi <= int(right); ++xi) {
            QLineF line(xi * gridStep, bottom * gridStep, xi * gridStep, top * gridStep);

            painter->drawLine(line);
        }

        // horizontal lines
        for (int yi = int(bottom); yi <= int(top); ++yi) {
            QLineF line(left * gridStep, yi * gridStep, right * gridStep, yi * gridStep);
            painter->drawLine(line);
        }
    };

    auto const& flowViewStyle =
        ((styleCollection_ ? (*styleCollection_) : FLowStyleCollection::defaultStyle())).flowViewStyle();

    QBrush bBrush = backgroundBrush();

    QPen pfine(stdStringToBrush(flowViewStyle.FineGridColor), 1.0);

    painter->setPen(pfine);
    drawGrid(15);

    QPen p(stdStringToBrush(flowViewStyle.CoarseGridColor), 1.0);

    painter->setPen(p);
    drawGrid(150);
}

void QtGridGraphicView::showEvent(QShowEvent* event)
{
    scene().setSceneRect(this->rect());
    QGraphicsView::showEvent(event);
}

QGraphicsScene& QtGridGraphicView::scene() const
{
    return *scene_;
}
