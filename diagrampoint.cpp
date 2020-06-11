
#include <QPainter>
#include "diagrampoint.h"

DiagramPoint::DiagramPoint(const QPointF &pos, const int id, const int index) {
  GraphicsItem(id, index);
  setFlag(GraphicsItemFlag::ItemIsSelectable);
  brush_.setColor(Qt::GlobalColor::red);
  pen_.setWidth(1);
  SetPos(pos);
}

void DiagramPoint::SetPos(const QPointF &pos) {
  prepareGeometryChange();
  setPos(pos);
  update();
}

QBrush DiagramPoint::GetBrush() const {
  return brush_;
}

void DiagramPoint::SetBrush(const QBrush &brush) {
  brush_ = brush;
  update();
}

QPen DiagramPoint::GetPen() const {
  return brush_;
}

void DiagramPoint::SetPen(const QBrush &pen) {
  prepareGeometryChange();
  pen_ = pen;
  update();
}

QRectF DiagramPoint::boundingRect() const {
  return QRectF(-radius_, radius_, 2*radius_, 2*radius_ );
}

QPainterPath DiagramPoint::shape() const {
  QPainterPath path;
  path.addEllipse(this->boundingRect());
  return path;
}

void DiagramPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->setBrush(brush_);
  painter->setPen(pen);
  painter->drawEllipse(this->boundingRect());
}