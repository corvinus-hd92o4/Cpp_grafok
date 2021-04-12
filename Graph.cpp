/*
 * cGraph.cpp
 *
 *  Created on: 2018. szept. 28.
 *      Author: Boda Mihaly HMH3MV
 */

#include "Graph.h"
#include "help.hpp"
#include <map>
#include <vector>

Graph::Graph() {
	// TODO Auto-generated constructor stub

}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
	cout << "\nThe program stopped running, goodbye!" << endl;
}

Graph::Node::Node() {
	//id = 0;
}

Graph::Node::~Node() {

}

//egy Node-nak visszaadja az id-ját
int Graph::getIndex(Graph::Node* node) {

	for (unsigned int i = 0; i < nodes.size(); i++) {
		if (nodes[i] == node) {
			return i;
		}
	}
	return -1;
}

//Visszaadja az adott id-jű Node-ot
Graph::Node* Graph::getNode(int idx) {
	for (Node* it : nodes) {
		if (it->id == idx) {
			return it;
		}
	}
	return nullptr;
}

void Graph::readFromFile(string filename) {

	ifstream fin(filename);

	//Ha nem létező fájlt adunk meg
	if (!fin.good()) {
		cerr << "Something went wrong while reading the file!\n";
		return;
	}

	//Beolvasásnál el kell tárolnunk, hiszen nem tudjuk rögtön megkeresni a szomszédot

	map<int, vector<pair<int, int>>> segedmap;

	//csucsok szamanak beolvasasa
	string temp;
	getline(fin, temp);
	int nodeNum = change<int>(temp);

	for (int i = 0; i < nodeNum; i++) {

		Node* node = new Node();

		getline(fin, temp);
		istringstream iss(temp);
		string token;

		//id beolvasása
		getline(iss, token, ';');
		int id = change<int>(token);
		(*node).id = id;

		//cout<<id<<endl;

		nodes.push_back(node);

		segedmap[id];

		vector<pair<int, int>> vec;

		while (getline(iss, token, ';')) {
			istringstream iss2(token);
			string token2;
			pair<int, int> pair;

			getline(iss2, token2, '-');
			pair.first = change<int>(token2);

			getline(iss2, token2, '-');
			pair.second = change<int>(token2);

			vec.push_back(pair);
		}

		segedmap[id] = vec;

	}

	//Végigmegyünk az összes tárolt csúcson
	for (int id = 0; id < nodeNum; id++) {

		//Az adott csúcshoz tartozó összes szomszédot felkeresünk
		for (unsigned int neighbourIdx = 0; neighbourIdx < segedmap[id].size();
				neighbourIdx++) {

			int valami = segedmap[id][neighbourIdx].first; //Lekérjük, hogy mi az id-je az adott szomszédnak

			Node* neighbourNode = getNode(valami); //Megkeressük magát a szomszédot

			//Megkeressük, hogy az, akinek be akarjuk állítani a szomszédait, az hol van a tárolt node-ok listájában, és
			//a megkeresett szomszédhoz beállítjuk a hozzá tartozó élnek a súlyát.
			nodes[getIndex(getNode(id))]->neighbours[neighbourNode] =
					segedmap[id][neighbourIdx].second;

		}
	}

}

//kiirja az adott id-jú csúcs szomszédait és azok súlyát
void Graph::sendNodes(unsigned int index) {
	if (nodes.empty()) {
		throw exception();
	} else {

		Node* nnode = getNode(index);

		cout << "A(z) " << nnode->id
				<< "-számú csúcsnak az alábbi szomszédai vannak:" << endl;
		;
		for (auto& it : nnode->neighbours) {
			cout << "\t\t\t\t\t\t" << it.first->id
					<< ", ahol a ket csucs kozti suly : " << it.second << endl;
		}
	}

}

void Graph::color(const unsigned int m) {
	cout << "\nColoring: \n";
	if (nodes.empty()) {
		throw exception();
	} else {
		//szinek jelolese: 0,1,2....stb

		int nodeNum = nodes.size();  // ennyi db csucsunk van
		cout << "A beolvasott gráfnak " << nodeNum << " csúcsa van." << endl;

		vector<int> colors(nodeNum);  //egy vectort letrehozunk a szineknek

		colors[0] = 0; // az elso  szinet 0-ra allitjuk

		// a tobbinek egyelore -1 re allitjuk az erteket, ezt meg fogjuk valtoztatni
		for (int i = 1; i < nodeNum; i++) {
			colors[i] = -1;
		}

		vector<bool> used_colors(nodeNum); // szinek eltarolasara hasznalt vector
		for (int col = 0; col < nodeNum; col++) {
			used_colors[col] = false;
		}
		//a maradek csucsokhoz szinek hozzarendelese
		for (int k = 1; k < nodeNum; k++) {
			Node* aktnode = getNode(k);
			for (auto& it : aktnode->neighbours) {
				if (colors[it.first->id] != -1) {
					used_colors[colors[it.first->id]] = true;
				}
			}
			int clrs;
			for (clrs = 0; clrs < nodeNum; clrs++) {  //szabad szin keresese
				if (used_colors[clrs] == false) {
					break;
				}
			}
			colors[k] = clrs;
			for (auto& it : aktnode->neighbours) {
				if (colors[it.first->id] != -1) {
					used_colors[colors[it.first->id]] = false;
				}
			}
		}

		//osszehasonlitas a megadott parameterrel
		unsigned int max = 0;
		for (unsigned int i = 0; i < colors.size(); i++) {
			if ((unsigned) colors[i] > max) {
				max = colors[i];
			}
		}

		if (max <= (unsigned) (m - 1)) {
			cout << "A graf kiszinezheto maximum " << m
					<< " darab szinnel, az alabbi modon:\n";
			for (int l = 0; l < nodeNum; l++) {
				cout << "Vertex: " << l << "   |   Color: " << colors[l]
						<< endl;
			}

		} else {
			cout << "A graf NEM szinezheto ki " << m << " darab szinnel, csak "
					<< max + 1 << " darab szinnel!" << endl;
		}
	}
}

void Graph::dijkstra(const unsigned int src_id) {
	cout << "\nDijkstra algorithm: \n";
	if (nodes.empty()) {
		throw exception();
	} else {
		map<Node*, int> ns;
		Node* firstNode = getNode(src_id); //kiindulasi csucs

		ns[firstNode] = 0;

		while (ns.size() < nodes.size()) {
			int min = INT_MAX; // a tavolsagot kezdetben vegtelenre kell allitani
			Node* nextNode;
			for (auto& it1 : ns) {
				for (auto& it2 : it1.first->neighbours) {
					if (it1.second + it2.second <= min
							&& ns.count(it2.first) == 0) {
						min = it1.second + it2.second;
						nextNode = it2.first;
					}
				}
			}
			//itt mar tudjuk ki a kovi es mi a sulya
			ns[nextNode] = min;
		}

		//kiiratas
		for (auto& it : ns) {
			cout << "Vertex: " << it.first->id << "   |   Distance: "
					<< it.second << endl;
		}
		//a csúcsokat nem rendezve irja ki
	}
}

