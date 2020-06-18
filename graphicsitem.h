#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>

enum class ItemType : uint32_t {
  ITEM_TYPE_UNKNOWN = 0,
  ITEM_TYPE_POINT = 1,
  ITEM_TYPE_POLYGON = 2,
};

class GraphicsItem : public QGraphicsItem {
public:

  GraphicsItem(const int id, const int index = 0, ItemType type = ItemType::ITEM_TYPE_UNKNOWN);

  void SetId(const int id);
  void SetIndex(const int index);

  int GetId() const;
  int GetIndex() const;

  void SetType(ItemType type);
  ItemType GetType();

private:
  int entity_id_ = 0;
  int diagram_item_index_ = 0;
  ItemType type_;
};

#endif // GRAPHICSITEM_H
