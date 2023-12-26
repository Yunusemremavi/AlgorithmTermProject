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
            if (i->studentID == j->studentID || i->profName == j->profName) {
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
    * This checkColor object will be used to color all the vertices which is not connected to the coloured vertex, with the same color.
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
                if (!checkNeighboor(checkColor, j->first, graph, mymap)) { // we check that this vertex has any connection with other vertexes which we colored them and they are located in checkColor.
                    colorTable[mymap[j->first]] = color;
                    checkColor.push_back(j->first);
                }
            }
        }
        checkColor.clear(); // we should clear vector for each new color process.
        color = static_cast<colorList>(static_cast<int>(color) + 1u); // we should increase color as we start new color process
    }


    /*for (auto i = myvec.begin(); i != myvec.end(); ++i) {
        std::cout << "Ders Adi : " << i->first << " ID : " << mymap[i->first] << " Color : " << colorTable[mymap[i->first]] << "\n";
    }*/

    return colorTable;
}

int totalNumberOfStudents(vector<classLists>& classes, string className)
{
    auto count{ 0 };
    for (auto& i : classes) {
        if (i.courseID == className) {
            ++count;
        }
    }
    return count;
}

times func(vector<vector<vector<int>>>& room_time_list, const std::vector<roomList>& rooms, pair<int, int> duration, int numberOfStudents, int* day, int hour, string className,int* sayac)
{
    if ((hour < 9) || (hour > 18) || (*day < 0) || (*day > 6))
        throw myException{};

    vector<string> vec;

    int temp_hour{ hour };
    int temp_hour_2{ hour };
    auto duration_2{ duration };
    numberOfStudents *= 2;
    int count{};

    for (auto i = rooms.begin() + ( * sayac); i != rooms.end(); ++i) {
        while (duration.first || duration.second) {
            (* sayac)++;
            if (room_time_list[distance(rooms.begin(), i)][*day][hour - 9] == 0) {
                if (duration.first)
                    --duration.first;
                else if (duration.second)
                    duration.second = 0;
                room_time_list[distance(rooms.begin(), i)][*day][hour - 9] = 1;
                ++hour;
            }
            else {
                while (temp_hour < hour) {
                    room_time_list[distance(rooms.begin(), i)][*day][temp_hour - 9] = 0;
                    ++temp_hour;
                }
                break;
            }
            if (hour > 18) {
                while (temp_hour < hour) {
                    room_time_list[distance(rooms.begin(), i)][*day][temp_hour - 9] == 0;
                    ++temp_hour;
                }
                count = 0;
                temp_hour_2 = 9;
                temp_hour = temp_hour_2;
                hour = temp_hour;
                ++(* day);
                if (*day > 6)
                    throw myException{};
                duration = duration_2;
                vec.clear();
            }
        } 
        if (temp_hour != hour) {
            count += i->capacity;
            vec.emplace_back(i->roomID);
        }
       
        
       
        if (count > numberOfStudents)
            break;

        temp_hour = temp_hour_2;
        hour = temp_hour;
        duration = duration_2;
        
        
    }
    if (count < numberOfStudents)
        throw myException{};

    return { className,day_of_array[*day], temp_hour_2, 0, temp_hour_2 + duration_2.first, duration_2.second, vec };

}

vector<times> createExamSchedule(myGraph& graph, vector<classLists>& classes, std::vector<roomList>& rooms, map<string, int>& mapForClassandID, map<int, colorList>& mapForClassIDandColor)
{
    map<int, pair<int, int>> duration;
    map<int, int> numberOfStudents;

    for (auto i = mapForClassandID.begin(); i != mapForClassandID.end(); ++i) {
        numberOfStudents[i->second] = totalNumberOfStudents(classes, i->first);
    }

    for (auto i = classes.begin(); i != classes.end(); ++i) {
        duration[mapForClassandID[i->courseID]] = pair<int, int>{ i->duration / 60, i->duration % 60 };
    }
    vector<times> examTimes;
    examTimes.reserve(mapForClassandID.size());

    vector<vector<vector<int>>> room_time_list(rooms.size(), vector<vector<int>>(7, vector<int>(10)));

    int day{ 0 };
    int hour{ 9 };
    int sayac{};
    int hourForRefresh{};
    int minForRefresh{};
    int dayForRefresh{day};

    vector<times> examTimeList;
    examTimeList.reserve(mapForClassandID.size());
    for (colorList i = white; i <= color_11; i = static_cast<colorList>(static_cast<int>(i) + 1)) {
        for (auto j = mapForClassandID.begin(); j != mapForClassandID.end(); ++j) {
            if (mapForClassIDandColor[j->second] == i) {
                dayForRefresh = day;
                examTimeList.emplace_back(func(room_time_list, rooms, duration[j->second], numberOfStudents[j->second], &day, hour, j->first,&sayac));
                if (duration[j->second].first > hourForRefresh && duration[j->second].second > minForRefresh) {
                    hourForRefresh = duration[j->second].first;
                    minForRefresh = duration[j->second].second;
                }
                    
            }
        }
        sayac = 0;
        hour += hourForRefresh;
        if (minForRefresh)
            ++hour;
        if (day == dayForRefresh && hour > 17) {
            hour = 9; ++day;
        }
        else if (hour > 17) {
            hour = 9 + hourForRefresh;
        }
       
        if (day > 6)
            return examTimeList;
    }
    return examTimeList;
}

void writeToCSV(const string& filename, const vector<times>& examScheduleResult) {
    std::ofstream file(filename);

    // Write CSV header
    file << "----------className----------,----------Day--------,---------HOUR-----------, ----------Rooms---------\n";

    // Write data
    for (const auto& d : examScheduleResult) {
        file << d.className << "," << d.day << "," << to_string(d.start_hour) + ":"s + to_string(d.start_min) + "-"s + to_string(d.finish_hour) + ":"s + to_string(d.finish_min) << ",";
        for (const auto r : d.rooms) {
            file << r.data() << ",";
        } 
        file << "\n";
    }
}