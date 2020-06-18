#include "entity.h"
#include <mediator.h>

Entity::Entity(const int id, const std::vector<QPointF> &points, EntityType type) : BaseEntity(id) {
  shape_feature_.SetPoints(points);
  type_feature_.SetType(type);
}

ShapeFeature *Entity::GetShape() {
  return &shape_feature_;
}

TypeFeature *Entity::GetType() {
  return &type_feature_;
}

void Entity::SetMediator(std::shared_ptr<EntityMediator> mediator) {
  mediator_ = mediator;
}

std::shared_ptr<EntityMediator> Entity::GetMediator() {
  return mediator_;
}

void ShapeFeature::SetPoints(const std::vector<QPointF> points) {
  points_ = points;
}

EntityType TypeFeature::GetType() const {
  return type_;
}

void TypeFeature::SetType(const EntityType &type) {
  type_ = type;
}
