#ifndef CLIENT_H
#define CLIENT_H

#include <datamanager.h>
#include <diagramscene.h>
#include <network.h>
#include <deque>
#include <command.h>

class Client : public QObject {
  Q_OBJECT
public:
  Client(const int client_id, DiagramScene* scene);
  virtual ~Client() {}

public:
  void ProcessServerMessage();

  void SetLag(const int millsec);

  void Spawn();

  void Move();

  int GetSeq() { return client_seq_; }

  int GetClientID() { return client_id_; }

signals:
  void SendCommands(std::vector<std::shared_ptr<Command>>);

public slots:
  void GetState(PayLoad payload);
  void ProcessCommands(std::vector<std::shared_ptr<Command>> commands);

private:
  DiagramScene* scene_ = nullptr;
  std::shared_ptr<DataManager> data_manager;
  std::vector<std::shared_ptr<Command>> command_list;
  int client_seq_ = 0;
  int client_id_ = 0;
  uint32_t lag_ = 1000;
  bool predication = true;
  bool reconciliation = true;
};

#endif // CLIENT_H
