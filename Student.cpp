#include "Student.h"

Student::Student(std::string name, std::vector<int> preferences) : name(name), preferences(preferences) {}

std::string Student::getName() const {
return name;
}

std::vector<int> Student::getPreferences() const {
return preferences;

}