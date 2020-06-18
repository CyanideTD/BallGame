#ifndef COMMAND_H
#define COMMAND_H

#include <entity.h>
#include <diagramentity.h>
#include <datamanager.h>
#include <diagramscene.h>

struct CommandArg {
  std::shared_ptr<DataManager> manager;
  DiagramScene* scene = nullptr;
};

class Command {
public:
  Command() = default;
  virtual int Init(const CommandArg& arg) = 0;
  virtual int Execute() = 0;
  virtual std::vector<int> GetRelateIds() = 0;

  bool Valid();

public:
  double valid_time_ = 0;
  int client_id_ = 0;
  int command_seq_ = 0;
};

class SetTypeCommand : public Command {
public:
  SetTypeCommand(const int id, const EntityType type);
  SetTypeCommand(const SetTypeCommand& type);
  SetTypeCommand &operator =(const SetTypeCommand& type);

  int Init(const CommandArg& arg) override;
  int Execute() override;
  std::vector<int> GetRelateIds() override;

public:
  int entity_id;
  EntityType type_;

  std::shared_ptr<Entity> entity_;

};

class MoveCommand : public Command {
public:
  MoveCommand(const int id, const std::vector<QPointF>& points);
  MoveCommand(const MoveCommand& command);
  MoveCommand& operator =(const MoveCommand& command);

  int Init(const CommandArg& arg) override;
  int Execute() override;
  std::vector<int> GetRelateIds() override;

public:
  int entity_id;
  std::vector<QPointF> points_;

  std::shared_ptr<Entity> entity_;
};

class CreateCommand : public Command {
public:
  CreateCommand() = default;
  CreateCommand(const int id, const std::vector<QPointF> &points, EntityType type);
  CreateCommand(const CreateCommand& command);
  CreateCommand& operator =(const CreateCommand& command);
  int Init(const CommandArg& arg) override;
  int Execute() override;
  std::vector<int> GetRelateIds() override;

public:
  int entity_id = 0;
  std::vector<QPointF> points_;
  EntityType type_;
  std::shared_ptr<DataManager> manager_;
  QGraphicsScene* scene_ = nullptr;
};

class SetStateCommand : public Command {
public:
  SetStateCommand(const int id, const std::vector<QPointF> &points, const EntityType type);
  SetStateCommand(const SetStateCommand& command);
  SetStateCommand& operator =(const SetStateCommand& command);
  int Init(const CommandArg& arg) override;
  int Execute() override;
  std::vector<int> GetRelateIds() override;

public:
  int entity_id_ = 0;
  std::vector<QPointF> points_;
  EntityType type_;
  std::shared_ptr<Entity> entity_;
  std::shared_ptr<DataManager> manager_;
  DiagramScene* scene_ = nullptr;
};

#endif // COMMAND_H
