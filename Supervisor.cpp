#include "Supervisor.h"

Supervisor::Supervisor(std::string name, int load) : name(name), load(load) {}

std::string Supervisor::getName() const {
return name;
}

int Supervisor::getLoad() const {
return load;
}

int Supervisor::getID() const { // Add this function definition
  return id_;
}