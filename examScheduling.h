#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <exception> 
#include <map>

using namespace std;


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

};

class myException : public exception {
public:
	virtual const char* what()const noexcept override {
		return "There is an error!";
	}
};



void readClassList(const std::string& filename, std::vector<classLists>& classes);
void readRoomCapacities(const std::string& filename, std::vector<roomList>& rooms);
map<string, int> readClassesfromVector(vector<classLists>& vec);
myGraph generateGraphForClasses(map<string, int> mymap, vector<classLists>& vec);



