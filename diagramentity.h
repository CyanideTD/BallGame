#ifndef DIAGRAMENTITY_H
#define DIAGRAMENTITY_H

#include <entity.h>
#include <diagrampolygon.h>
#include <diagrampoint.h>
#include <diagram.h>
#include <QGraphicsScene>

class DiagramEntity : public Diagram  {
public:
  explicit DiagramEntity(const int id, const std::vector<QPointF>& points, const EntityType type) noexcept;
  ~DiagramEntity() = default;
public:
  DiagramPolygon *GetPolygon() const;

  std::vector<DiagramPoint *> GetPoint() const;

  void OnTypeChanged(const EntityType& type);

  void OnShapeChanged(const int id, const std::vector<QPointF>& points);

  void Draw(QGraphicsScene* scene);

private:

  DiagramPolygon* polygon = nullptr;
  std::vector<DiagramPoint*> points_;
};

#endif // DIAGRAMENTITY_H
