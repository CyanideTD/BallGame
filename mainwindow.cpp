#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  player_one_scene = new DiagramScene(this);
  player_two_scene = new DiagramScene(this);
  server_scene = new DiagramScene(this);
  ui->player_one_view->GetView()->setScene(player_one_scene);
  ui->player_two_view->GetView()->setScene(player_two_scene);
  ui->server_view->GetView()->setScene(server_scene);

  player_one = std::make_shared<Client>(1, player_one_scene);
  player_two = std::make_shared<Client>(2, player_two_scene);
  server = std::make_shared<Server>(server_scene);

  connect(
    server.get(),
    SIGNAL(SendState(PayLoad)),
    player_one.get(),
    SLOT(GetState(PayLoad)));

  connect(
    server.get(),
    SIGNAL(SendState(PayLoad)),
    player_two.get(),
    SLOT(GetState(PayLoad)));

  connect(
    player_one.get(),
    SIGNAL(SendCommands(std::vector<std::shared_ptr<Command>>)),
    server.get(),
    SLOT(GetCommand(std::vector<std::shared_ptr<Command> >)));

  connect(
    player_two.get(),
    SIGNAL(SendCommands(std::vector<std::shared_ptr<Command>>)),
    server.get(),
    SLOT(GetCommand(std::vector<std::shared_ptr<Command> >)));


  server_timer = new QTimer;
  server_timer->setInterval(100);
  connect(
    server_timer,
    SIGNAL(timeout()),
    server.get(),
    SLOT(RunOnce()));
  server_timer->start();

  qRegisterMetaType<PayLoad>("PayLoad");

  player_one->SetLag(2000);
  player_two->SetLag(4000);
  player_one->Spawn();
  player_two->Spawn();
  ui->player_one_view->GetView()->centerOn(0, 0);
  ui->player_two_view->GetView()->centerOn(0, 0);
  ui->server_view->GetView()->centerOn(0, 0);
  player_one->SetLag(4000);
  player_one->Move();
}

MainWindow::~MainWindow()
{
  delete ui;
}
