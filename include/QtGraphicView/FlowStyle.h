#ifndef __FLOW_STYLE_H__
#define __FLOW_STYLE_H__
#pragma once

#include <QBrush>
#include <string>

#include "QtGraphicView/QtGraphicView_export.hpp"
#include "json.hpp"

struct QTGRAPHICVIEW_EXPORT FlowViewStyle
{
  std::string BackgroundColor = "#353535";
  std::string FineGridColor = "#3c3c3c";
  std::string CoarseGridColor = "#191919";
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(FlowViewStyle,
                                 BackgroundColor,
                                 FineGridColor,
                                 CoarseGridColor);
};

struct QTGRAPHICVIEW_EXPORT NodeStyle
{
  std::string NormalBoundaryColor = "#FFFFFF";
  std::string SelectedBoundaryColor = "#FFA500";
  std::string GradientColor0 = "gray";
  std::string GradientColor1 = "#505050";
  std::string GradientColor2 = "#404040";
  std::string GradientColor3 = "#3A3A3A";
  std::string ShadowColor = "#141414";
  std::string FontColor = "white";
  std::string FontColorFaded = "gray";
  std::string ConnectionPointColor = "#A9A9A9";
  float PenWidth = 1.5;
  float HoveredPenWidth = 1.5;
  float ConnectionPointDiameter = 8.0;
};

inline auto stdStringToBrush(const std::string& strColor)
{
  return QBrush(QColor(QString::fromStdString(strColor)));
}

#endif  // __FLOW_STYLE_H__