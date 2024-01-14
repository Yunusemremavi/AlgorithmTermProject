#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <exception> 
#include <map>
#include <iterator>
#include <tuple>

using namespace std;

#define theNumberOfRooms 60

class roomList;
extern vector<roomList> roomListVec;

typedef int verticesDegree;

class classLists {
public:
	int studentID;
	string profName;
	string courseID;
	int duration;

	classLists(int id, const string& name, const string& course, int time) : studentID{ id }, profName{ name }, courseID{ course }, duration{ time } {}
};

class roomList {
public:
	string roomID;
	int capacity;

	roomList(const string& id, int size) : roomID{id}, capacity{size} {}
};

/*
*  This class is implemented for generating adjancency graph method�
*/

class myGraph {
	int numberOfVertices;
	vector<vector<int>> adjMatrix;

public:
	myGraph() = default;
	myGraph(int v) : numberOfVertices{ v }, adjMatrix{ v, vector<int>(v, 0) } {}

	void addAdge(int x, int y)
	{
		adjMatrix[x][y] = 1;
		adjMatrix[y][x] = 1;
	}

	int verticesDegree(int x)
	{
		int count{};

		for (int i = 0; i < numberOfVertices; ++i) {
			if (adjMatrix[x][i] == 1)
				++count;
		}

		return count;
	}

	bool checkIsItNeighboor(int x, int y)
	{
		return adjMatrix[x][y];
	}

};

class times {
public:
	string className;
	string day;
	int start_hour;
	int start_min;
	int finish_hour;
	int finish_min;
	vector<string> rooms;

	times() = default;
	times(string c, string d, int sh, int sm, int fh, int fm, vector<string>& r) : className{ c }, day { d }, start_hour{ sh }, start_min{ sm }, finish_hour{ fh }, finish_min{ fm }, rooms{ r } {}
};

class myException : public exception {
public:
	virtual const char* what()const noexcept override {
		return "Sinav takvimi olusturulamiyor";
	}
};

typedef enum : unsigned int {
	white = 0,
	yellow,
	blue,
	red,
	green,
	brown,
	black,
	wheat,
	hotPink,
	pink,
	gray,
	silver,
	orange,
	royalBlue,
	olive,
	golden,
	color_1,
	color_2,
	color_3,
	color_4,
	color_5,
	color_6,
	color_7,
	color_8,
	color_9,
	color_10,
	color_11
}colorList;


void readClassList(const std::string& filename, std::vector<classLists>& classes);
void readRoomCapacities(const std::string& filename, std::vector<roomList>& rooms);
map<string, int> readClassesfromVector(vector<classLists>& vec);
myGraph generateGraphForClasses(map<string, int> mymap, vector<classLists>& vec);
map<int, colorList>  graphColouring(myGraph& graph, map<string, int>& mymap);
int totalNumberOfStudents(vector<classLists>& classes, string className);
times calculatingExamTimesforClass(vector<vector<vector<int>>>& room_time_list, const std::vector<roomList>& rooms, pair<int, int> duration, int numberOfStudents, int day, int hour, string className);
vector<times>  createExamSchedule(myGraph& graph, vector<classLists>& classes, std::vector<roomList>& rooms, map<string, int>& mapForClassandID, map<int, colorList>& mapForClassIDandColor);
void writeToCSV(const string& filename, const vector<times>& examScheduleResult);
void bookRoom(const char* room, const char* day, int start_hour, int start_min, int duration);


