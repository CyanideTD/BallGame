#ifndef DIAGRAMPOLYGON_H
#define DIAGRAMPOLYGON_H

#include <graphicsitem.h>

class DiagramPolygon : public GraphicsItem {
public:
 explicit DiagramPolygon(const std::vector<QPointF>& points, const int id, const int index = 0) noexcept;

 void UpdateShape(const std::vector<QPointF>& shape);

 void SetBrush(const QBrush& brush);

 void SetPen(const QPen& pen);

public:
 QRectF boundingRect() const override;

 QPainterPath shape() const override;

protected:

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
  QPolygonF polygon_;

  QBrush brush_;

  QPen pen_;
};

#endif // DIAGRAMPOLYGON_H
