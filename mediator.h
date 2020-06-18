#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <memory>

#include <QObject>

#include <diagramentity.h>
#include <entity.h>

class Mediator : public QObject {
  Q_OBJECT
public:
  virtual void RegisterDiagram(std::shared_ptr<Diagram>) = 0;
  virtual void RegisterEntity(std::shared_ptr<BaseEntity>) = 0;
};

class EntityMediator : public Mediator {
public:
  void RegisterDiagram(std::shared_ptr<Diagram>) override;
  void RegisterEntity(std::shared_ptr<BaseEntity>) override;

public:
  void NotifyTypeChanged();
  void NotifyShapeChanged();

private:
  std::shared_ptr<DiagramEntity> diagram_entity_;
  std::shared_ptr<Entity> entity_;
};

#endif // MEDIATOR_H
