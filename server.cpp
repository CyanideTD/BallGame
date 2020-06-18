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
  std::map<int, int> client_seq;
  std::set<int> influence_id;
  std::vector<std::shared_ptr<Command>> commands = connect_.Receive();
  for (auto it : commands) {
    it->Init(arg);
    it->Execute();
    std::vector<int> ids = it->GetRelateIds();
    for (auto id : ids) {
      influence_id.insert(id);
    }
    if (client_seq.count(it->client_id_) == 0) {
      client_seq.insert(std::make_pair(it->client_id_, it->command_seq_));
    } else {
      int seq = client_seq[it->client_id_];
      client_seq[it->client_id_] = std::max(seq, it->command_seq_);
    }
  }

  for (auto client : client_seq) {
    PayLoad payload;
    payload.client_id_ = client.first;
    payload.command_seq_ = client.second;

    for (auto id : influence_id) {
      std::shared_ptr<Entity> entity = manager_->GetEntityBuffer()->GetSP(id);
      if (entity) {
        std::shared_ptr<SetStateCommand> command = std::make_shared<SetStateCommand>(
          entity->GetID(), entity->GetShape()->GetPoints(), entity->GetType()->GetType());
        payload.commands.push_back(command);
      } else {
          std::cout << manager_->GetEntityBuffer()->GetMapSize() << std::endl;
        std::cout << "Error" << std::endl;
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
