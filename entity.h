#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <QPointF>
#include <QObject>

enum class EntityType : uint32_t {
  FIRST_PLAYER = 1,
  SECOND_PLAYER = 2
};

class ShapeFeature {
public:
  void SetPoints(const std::vector<QPointF> points);
signals:
  void ShapeChanged(std::vector<QPointF> points);
private:
  std::vector<QPointF> points_;
};

class TypeFeature {
public:
  TypeFeature();

  EntityType GetType() const;

  void SetType(const EntityType& type);

signals:
  void TypeChanged(EntityType type);

private:
  EntityType type_;
};

class Entity {
public:
  Entity();

  ShapeFeature* GetShape() const;
  TypeFeature* GetType() const;

private:
  ShapeFeature shape_feature_;
  TypeFeature type_feature_;
};

#endif // ENTITY_H
