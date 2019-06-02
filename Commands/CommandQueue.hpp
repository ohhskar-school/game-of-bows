#ifndef RC_COMMANDQUEUE
#define RC_COMMANDQUEUE

#include "Command.hpp"
#include <queue>

class CommandQueue{
  public:
    void push(const Command&);
    Command pop();
    bool isEmpty() const;

    private:
    std::queue<Command> mQueue;
};

#endif