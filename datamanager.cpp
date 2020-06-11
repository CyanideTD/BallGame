#include "datamanager.h"

DataManager::DataManager() {
  entity_buffer_ = std::make_shared<Buffer<Entity>>();
}
