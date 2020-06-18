#include "diagramscene.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>

DiagramScene::DiagramScene(QObject *parent) : QGraphicsScene(parent) {
  QBrush brush;
  QColor color(Qt::black);
  brush.setColor(color);
  setBackgroundBrush(brush);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
  mouseEvent->lastScenePos();
  mouseEvent->pos();
  selectedItems();
  std::vector<QPointF> points;

  QGraphicsScene::mouseMoveEvent(mouseEvent);
}
