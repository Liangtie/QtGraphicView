#ifndef __QTGRAPHICVIEW_H__
#define __QTGRAPHICVIEW_H__

#pragma once

#include <memory>
#pragma once

#include <QGraphicsView>

#include "QtGraphicView/QtGraphicView_export.hpp"

class QMenu;
class QGraphicsScene;
struct FlowViewStyle;
class FLowStyleCollection;
class QTGRAPHICVIEW_EXPORT QtGridGraphicView : public QGraphicsView
{
public:
  QtGridGraphicView(QGraphicsScene* scene,
                    QMenu* menu,
                    QWidget* parent = nullptr);
  ~QtGridGraphicView() override;
  QtGridGraphicView(const QtGridGraphicView&) = delete;
  auto operator=(const QtGridGraphicView&) -> const QtGridGraphicView& = delete;

  void scaleUp();

  void scaleDown();

  void setStyleCollection(std::shared_ptr<FLowStyleCollection> style);

protected:
  void contextMenuEvent(QContextMenuEvent* event) override;

  void wheelEvent(QWheelEvent* event) override;

  void keyPressEvent(QKeyEvent* event) override;

  void keyReleaseEvent(QKeyEvent* event) override;

  void mousePressEvent(QMouseEvent* event) override;

  void mouseMoveEvent(QMouseEvent* event) override;

  void drawBackground(QPainter* painter, const QRectF& r) override;

  void showEvent(QShowEvent* event) override;

  [[nodiscard]] auto scene() const -> QGraphicsScene&;

private:
  QPointF clickPos_;
  QGraphicsScene* scene_;
  std::unique_ptr<QMenu> menu_;
  std::shared_ptr<FLowStyleCollection> styleCollection_ {};
};

#endif  // __QTGRAPHICVIEW_H__