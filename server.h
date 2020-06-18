#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <client.h>

class Server : public QObject {
  Q_OBJECT
public:
  Server(DiagramScene* scene);

signals:
  void SendState(PayLoad);

public slots:
  void RunOnce();
  void GetCommand(std::vector<std::shared_ptr<Command>> commands);

private:
  NetWork connect_;
  std::shared_ptr<DataManager> manager_;
  DiagramScene* scene_ = nullptr;
  bool stop_flag_ = false;
};

#endif // SERVER_H
