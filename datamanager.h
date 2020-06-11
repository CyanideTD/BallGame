#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>

#include <entity.h>


template<class T>
class Buffer {
 public:
  Buffer() = default;
  ~Buffer() = default;

  Buffer(const Buffer& buffer) = delete;
  Buffer& operator=(const Buffer& buffer) = delete;

  std::shared_ptr<T> GetSP(const int key);
  void PushSP(std::shared_ptr<T> value);

  int GetMapSize();
  std::vector<int> GetKeys();

  void Clear();
  void Clear(const int key);

  std::shared_ptr<T> PopSP(const int key);

  std::vector<std::shared_ptr<T>> PopSP();

 private:
  std::recursive_mutex map_mutex_;
  std::unordered_map<int, std::shared_ptr<T>> element_map_;
  std::vector<int> keys_;
};

class DataManager {
public:
  DataManager();
  std::shared_ptr<Buffer<Entity>> GetEntityBuffer();

private:
  std::shared_ptr<Buffer<Entity>> entity_buffer_;

};

#endif // DATAMANAGER_H
