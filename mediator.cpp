#include "mediator.h"

void EntityMediator::RegisterDiagram(std::shared_ptr<Diagram> diagram_entity) {
  diagram_entity_ = std::dynamic_pointer_cast<DiagramEntity>(diagram_entity);
}

void EntityMediator::RegisterEntity(std::shared_ptr<BaseEntity> entity) {
  entity_ = std::dynamic_pointer_cast<Entity>(entity);
}

void EntityMediator::NotifyTypeChanged() {
  diagram_entity_->OnTypeChanged(entity_->GetType()->GetType());
}

void EntityMediator::NotifyShapeChanged() {
  diagram_entity_->OnShapeChanged(entity_->GetID(), entity_->GetShape()->GetPoints());
}
