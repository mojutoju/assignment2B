#include "Project.h"

Project::Project(std::string name, int id, int multiplicity, int supervisor) : name(name), id(id), multiplicity(multiplicity), supervisor(supervisor) {}

int Project::getID() const {
return id;
}


std::string Project::getName() const {
return name;
}

int Project::getMultiplicity() const {
return multiplicity;
}

int Project::getSupervisor() const {
return supervisor;
}