#include <string>

class Supervisor {
private:
std::string name;
int load;
int id_;

public:
Supervisor(std::string name, int load);
std::string getName() const;
int getLoad() const;
int getID() const;
};