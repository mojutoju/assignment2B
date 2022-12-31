#include <string>

class Project {
private:
std::string name;
int multiplicity;
int supervisor;
int id;

public:
Project(std::string name, int multiplicity, int id ,int supervisor);
std::string getName() const;
int getMultiplicity() const;
int getID() const;
int getSupervisor() const;
};