#ifndef COMMAND_H
#define COMMAND_H

#include <entity.h>
#include <diagramentity.h>

class Command {
public:
  Command();
  virtual void Execute() = 0;
};

class SetTypeCommand : public Command {
public:
  SetTypeCommand();
  void Execute() override;

private:
  Entity* entity;
  EntityType type;
};

class MoveCommand : public Command {
public:
  MoveCommand();
  void Execute() override;

private:
  Entity* entity;
  std::vector<QPointF> points;
}

#endif // COMMAND_H
