/*
 * cGraph.h
 *
 *  Created on: 2018. szept. 28.
 *      Author: Boda Mihaly HMH3MV
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Graph {
private:
	struct Node {
		int id;
		map<Node*, int> neighbours;

		Node();
		virtual ~Node();
	};
	vector<Node*> nodes;
	Node* getNode(int idx);
	int getIndex(Node* node);

public:
	Graph();
	virtual ~Graph();
	void readFromFile(string filename);
	void sendNodes(unsigned int idx); //ezt a függvényt csak a beolvasás, és a gráf ellenőrzésére használtam.
	void color(const unsigned int m);
	void dijkstra(const unsigned int src_id);

};

#endif /* GRAPH_H_ */
