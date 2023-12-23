#include "examScheduling.h"
#include <algorithm>

#include <iostream>

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

/*
*  This function is used for taking available class from input csv file. map container is used since it store
*  a pair where class id will be used as key and an integer will be used as value. Integer used value is used for
*  generating graph adjanceny matrix.
*
*/

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

/*
*  This function is used for generating a graph using adjancency matrix method. The size of matrix is
*  taken from map container generated in readClassesfromVector. Also, adding edge is performed in this function
*  checking the whether a class is taken from same student.
*
*/

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

/*
*  This function is used by graphColouring to be sure that vertices do not have any connection. If there is
*  no connection, they can have same colour.
*/

bool checkNeighboor(vector<string>& vec, string& s, myGraph& graph, map<string, int>& mymap)
{
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        if (graph.checkIsItNeighboor(mymap[*i], mymap[s]))
        {
            return true;
        }
    }
    return false;
}

/*
*  This functios is impelemented for graph colouring using Welsh Powell algorithm.
*  mymap : It stores classes and their ID's used in Adjancecy matrix as index.
*  graph : It is an object managing adjancecy graph process.
*/
map<int, colorList>  graphColouring(myGraph& graph, map<string, int>& mymap)
{
    using pairForClouring = pair<string, verticesDegree>;

    /*
    *   This vector is generated for storing class and their vertices degree located in Adjancecy matrix.
    */
    vector<pairForClouring> myvec;
    myvec.reserve(mymap.size());

    for (auto i = mymap.begin(); i != mymap.end(); ++i) {
        myvec.emplace_back(pairForClouring{ i->first, graph.verticesDegree(i->second) });
    }

    /*
    *  This sort function is called to store classes according to their verticesDegree
    */
    sort(myvec.begin(), myvec.end(), [](pairForClouring& x, pairForClouring& y) { return x.second > y.second; });

    /*
    * This colorTable object will store class ID loceted in mymap and their colors.
    */
    map<int, colorList> colorTable;

    colorList color = white;

    /*
    * This checkColor object will be used to color all the vertices not connected to the coloured vertex, with the same color.
    */
    vector<string> checkColor;

    for (auto i = myvec.begin(); i != myvec.end(); ++i) {
        for (auto j = i; j != myvec.end(); ++j) {
            if (colorTable.find(mymap[j->first]) != colorTable.end())
                continue;

            if (i == j) {
                colorTable[mymap[i->first]] = color;
                checkColor.push_back(i->first);
            }
            else {
                if (!checkNeighboor(checkColor, j->first, graph, mymap)) {
                    colorTable[mymap[j->first]] = color;
                    checkColor.push_back(j->first);
                }
            }
        }
        checkColor.clear();
        color = static_cast<colorList>(static_cast<int>(color) + 1u);
    }


    /*for (auto i = myvec.begin(); i != myvec.end(); ++i) {
        std::cout << "Ders Adi : " << i->first << " ID : " << mymap[i->first] << " Color : " << colorTable[mymap[i->first]] << "\n";
    }*/

    return colorTable;
}

void createExamSchedule(myGraph& graph, vector<classLists>& classes, std::vector<roomList>& rooms, map<string, int>& mapForClassandID, map<int, colorList>& mapForClassIDandColor)
{
    map<int, pair<int, int>> duration;

    for (auto i = classes.begin(); i != classes.end(); ++i) {
        duration[mapForClassandID[i->courseID]] = pair<int, int>{ i->duration / 60, i->duration % 60 };
    }
    vector<times> examTimes;
    examTimes.reserve(mapForClassandID.size());

    vector<vector<vector<int>>> room_time_list(rooms.size(), vector<vector<int>>(6, vector<int>(10)));

    for (colorList i = white; i <= golden; i = static_cast<colorList>(static_cast<int>(i) + 1)) {

    }

}