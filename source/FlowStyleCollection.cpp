#include "QtGraphicView/FlowStyle.h"

#include "QtGraphicView/FlowStyleCollection.h"

static const auto DefaultFlowViewStyle = FlowViewStyle();
static const auto DefaultNodeStyle = NodeStyle();

FLowStyleCollection& FLowStyleCollection::defaultStyle()
{
  static FLowStyleCollection instance;
  return instance;
}

const FlowViewStyle& FLowStyleCollection::flowViewStyle() const
{
  return DefaultFlowViewStyle;
}

const NodeStyle& FLowStyleCollection::nodeStyle() const
{
  return DefaultNodeStyle;
}
