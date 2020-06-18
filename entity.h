#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include <QPointF>
#include <QObject>
#include <baseentity.h>

class Mediator;
class EntityMediator;

enum class EntityType : uint32_t {
  FIRST_PLAYER = 1,
  SECOND_PLAYER = 2
};

class ShapeFeature : public QObject {
  Q_OBJECT
public:
  ShapeFeature() = default;

  void SetPoints(const std::vector<QPointF> points);

  std::vector<QPointF> GetPoints() { return points_; }

private:
  std::vector<QPointF> points_;
};

class TypeFeature : public QObject {
  Q_OBJECT
public:
  TypeFeature() = default;

  EntityType GetType() const;

  void SetType(const EntityType& type);

private:
  EntityType type_;
};

class Entity : public BaseEntity {
public:
  explicit Entity(const int id, const std::vector<QPointF>& points, EntityType type);

  ShapeFeature *GetShape();
  TypeFeature *GetType();

  void SetMediator(std::shared_ptr<EntityMediator> mediator);
  std::shared_ptr<EntityMediator> GetMediator();

private:
  ShapeFeature shape_feature_;
  TypeFeature type_feature_;
  std::shared_ptr<EntityMediator> mediator_;
};

#endif // ENTITY_H
