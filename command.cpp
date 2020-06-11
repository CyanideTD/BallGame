#include "command.h"

Command::Command() {}

void SetTypeCommand::Execute() {
  entity->GetType()->SetType(type);
  QColor color;
  diagram_entity->GetPolygon()->SetColor(color);
}
