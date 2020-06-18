#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <vector>
#include <memory>

class DiagramScene;
class QGraphicsSceneMouseEvent;
class Command;
class DataManager;

class CommandFactory {
public:
  CommandFactory();
  virtual ~CommandFactory() {}
  virtual std::vector<std::shared_ptr<Command>> GenerateCommand() = 0;
};

class EntityMouseMoveCommandFactory : public CommandFactory {
public:
  EntityMouseMoveCommandFactory(std::shared_ptr<DataManager> manager, DiagramScene* scene, QGraphicsSceneMouseEvent* mouseEvent);
  virtual ~EntityMouseMoveCommandFactory() {}
  std::vector<std::shared_ptr<Command>> GenerateCommand();
private:
  std::shared_ptr<DataManager> data_manager_;
  DiagramScene* scene_ = nullptr;
  QGraphicsSceneMouseEvent* event_ = nullptr;
};

#endif // COMMANDFACTORY_H
