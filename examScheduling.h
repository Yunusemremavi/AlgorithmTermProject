#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <exception> 
#include <map>

using namespace std;

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
*  This class is implemented for generating adjancency graph methodç
*/

class myGraph {
	int numberOfVertices;
	vector<vector<int>> adjMatrix;

public:
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
	string day;
	int hour;
	int min;
	vector<string> rooms;
};

class myException : public exception {
public:
	virtual const char* what()const noexcept override {
		return "There is an error!";
	}
};

typedef enum : unsigned int {
	white,
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
	golden
}colorList;


void readClassList(const std::string& filename, std::vector<classLists>& classes);
void readRoomCapacities(const std::string& filename, std::vector<roomList>& rooms);
map<string, int> readClassesfromVector(vector<classLists>& vec);
myGraph generateGraphForClasses(map<string, int> mymap, vector<classLists>& vec);
map<int, colorList>  graphColouring(myGraph& graph, map<string, int>& mymap);
void createExamSchedule(myGraph& graph, vector<classLists>& classes, std::vector<roomList>& rooms, map<string, int>& mapForClassandID, map<int, colorList>& mapForClassIDandColor);



