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

vector<classLists> studentAndClassListVec{}; //this object will store student and classes located in ClassLists.csv file.
vector<roomList> roomListVec{};  //this object will store rooms and their capasities located in RoomListsçcsv file.
vector<times> examScheduleStoreVec; //this object will store examination time zone and room information thanks to times class.
map<string, int> classAndTheirIdMap; //this object will store class names and their ID's.
myGraph graphHandle; //this object will handle graph structure.
map<int, colorList> classIdAndTheirColorMap; //this object will store class ID's and their colors.

int main()
{
    
    try {
        // 1. Read ClassLists.csv and RoomLists.csv files
        studentAndClassListVec.reserve(316);
        roomListVec.reserve(40);
        readClassList("ClassLists.csv", studentAndClassListVec);
        readRoomCapacities("RoomLists.csv", roomListVec);

        // 2. Assign an ID for each classes and store them as <ClassName, ID> pair in a map.
        classAndTheirIdMap = readClassesfromVector(studentAndClassListVec);

        // 3. Generate a graph for classes and handle it by graphHandle.
        graphHandle = generateGraphForClasses(classAndTheirIdMap, studentAndClassListVec);

        // 4. Book some rooms
        bookRoom("A101", "monday", 9, 30, 9);
        bookRoom("A102", "monday", 9, 0, 9);
        bookRoom("A103", "monday", 9, 0, 9);
        bookRoom("A104", "monday", 9, 0, 9);
        bookRoom("A106", "monday", 9, 30, 9);

        // 5. Implement graph coloring
        classIdAndTheirColorMap = graphColouring(graphHandle, classAndTheirIdMap);

        // 6. Determine time zones and rooms for each class examination
        examScheduleStoreVec = createExamSchedule(graphHandle, studentAndClassListVec, roomListVec, classAndTheirIdMap, classIdAndTheirColorMap);

        // 7. Write examination times to csv file.
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
