#include "diagrampolygon.h"

DiagramPolygon::DiagramPolygon(const std::vector<QPointF>& points, const int id, const int index) noexcept
  : GraphicsItem(id, index) {
  setFlag(GraphicsItemFlag::ItemIsSelectable);
  brush_.setColor(Qt::GlobalColor::blue);
  pen_.setWidth(1);
  UpdateShape(points);
}

void DiagramPolygon::UpdateShape(const std::vector<QPointF> &shape) {
  prepareGeometryChange();
  if (!polygon_.isEmpty()) {
    polygon_.clear();
  }
  QPolygonF polygon;
  for (unsigned int i = 0; i < shape.size(); i++) {
    polygon.append(shape[i]);
  }
  setPos(polygon.boundingRect().center());
  for (unsigned int i = 0; i < shape.size(); i++) {
    QPointF point = mapFromScene(shape[i]);
    polygon_.append(point);
  }
  update();
}

void DiagramPolygon::SetBrush(const QBrush &brush) {
  brush_ = brush;
  update();
}

void DiagramPolygon::SetPen(const QPen &pen) {
  pen_ = pen;
  update();
}

void DiagramPolygon::paint(
  QPainter *painter,
  const QStyleOptionGraphicsItem *option,
  QWidget *) {
  brush_.setStyle(
      isSelected()? Qt::Dense4Pattern : Qt::SolidPattern);
  painter->setPen(pen_);
  painter->setBrush(brush_);
  painter->drawPolygon(polygon_);
}

QRectF DiagramPolygon::boundingRect() const {
  const qreal pen_width_zero = qreal(0.00000001);
  QPainterPathStroker graphic_outline;
  graphic_outline.setCapStyle(
      pen_.capStyle());
  if (pen_.widthF() <= 0.0f) {
    graphic_outline.setWidth(pen_width_zero);
  } else {
    graphic_outline.setWidth(pen_.widthF());
  }
  graphic_outline.setJoinStyle(
      pen_.joinStyle());
  graphic_outline.setMiterLimit(
      pen_.miterLimit());

  QPainterPath polygon;
  polygon.addPolygon(polygon_);
  QPainterPath path_outline = graphic_outline.createStroke(polygon);
  return path_outline.controlPointRect();
}

QPainterPath DiagramPolygon::shape() const {
  QPainterPath polygon;
  polygon.addPolygon(polygon_);
  return polygon;
}
