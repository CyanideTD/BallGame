#include "commandfactory.h"
#include <diagramscene.h>
#include <datamanager.h>
#include <mediator.h>
#include <QGraphicsSceneMouseEvent>

CommandFactory::CommandFactory() {

}


std::vector<std::shared_ptr<Command> > EntityMouseMoveCommandFactory::GenerateCommand() {

  std::vector<std::shared_ptr<Command>> commands;

  if (event_->buttons() != Qt::LeftButton) {
    return commands;
  }

  auto item_list = scene_->selectedItems();

  QPointF last_pos = event_->lastScenePos();
  QPointF cur_pos = event_->scenePos();

  QPointF delta = cur_pos - last_pos;

  std::map<int, std::vector<DiagramPoint*>> point_map;
  for (auto it : item_list) {
    GraphicsItem* item = dynamic_cast<GraphicsItem*>(it);
    if (nullptr == item || item->GetType() != ItemType::ITEM_TYPE_POINT) {
      continue;
    }

    int id = item->GetId();
    DiagramPoint* point = dynamic_cast<DiagramPoint*>(item);
    if (nullptr != point) {
      point_map[id].push_back(point);
    }
  }

  for (auto it : point_map) {
    int id = it.first;
    std::vector<DiagramPoint*> points = it.second;

    std::shared_ptr<Entity> entity = data_manager_->GetEntityBuffer()->GetSP(id);
    if (!entity) {
      continue;
    }

    std::vector<QPointF> cur_points = entity->GetShape()->GetPoints();
    for (auto it : points) {
      cur_points[it->GetIndex()] = it->pos() + delta;
    }

    std::shared_ptr<MoveCommand> move_command = std::make_shared<MoveCommand>(id, cur_points);
    commands.push_back(move_command);
  }

  return commands;
}

EntityMouseMoveCommandFactory::EntityMouseMoveCommandFactory(
  std::shared_ptr<DataManager> manager,
  DiagramScene *scene,
  QGraphicsSceneMouseEvent *mouseEvent) :
    data_manager_(manager),
    scene_(scene),
    event_(mouseEvent){}
