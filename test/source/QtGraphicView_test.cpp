#include <QApplication>
#include <string>

#include "QtGraphicView/QtGraphicView.hpp"

#include <qapplication.h>
#include <qgraphicsscene.h>
#include <qmenu.h>

auto main(int argc, char** argv) -> int
{
  QApplication a(argc, argv);

  QtGridGraphicView view(new QGraphicsScene, new QMenu);
  view.show();
  return a.exec();
}
