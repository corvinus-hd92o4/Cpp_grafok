//============================================================================
// Name        : Graph.cpp
// Author      : Boda Mihaly HMH3MV
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
//felhasznalt hivatkozasok:
//Thore Husfeldt, Second draft, rev. 8a882dd, 2013-09-20 : Graph colouring algorithms

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graph.h"

using namespace std;

int main() {
	Graph* graph = new Graph();
	graph->readFromFile("G2.txt");
	try {
		graph->sendNodes(1);  //csak magam ellenőrzésére használtam
	} catch (exception& e) {
		cout << "Something went wrong, the Graph does not exist!" << endl;
	}

	try {
		graph->color(4);
	} catch (exception& e) {
		cout << "Something went wrong, the Graph does not exist!"<< endl;
	}

	try {
		graph->dijkstra(1);
	} catch (exception& e) {
		cout << "Something went wrong, the Graph does not exist!" << endl;
	}

	delete graph;

	return 0;
}
