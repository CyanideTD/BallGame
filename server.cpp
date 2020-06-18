#include <set>
#include <map>
#include <vector>
#include <unistd.h>
#include <command.h>
#include <iostream>
#include "server.h"

void Server::RunOnce() {
  CommandArg arg;
  arg.manager = manager_;
  arg.scene = scene_;
  std::set<int> influence_id;
  std::vector<std::shared_ptr<Command>> commands = connect_.Receive();
  for (auto it : commands) {
    it->Init(arg);
    it->Execute();
    std::vector<int> ids = it->GetRelateIds();
    for (auto id : ids) {
      influence_id.insert(id);
    }
    if (clients_.count(it->client_id_) == 0) {
      clients_.insert(std::make_pair(it->client_id_, it->command_seq_));
    } else {
      int seq = clients_[it->client_id_];
      clients_[it->client_id_] = std::max(seq, it->command_seq_);
    }
  }

  for (auto client : clients_) {
    PayLoad payload;
    payload.client_id_ = client.first;
    payload.command_seq_ = client.second;

    for (auto id : influence_id) {
      std::shared_ptr<Entity> entity = manager_->GetEntityBuffer()->GetSP(id);
      if (entity) {
        std::shared_ptr<SetStateCommand> command = std::make_shared<SetStateCommand>(
          entity->GetID(), entity->GetShape()->GetPoints(), entity->GetType()->GetType());
        payload.commands.push_back(command);
      }
    }

    emit SendState(payload);
  }
}

void Server::GetCommand(std::vector<std::shared_ptr<Command> > commands) {
  connect_.Send(commands);
}

Server::Server(DiagramScene *scene) {
  manager_ = std::make_shared<DataManager>();
  scene_ = scene;
}
