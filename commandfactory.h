#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H


class CommandFactory {
public:
  CommandFactory();
  virtual ~CommandFactory();
  virtual void GenerateCommand() = 0;
};

#endif // COMMANDFACTORY_H
