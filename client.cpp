#include "client.h"
#include <iostream>
#include <commandfactory.h>

Client::Client(const int client_id, DiagramScene *scene) {
  client_id_ = client_id;
  scene_ = scene;

  data_manager = std::make_shared<DataManager>();
  scene_->SetDataManager(data_manager);

  connect(
    scene_,
    SIGNAL(SendCommand(std::vector<std::shared_ptr<Command> >)),
    this,
    SLOT(ProcessCommands(std::vector<std::shared_ptr<Command> >)));
}

void Client::SetLag(const int millsec) {
  lag_ = millsec;
}

void Client::Spawn() {
  std::vector<QPointF> points;
  int factor = client_id_ == 1 ? 1 : -1;
  points.push_back(QPointF(0,0));
  points.push_back(QPointF(100 * factor,0));
  points.push_back(QPointF(100 * factor,100 * factor));
  points.push_back(QPointF(0,100 * factor));
  EntityType type = client_id_ == 1 ? EntityType::FIRST_PLAYER : EntityType::SECOND_PLAYER;
  std::shared_ptr<CreateCommand> create_command = std::make_shared<CreateCommand>(client_id_, points, type);
  ProcessCommands({create_command});
}

void Client::Move() {
  std::vector<QPointF> points;
  points.push_back(QPointF(0,0));
  points.push_back(QPointF(200,0));
  points.push_back(QPointF(200,200));
  points.push_back(QPointF(0,200));
  points.push_back(QPointF(300,200));

  std::shared_ptr<MoveCommand> move_command = std::make_shared<MoveCommand>(client_id_, points);
  ProcessCommands({move_command});
}

void Client::ProcessCommands(std::vector<std::shared_ptr<Command>> commands) {
  CommandArg arg;
  arg.manager = data_manager;
  arg.scene = scene_;

  std::vector<std::shared_ptr<Command>> send_commands;

  for (auto command : commands) {
    command->Init(arg);
    if (predication) {
     command->Execute();
    }
    command->client_id_ = client_id_;
    command->command_seq_ = client_seq_++;
    command_list.push_back(command);

    std::shared_ptr<Command> send_command = command->DeepCopy();
    send_command->client_id_ = client_id_;
    std::chrono::milliseconds millsec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    send_command->valid_time_ = millsec.count() + lag_;
    send_command->command_seq_ = command->command_seq_;
    send_commands.push_back(send_command);
  }

  emit SendCommands(send_commands);
}

void Client::GetState(PayLoad payload) {
  CommandArg arg;
  arg.manager = data_manager;
  arg.scene = scene_;
  if (payload.client_id_ != client_id_) {
    return;
  }

  auto it = command_list.begin();

  while (it != command_list.end() && (*it)->command_seq_ <= payload.command_seq_) {
    it = command_list.erase(it);
  }
  for (auto command : payload.commands) {
    command->Init(arg);
    command->Execute();
  }

  if (reconciliation) {
    for (auto it : command_list) {
      it->Init(arg);
      it->Execute();
    }
  }
}
