#include <QPainter>
#include <QGraphicsScene>
#include "diagramentity.h"

DiagramEntity::DiagramEntity(const int id, const std::vector<QPointF> &points, const EntityType type) noexcept {
  polygon = new DiagramPolygon(points, id, 0);
  for (unsigned int i = 0; i < points.size(); i++) {
    DiagramPoint* point = new DiagramPoint(points[i], id, i);
    points_.push_back(point);
  }
  OnTypeChanged(type);
}

DiagramPolygon *DiagramEntity::GetPolygon() const {
  return polygon;
}

std::vector<DiagramPoint *> DiagramEntity::GetPoint() const {
  return points_;
}

void DiagramEntity::OnTypeChanged(const EntityType& type) {
  QBrush brush;
  QPen pen;
  switch (type) {
    case EntityType::FIRST_PLAYER:
        brush.setColor(Qt::GlobalColor::red);
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        pen.setColor(Qt::GlobalColor::red);
      break;
    case EntityType::SECOND_PLAYER:
      brush.setColor(Qt::GlobalColor::blue);
      brush.setStyle(Qt::BrushStyle::SolidPattern);
      pen.setColor(Qt::GlobalColor::blue);
    default:
      break;
  }

  if (nullptr != polygon) {
    polygon->SetBrush(brush);
    polygon->SetPen(pen);
  }

  brush.setColor(Qt::GlobalColor::black);
  for (auto it : points_) {
    it->SetBrush(brush);
    it->SetPen(pen);
   }
}

void DiagramEntity::OnShapeChanged(const int id, const std::vector<QPointF> &points) {
  if (nullptr != polygon) {
    polygon->UpdateShape(points);
  }
  unsigned int index = 0;

  for (; index < points.size(); index++) {
    if (index < points_.size()) {
      points_[index]->SetPos(points[index]);
    } else {
      DiagramPoint* point = new DiagramPoint(points[index], id, index);
      points_.push_back(point);
    }
  }

  auto it = points_.begin() + index;
  while (it != points_.end()) {
    auto scene = (*it)->scene();
    if (nullptr != scene) {
      scene->removeItem(*it);
    }
    it = points_.erase(it);
  }
}

void DiagramEntity::Draw(QGraphicsScene *scene) {
  if (scene != nullptr) {
    scene->addItem(polygon);
  }

  for (auto it : points_) {
    scene->addItem(it);
  }
}
