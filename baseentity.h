#ifndef BASEENTITY_H
#define BASEENTITY_H

class BaseEntity {
public:
  BaseEntity(const int id) { id_ = id; }
  virtual ~BaseEntity() {}
  int GetID() { return id_; }
private:
  int id_ = 0;
};

#endif // BASEENTITY_H
