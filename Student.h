#include <string>
#include <vector>

class Student {
private:
std::string name;
std::vector<int> preferences;

public:
Student(std::string name, std::vector<int> preferences);
std::string getName() const;
std::vector<int> getPreferences() const;
};