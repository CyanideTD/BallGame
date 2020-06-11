#ifndef DIAGRAMENTITY_H
#define DIAGRAMENTITY_H

#include <diagrampolygon.h>
#include <diagrampoint.h>
#include <entity.h>

class DiagramEntity {
public:
  explicit DiagramEntity(const int id, const std::vector<QPointF>& points, const EntityType type) noexcept;
  ~DiagramEntity() = default;
public:
  DiagramPolygon *GetPolygon() const;

  std::vector<DiagramPoint *> GetPoint() const;

public slots:
  void OnTypeChanged(const EntityType& type);

  void OnShapeChanged(const int id, const std::vector<QPointF>& points);

private:

  DiagramPolygon* polygon = nullptr;
  std::vector<DiagramPoint*> points_;
};

#endif // DIAGRAMENTITY_H
