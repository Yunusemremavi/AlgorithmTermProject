/*
* 
* Group Members: 
- BERAT YILDIZER - 235101103 
- MUSTAFA IBRAHIM AKSU - 235101102 
- YUNUS EMRE MAVI – 225101154

*/

// termProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Please use here direclty and just customizing input csv files to test our algortihm because giving correct arguments to functions and
// calling them in correct order could be complex.
//

#include <iostream>
#include "examScheduling.h"

vector<classLists> studentAndClassListVec{};
vector<roomList> roomListVec{};
vector<times> examScheduleStoreVec;
map<string, int> classAndTheirIdMap;
myGraph graphHandle;
map<int, colorList> classIdAndTheirColorMap;

int main()
{
    
    try {
        studentAndClassListVec.reserve(316);
        roomListVec.reserve(40);
        readClassList("ClassLists.csv", studentAndClassListVec);
        readRoomCapacities("RoomLists.csv", roomListVec);
        classAndTheirIdMap = readClassesfromVector(studentAndClassListVec);
        graphHandle = generateGraphForClasses(classAndTheirIdMap, studentAndClassListVec);
        bookRoom("A101", "monday", 9, 30, 9);
        bookRoom("A102", "monday", 9, 0, 9);
        bookRoom("A103", "monday", 9, 0, 9);
        bookRoom("A107", "monday", 9, 0, 9);
        bookRoom("A106", "monday", 9, 30, 9);
        classIdAndTheirColorMap = graphColouring(graphHandle, classAndTheirIdMap);
        examScheduleStoreVec = createExamSchedule(graphHandle, studentAndClassListVec, roomListVec, classAndTheirIdMap, classIdAndTheirColorMap);
        writeToCSV("exam_schedule_program.csv", examScheduleStoreVec);
        cout << "go to exam_schedule_program.csv\n";
        

    }
    catch (exception& x) {
        cout << x.what();
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
