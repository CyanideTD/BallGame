#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>

class GraphicsItem : public QGraphicsItem {
public:
  GraphicsItem(const int id, const int index = 0);

  void SetId(const int id);
  void SetIndex(const int index);

  int GetId() const;
  int GetIndex() const;

private:
  int entity_id_ = 0;
  int diagram_item_index_ = 0;
};

#endif // GRAPHICSITEM_H
