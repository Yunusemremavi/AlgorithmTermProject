#include "examScheduling.h"

static string day_of_array[]{ "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };

void readClassList(const std::string& filename, std::vector<classLists>& classes)
{
	ifstream file(filename);

    if (!file.is_open()) {
        throw myException{};
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, professorName, courseID, token;
        int studentID, examDuration;

        std::getline(iss, id, ',');
        std::getline(iss, professorName, ',');
        std::getline(iss, courseID, ',');
        std::getline(iss, token, ',');
        studentID = std::stoi(id);
        examDuration = std::stoi(token);

        classes.emplace_back(studentID, professorName, courseID, examDuration);
    }

    file.close();
}

void readRoomCapacities(const std::string& filename, std::vector<roomList>& rooms)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw myException{};
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string roomID, token;
        int capacity;

        std::getline(iss, roomID, ',');
        std::getline(iss, token, ',');
        capacity = std::stoi(token);

        rooms.emplace_back(roomID, capacity);
    }

    file.close();
}

map<string, int> readClassesfromVector(vector<classLists>& vec)
{
    map<string, int> mapClass;
    int count{};

    for (auto& i : vec) {
        if (mapClass.find(i.courseID) == mapClass.end()) {
            mapClass[i.courseID] = count++;
        }
    }

    return mapClass;
}

myGraph generateGraphForClasses(map<string, int> mymap, vector<classLists>& vec)
{
    myGraph temp = mymap.size();

    for (auto i = vec.begin(); i != vec.end(); ++i) {
        for (auto j = i + 1; j != vec.end(); ++j) {
            if (i->studentID == j->studentID) {
                temp.addAdge(mymap[i->courseID], mymap[j->courseID]);
            }

        }
    }

    return temp;

}