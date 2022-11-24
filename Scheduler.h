
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <map>
#include <string>

class Scheduler {
  private:
    std::map<std::string, unsigned long> previousCalls;

  public:
    void every(unsigned long interval, std::string id, void (*f)());
};

#endif
