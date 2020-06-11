#include "graphicsitem.h"

GraphicsItem::GraphicsItem(const int id, const int index) {
  SetId(id);
  SetIndex(index);
}

void GraphicsItem::SetId(const int id) {
  entity_id_ = id;
}

void GraphicsItem::SetIndex(const int index) {
  diagram_item_index_ = index;
}

int GraphicsItem::GetId() const {
  return entity_id_;
}

int GraphicsItem::GetIndex() const {
  return diagram_item_index_;
}
