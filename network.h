#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <mutex>
#include <command.h>
#include <queue>

class PayLoad {
public:
  PayLoad() = default;
  PayLoad(const PayLoad& payload);
  PayLoad& operator =(const PayLoad& payload);

  std::vector<std::shared_ptr<SetStateCommand>> commands;
  int command_seq_ = 0;
  int client_id_ = 0;
};

class CommandCompare {
public:
  bool operator() (const std::shared_ptr<Command>& lhs, const std::shared_ptr<Command>&rhs) const
  {
    return lhs->valid_time_ > rhs->valid_time_;
  }
};

class NetWork {
public:
  NetWork();

  int Send(const std::vector<std::shared_ptr<Command>>& commands);
  std::vector<std::shared_ptr<Command>> Receive();

private:
  std::priority_queue<std::shared_ptr<Command>, std::vector<std::shared_ptr<Command>>, CommandCompare> command_;
  std::mutex lock_;
};

#endif // NETWORK_H
