#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <memory>
#include <QGraphicsScene>
#include <command.h>

class DataManager;

class DiagramScene : public QGraphicsScene {
  Q_OBJECT
public:
  DiagramScene(QObject *parent = Q_NULLPTR);

  void SetDataManager(std::shared_ptr<DataManager> manager);

signals:
  void SendCommand(std::vector<std::shared_ptr<Command>> commands);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
  std::shared_ptr<DataManager> manager_;
};

#endif // DIAGRAMSCENE_H
