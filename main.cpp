#include <iostream>
#include <vector>
#include <unordered_map>
#include<algorithm>
#include<fstream>
#include<sstream>
#include "Student.h"
#include "Project.h"
#include "Supervisor.h"


// Allocate projects to students using the algorithm described in the prompt
std::unordered_map<std::string, int> allocateProjects(const std::vector<Student>& students, std::vector<Project>& projects,
std::vector<Supervisor>& supervisors) {
std::unordered_map<std::string, int> allocation; // Maps student names to project IDs
std::unordered_map<int, int> supervisorAllocations; // Maps supervisor IDs to the number of projects they have been allocated
std::unordered_map<int, int> projectAllocations; // Maps project IDs to the number of students they have been allocated

// Initialize the supervisor and project allocation counts
for (const auto& supervisor : supervisors) {
supervisorAllocations[supervisor.getID()] = 0;
}
for (const auto& project : projects) {
projectAllocations[project.getID()] = 0;
}

// Process each student one by one
for (const auto& student : students) {
bool allocated = false; // Flag to track if a project has been allocated to the student
int allocatedProject; // Keep track of the allocated project to check for higher preference projects later
for (const auto& preference : student.getPreferences()) {
// Allocate student to their most preferred project that is still available
Project& project = projects[preference - 1];
// Need to pass a reference to project instead of a copy
Supervisor& supervisor = supervisors[project.getSupervisor() - 1];
if (project.getMultiplicity() > 0 && supervisor.getLoad() > 0) {
allocation[student.getName()] = preference;
allocatedProject = preference;
project.getMultiplicity();
supervisor.getLoad();
supervisorAllocations[supervisor.getID()]++;
projectAllocations[project.getID()]++;
allocated = true;
break;
}
}


  // If all projects on the student's preference list are full, allocate an arbitrary available project to them
if (!allocated) {
  for (const auto& project : projects) {
    if (project.getMultiplicity() > 0 && supervisors[project.getSupervisor() - 1].getLoad() > 0) {
      allocation[student.getName()] = project.getID(); 
      allocatedProject = project.getID();
      project.getMultiplicity();
      supervisors[project.getSupervisor() - 1].getLoad();
      supervisorAllocations[project.getSupervisor()]++;
      projectAllocations[project.getID()]++;
      break;
    }
  }
}


// Check if any of the student's higher preference projects are still available
bool higherPreferenceAvailable = false;
for (const auto& preference : student.getPreferences()) {
if (allocation[student.getName()] != preference && projects[preference - 1].getMultiplicity() > 0 &&
supervisors[projects[preference - 1].getSupervisor() - 1].getLoad() > 0) {
higherPreferenceAvailable = true;
break;
}
}
if (higherPreferenceAvailable) {
std::cout << "Student " << student.getName() << " is allocated project " << allocation[student.getName()]
<< " but project " << allocatedProject << " is higher on their preference list and is available" << std::endl;
}

for (const auto& project : projects) {
if (project.getMultiplicity() < projectAllocations[project.getID()]) {
std::cout << "Project " << project.getID() << " has multiplicity " << project.getMultiplicity()
<< " but is allocated to " << projectAllocations[project.getID()] << " students" << std::endl;
}
}


// Check for other students who have been allocated a project that is lower on their preference list than this student's allocated project
for (const auto& otherStudent : students) {
  if (allocation.count(otherStudent.getName()) > 0) {
    int otherAllocatedProject = allocation[otherStudent.getName()];
    if (std::find(otherStudent.getPreferences().begin(), otherStudent.getPreferences().end(), otherAllocatedProject) <
        std::find(otherStudent.getPreferences().begin(), otherStudent.getPreferences().end(), allocatedProject)) {
      std::cout << "Student " << student.getName() << " is allocated project " << allocatedProject
                << " but project " << otherAllocatedProject << " is higher on their preference list";

                  std::cout << ", while student " << otherStudent.getName() << " is allocated project " << otherAllocatedProject
                << " but project " << allocatedProject << " is higher on their preference list" << std::endl;
    }
  }
}
}







// Check if any projects or supervisors have been allocated more than they can handle
for (const auto& student : students) {
if (allocation.count(student.getName()) > 1) {
std::cout << "Student " << student.getName() << " is allocated more than one project" << std::endl;
}
}
for (const auto& supervisor : supervisors) {
if (supervisorAllocations[supervisor.getID()] > supervisor.getLoad()) {
std::cout << "Supervisor " << supervisor.getName() << " has load " << supervisor.getLoad()
<< " but is allocated " << supervisorAllocations[supervisor.getID()] << " projects" << std::endl;
}
}
for (const auto& project : projects) {
if (project.getMultiplicity() < projectAllocations[project.getID()]) {
std::cout << "Project " << project.getID() << " has multiplicity " << project.getMultiplicity()
<< " but is allocated to " << projectAllocations[project.getID()] << " students" << std::endl;
}
}



// Check if the allocation is legally and locally optimal
bool legallyOptimal = true;
bool locallyOptimal = true;

for (const auto& student : students) {
// Check if the allocation is legally optimal
if (allocation[student.getName()] != student.getPreferences()[0]) {
legallyOptimal = false;
}

// Check if the allocation is locally optimal
bool higherPreferenceAvailable = false;
for (const auto& preference : student.getPreferences()) {
if (allocation[student.getName()] != preference && projects[preference - 1].getMultiplicity() > 0 &&
supervisors[projects[preference - 1].getSupervisor() - 1].getLoad() > 0) {
higherPreferenceAvailable = true;
break;
}
}
if (higherPreferenceAvailable) {
locallyOptimal = false;
}
}

if (!legallyOptimal) {
std::cout << "Allocation is not legally optimal" << std::endl;
}

if (!locallyOptimal) {
std::cout << "Allocation is not locally optimal" << std::endl;
}

return allocation;



}




// Read input from the given files and store the data in the provided vectors
void readInput(const std::string& staffFile, const std::string& projectFile, const std::string& studentFile,
std::vector<Student>& students, std::vector<Project>& projects, std::vector<Supervisor>& supervisors) {
// Read staff data from the input file
std::ifstream staffInput(staffFile);
std::string line;
while (std::getline(staffInput, line)) {
std::istringstream lineStream(line);
std::string name;
int load;
lineStream >> name >> load;
supervisors.emplace_back(name, load);
}

// Read project data from the input file
std::ifstream projectInput(projectFile);
while (std::getline(projectInput, line)) {
std::istringstream lineStream(line);
std::string title;
int id, supervisor, multiplicity;
lineStream >> title >> id >> supervisor >> multiplicity;
projects.emplace_back(title, id, supervisor, multiplicity);
}

// Read student data from the input file
std::ifstream studentInput(studentFile);
while (std::getline(studentInput, line)) {
std::istringstream lineStream(line);
std::string name;
std::vector<int> preferences;
lineStream >> name;
int preference;
while (lineStream >> preference) {
preferences.push_back(preference);
}
students.emplace_back(name, preferences);
}
}

// Write the given allocation to a text file
void writeAllocation(const std::unordered_map<std::string, int>& allocation, const std::string& outputFile) {
std::ofstream output(outputFile);
for (const auto& entry : allocation) {
output << entry.first << " " << entry.second << std::endl;
}
}

// Calculate the preference score of a student for a given project
int getPreferenceScore(const std::vector<Student>& students, const std::string& studentName, int projectID) {
// Find the Student object with the given name
auto it = std::find_if(students.begin(), students.end(), [&](const Student& s) { return s.getName() == studentName; });
if (it == students.end()) {
std::cerr << "Error: Student " << studentName << " not found" << std::endl;
return 0;
}

// Find the preference of the student for the given project
const auto& preferences = it->getPreferences();
int preference = std::find(preferences.begin(), preferences.end(), projectID) - preferences.begin();
return preference + 1; // Return the 1-indexed preference
}

// Check if the given allocation is legal and locally optimal
void checkAllocation(const std::vector<Student>& students, const std::vector<Project>& projects,
const std::vector<Supervisor>& supervisors,const std::unordered_map<std::string, int>& allocation)
 {

// Check that each student is allocated to at most one project
for (const auto& student : students) {
int allocatedProjects = 0;
for (const auto& pair : allocation) {
if (pair.first == student.getName()) {
++allocatedProjects;
}
}
if (allocatedProjects > 1) {
std::cout << "Student " << student.getName() << " is allocated more than one project" << std::endl;
}
}
  
// Check that each supervisor's allocated load does not exceed their maximum load
for (const auto& supervisor : supervisors) {
int allocatedLoad = 0;
for (const auto& project : projects) {
if (project.getSupervisor() == supervisor.getID()) {
allocatedLoad += project.getMultiplicity();
}
}
if (allocatedLoad > supervisor.getLoad()) {
std::cout << "Supervisor " << supervisor.getName() << " has load " << supervisor.getLoad()
<< " but is allocated " << allocatedLoad << " projects" << std::endl;
}
}

// Check that each student is allocated their most preferred project that is still available
for (const auto& student : students) {
bool allocated = false;
for (const auto& preference : student.getPreferences()) {
if (allocation.at(student.getName()) == preference) {
allocated = true;
break;
}
}
if (!allocated) {
std::cout << "Student " << student.getName() << " is not allocated their most preferred available project" << std::endl;
}
}
}


int main(int argc, char* argv[]) {


 if (argc != 5) {
    std::cerr << "Error: Incorrect number of arguments provided." << std::endl;
    return 1;
  }

  // Parse the command line arguments
  std::string staffFile = argv[1];
  std::string projectFile = argv[2];
  std::string studentFile = argv[3];
  std::string allocFile = argv[4];


std::vector<Student> students;
std::vector<Project> projects;
std::vector<Supervisor> supervisors;

// Add students, projects, and supervisors to their respective vectors
// Add students

students.push_back(Student("stu1", {1, 2, 3, 4}));
students.push_back(Student("stu2", {2, 3, 4, 1}));
students.push_back(Student("stu3", {2, 4, 1, 3}));
students.push_back(Student("stu4", {4, 1, 2, 3}));


// Add projects
projects.push_back(Project("helloworld", 1, 1, 0));
projects.push_back(Project("easy easy", 2, 2, 1));
projects.push_back(Project("a piece of cake", 3, 3, 1));
projects.push_back(Project("a login page", 4, 4, 1));

// Add supervisors
supervisors.push_back(Supervisor("staff1", 1));
supervisors.push_back(Supervisor("staff2", 1));
supervisors.push_back(Supervisor("staff3", 1));
supervisors.push_back(Supervisor("staff4", 1));

// Allocate projects to students
std::unordered_map<std::string, int> allocation = allocateProjects(students, projects, supervisors);

int score = 0; // Score of the allocation
int calculatedScore = 0; // Calculated Score

// Create a vector of pairs to sort the allocation by student name
std::vector<std::pair<std::string, int>> allocationPairs;
for (const auto& pair : allocation) {
std::string student = pair.first;
int project = pair.second;
allocationPairs.emplace_back(student, project);

}

// Sort the allocation by student name
std::sort(allocationPairs.begin(), allocationPairs.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
return a.first < b.first;
});

// Print the allocation of each student in ascending order
std::cout<<"Allocation Results"<< std:: endl;
for (const auto& pair : allocationPairs) {
std::string student = pair.first;
int project = pair.second;
std::cout << student << " " << project << std::endl;
}

// Calculate the score of the allocation

for (const auto& student : students) {
  std::string name = student.getName();
  int allocatedProject = allocation[name];
  std::vector<int> preferences = student.getPreferences();

 for (int i = 0; i < 4; i++) {
if (student.getPreferences()[i] == allocatedProject) {
score += (4 - i);
break;
}
}

}


// Calculate the score of the allocation
for (const auto& student : students) {
std::string name = student.getName();
int allocatedProject = allocation[name];
std::vector<int> preferences = student.getPreferences();

for (int i = 0; i < 4; i++) {
if (student.getPreferences()[i] == allocatedProject) {
calculatedScore += (4 - i);
break;
}
}
}

if (calculatedScore == score) {
std::cout << "Score is correct" << std::endl;
} else {
std::cout << "Score is incorrect" << std::endl;
}

// Print out the score
std::cout << "Score: " << score << std::endl;



std::ofstream allocStream(allocFile);


  // Write the allocation result to the output file
  for (const auto& pair : allocationPairs) {
    std::string student = pair.first;
    int project = pair.second;
    
    allocStream << student << " " << project << std::endl;
  }


// Write the score to the output file
allocStream << "Score: " << score << std::endl;
  checkAllocation(students, projects, supervisors, allocation);

  // Close the output file
  allocStream.close();
  


return 0;
}