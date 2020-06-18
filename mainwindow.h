#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QTimer>
#include <QMainWindow>
#include <client.h>
#include <server.h>
#include <diagramscene.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  DiagramScene* player_one_scene = nullptr;
  DiagramScene* player_two_scene = nullptr;
  DiagramScene* server_scene = nullptr;

  std::shared_ptr<Client> player_one;
  std::shared_ptr<Client> player_two;
  std::shared_ptr<Server> server;
  QTimer* server_timer;
};

#endif // MAINWINDOW_H
