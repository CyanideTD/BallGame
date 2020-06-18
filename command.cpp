#include <chrono>

#include "command.h"
#include <mediator.h>
#include <diagramscene.h>
#include <datamanager.h>


SetTypeCommand::SetTypeCommand(const int id, const EntityType type) {
  entity_id = id;
  type_ = type;
}

SetTypeCommand::SetTypeCommand(const SetTypeCommand &type) {
  type_ = type.type_;
  entity_id = type.entity_id;
}

SetTypeCommand &SetTypeCommand::operator =(const SetTypeCommand &type){
  if (this != &type) {
    type_ = type.type_;
    entity_id = type.entity_id;
  }

  return *this;
}

std::shared_ptr<Command> SetTypeCommand::DeepCopy() {
  std::shared_ptr<SetTypeCommand> command = std::make_shared<SetTypeCommand>(entity_id, type_);
  return command;
}

int SetTypeCommand::Init(const CommandArg& arg) {
  entity_ = arg.manager->GetEntityBuffer()->GetSP(entity_id);
  if (entity_) {
    return 0;
  } else {
    return -1;
  }
}

int SetTypeCommand::Execute() {
  if (entity_) {
    entity_->GetType()->SetType(type_);
    return 0;
  } else {
    return -1;
  }

}

std::vector<int> SetTypeCommand::GetRelateIds() {
  return {entity_id};
}

MoveCommand::MoveCommand(const int id, const std::vector<QPointF> &points) {
  entity_id = id;
  points_ = points;
}

MoveCommand::MoveCommand(const MoveCommand &command) {
  entity_id = command.entity_id;
  points_ = command.points_;
}

MoveCommand &MoveCommand::operator =(const MoveCommand &command) {
  if (&command != this) {
    entity_id = command.entity_id;
    points_ = command.points_;
  }
  return *this;
}

std::shared_ptr<Command> MoveCommand::DeepCopy() {
  std::shared_ptr<MoveCommand> move_command = std::make_shared<MoveCommand>(entity_id, points_);
  return move_command;
}

int MoveCommand::Init(const CommandArg &arg) {
  entity_ = arg.manager->GetEntityBuffer()->GetSP(entity_id);
  if (entity_) {
    return 0;
  } else {
    return -1;
  }
}

int MoveCommand::Execute() {
  if (entity_) {
    entity_->GetShape()->SetPoints(points_);

    entity_->GetMediator()->NotifyShapeChanged();
    entity_->GetMediator()->NotifyTypeChanged();
    return 0;
  } else {
    return -1;
  }
}

std::vector<int> MoveCommand::GetRelateIds() {
  return {entity_id};
}

CreateCommand::CreateCommand(const int id, const std::vector<QPointF> &points, EntityType type) {
  entity_id = id;
  points_ = points;
  type_ = type;
}

CreateCommand::CreateCommand(const CreateCommand &command) {
  entity_id = command.entity_id;
  points_ = command.points_;
  type_ = command.type_;
}

CreateCommand &CreateCommand::operator =(const CreateCommand &command) {
  if (this != &command) {
    entity_id = command.entity_id;
    points_ = command.points_;
    type_ = command.type_;
  }
  return *this;
}

std::shared_ptr<Command> CreateCommand::DeepCopy() {
  std::shared_ptr<CreateCommand> create_command = std::make_shared<CreateCommand>(entity_id, points_, type_);
  return create_command;
}

int CreateCommand::Init(const CommandArg& arg) {
  manager_ = arg.manager;
  scene_ = arg.scene;
  return 0;
}

int CreateCommand::Execute() {
  std::shared_ptr<Entity> check_entity = manager_->GetEntityBuffer()->GetSP(entity_id);
  if (check_entity) {
    return -1;
  }
  std::shared_ptr<Entity> entity = std::make_shared<Entity>(entity_id, points_, type_);
  std::shared_ptr<DiagramEntity> diagram_entity = std::make_shared<DiagramEntity>(entity_id, points_, type_);

  std::shared_ptr<EntityMediator> mediator = std::make_shared<EntityMediator>();
  mediator->RegisterDiagram(diagram_entity);
  mediator->RegisterEntity(entity);
  entity->SetMediator(mediator);

  manager_->GetEntityBuffer()->PushSP(entity);
  if (scene_ != nullptr) {
    diagram_entity->Draw(scene_);
  }
  return 0;
}

std::vector<int> CreateCommand::GetRelateIds() {
  return {entity_id};
}

bool Command::Valid() {
  std::chrono::milliseconds mill_sec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  if (valid_time_ <= mill_sec.count()) {
    return true;
  } else {
    return false;
  }
}

SetStateCommand::SetStateCommand(const int id, const std::vector<QPointF> &points, const EntityType type) {
  entity_id_ = id;
  points_ = points;
  type_ = type;
}

SetStateCommand::SetStateCommand(const SetStateCommand &command) {
  entity_id_ = command.entity_id_;
  points_ = command.points_;
  type_ = command.type_;
}

SetStateCommand &SetStateCommand::operator =(const SetStateCommand &command) {
  if (this != &command) {
    entity_id_ = command.entity_id_;
    points_ = command.points_;
    type_ = command.type_;
  }
  return *this;
}

std::shared_ptr<Command> SetStateCommand::DeepCopy() {
  std::shared_ptr<SetStateCommand> command = std::make_shared<SetStateCommand>(entity_id_, points_, type_);
  return command;
}

int SetStateCommand::Init(const CommandArg &arg) {
  entity_ = arg.manager->GetEntityBuffer()->GetSP(entity_id_);
  scene_ = arg.scene;
  manager_ = arg.manager;

  return 0;
}

int SetStateCommand::Execute() {
  if (entity_) {
    entity_->GetShape()->SetPoints(points_);
    entity_->GetType()->SetType(type_);
    entity_->GetMediator()->NotifyShapeChanged();
    entity_->GetMediator()->NotifyTypeChanged();
  } else {
    CreateCommand command(entity_id_, points_, type_);
    command.manager_ = manager_;
    command.scene_ = scene_;
    command.Execute();
  }

  return 0;
}

std::vector<int> SetStateCommand::GetRelateIds() {
  return {entity_id_};
}
