
#include <QPainter>
#include "diagrampoint.h"

DiagramPoint::DiagramPoint(const QPointF &pos, const int id, const int index)
  : GraphicsItem(id, index, ItemType::ITEM_TYPE_POINT) {
  setFlag(GraphicsItemFlag::ItemIsSelectable);
  brush_.setColor(Qt::GlobalColor::black);
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
  return pen_;
}

void DiagramPoint::SetPen(const QPen &pen) {
  prepareGeometryChange();
  pen_ = pen;
  update();
}

QRectF DiagramPoint::boundingRect() const {
  return QRectF(-radius_, -radius_, 2*radius_, 2*radius_ );
}

QPainterPath DiagramPoint::shape() const {
  QPainterPath path;
  path.addEllipse(this->boundingRect());
  return path;
}

void DiagramPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  brush_.setStyle(
      isSelected()? Qt::Dense4Pattern : Qt::SolidPattern);
  painter->setBrush(brush_);
  painter->setPen(pen_);
  painter->drawEllipse(this->boundingRect());
}
