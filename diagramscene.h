#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <memory>
#include <QGraphicsScene>
#include <command.h>

class DiagramScene : public QGraphicsScene {
  Q_OBJECT
public:
  DiagramScene(QObject *parent = Q_NULLPTR);

signals:
  void SendCommand(std::vector<std::shared_ptr<Command>> commands);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
};

#endif // DIAGRAMSCENE_H
