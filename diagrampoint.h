#ifndef DIAGRAMPOINT_H
#define DIAGRAMPOINT_H

#include "graphicsitem.h"

class DiagramPoint : public GraphicsItem {
public:
  explicit DiagramPoint(const QPointF& pos, const int id, const int index);

  void SetPos(const QPointF& pos);

  QBrush GetBrush() const;

  void SetBrush(const QBrush& brush);

  QPen GetPen() const;
  void SetPen(const QBrush& pen);

public:
  QRectF boundingRect() const override;

  QPainterPath shape() const override;

protected:
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget = 0) override;

private:
  QBrush brush_;
  QPen pen_;
  qreal radius_;
};

#endif // DIAGRAMPOINT_H
