#include "diagramscene.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <commandfactory.h>

DiagramScene::DiagramScene(QObject *parent) : QGraphicsScene(parent) {
  QBrush brush;
  QColor color(Qt::black);
  brush.setColor(color);
  setBackgroundBrush(brush);
}

void DiagramScene::SetDataManager(std::shared_ptr<DataManager> manager) {
  manager_ = manager;
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
  EntityMouseMoveCommandFactory factory(manager_, this, mouseEvent);
  std::vector<std::shared_ptr<Command>> commands = factory.GenerateCommand();
  SendCommand(commands);

  QGraphicsScene::mouseMoveEvent(mouseEvent);
}
