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

  template<typename T>
  void SendCommand(std::shared_ptr<T> command) {
    CommandArg arg;
    arg.manager = data_manager;
    arg.scene = scene_;
    command->Init(arg);
    if (predication) {
      command->Execute();
    }
    command->Execute();
    command->client_id_ = client_id_;
    command->command_seq_ = client_seq_++;
    command_list.push_back(command);

    std::shared_ptr<T> send_command = std::make_shared<T>(*command.get());
    send_command->client_id_ = client_id_;
    std::chrono::milliseconds millsec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    send_command->valid_time_ = millsec.count() + lag_;
    send_command->command_seq_ = command->command_seq_;
    SendCommands({send_command});
  }

signals:
  void SendCommands(std::vector<std::shared_ptr<Command>>);

public slots:
  void GetState(PayLoad payload);

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
