#include "network.h"
#include <iostream>

NetWork::NetWork()
{

}

int NetWork::Send(const std::vector<std::shared_ptr<Command> > &commands) {
  for (auto it : commands) {
    command_.push(it);
  }
}

std::vector<std::shared_ptr<Command> > NetWork::Receive() {
  std::vector<std::shared_ptr<Command>> commands;
  std::chrono::milliseconds mill_sec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  while (!command_.empty() && command_.top()->valid_time_ <= mill_sec.count()) {
    commands.push_back(command_.top());
    command_.pop();
  }

  return commands;
}

PayLoad::PayLoad(const PayLoad &payload) {
  commands = payload.commands;
  client_id_ = payload.client_id_;
  command_seq_ = payload.command_seq_;
}

PayLoad &PayLoad::operator =(const PayLoad &payload) {
  commands = payload.commands;
  client_id_ = payload.client_id_;
  command_seq_ = payload.command_seq_;
}
