#ifndef FLOW_STYLE_COLLECTION_H
#define FLOW_STYLE_COLLECTION_H

#pragma once

#include <QColor>
#include <QPixmap>

#include "QtGraphicView/QtGraphicView_export.hpp"

struct FlowViewStyle;
struct NodeStyle;

class QTGRAPHICVIEW_EXPORT FLowStyleCollection
{
public:
  virtual ~FLowStyleCollection() = default;

  [[nodiscard]] virtual const FlowViewStyle& flowViewStyle() const;

  [[nodiscard]] virtual const NodeStyle& nodeStyle() const;

  static FLowStyleCollection& defaultStyle();

private:
};

#endif
