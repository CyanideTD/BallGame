#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <set>
#include <entity.h>


template<class T>
class Buffer {
 public:
  Buffer() = default;
  ~Buffer() = default;

  Buffer(const Buffer& buffer) = delete;
  Buffer& operator=(const Buffer& buffer) = delete;

  std::shared_ptr<T> GetSP(const int key) {
    std::lock_guard<std::recursive_mutex> lock_guard(map_mutex_);
    return element_map_[key];
  }

  void PushSP(std::shared_ptr<T> value) {
    std::lock_guard<std::recursive_mutex> lock_guard(map_mutex_);
    element_map_[value->GetID()] = value;
    keys_.insert(value->GetID());
  }

  int GetMapSize() {
    std::lock_guard<std::recursive_mutex> lock_guard(map_mutex_);
    return element_map_.size();
  }
  std::vector<int> GetKeys();

  void Clear();
  void Clear(const int key);

  std::shared_ptr<T> PopSP(const int key);

  std::vector<std::shared_ptr<T>> PopSP();

 private:
  std::recursive_mutex map_mutex_;
  std::unordered_map<int, std::shared_ptr<T>> element_map_;
  std::set<int> keys_;
};

class DataManager {
public:
  DataManager();
  std::shared_ptr<Buffer<Entity>> GetEntityBuffer() {return entity_buffer_;}

private:
  std::shared_ptr<Buffer<Entity>> entity_buffer_;

};

#endif // DATAMANAGER_H
