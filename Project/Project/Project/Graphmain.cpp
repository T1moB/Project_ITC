
#include <iostream>
#include <fstream>
#include <string>

#include "Graph.h"

using namespace std;


typedef GraphArc<std::string, int> Arc;
typedef GraphNode<std::string, int> Node;

//void visit(Node * node) {
//	cout << "Visiting: " << node->data() << endl;
//}

void init() {

	Graph<std::string, int> graph(25);

	std::string nodeLabel;
	int i = 0;
	ifstream myfile;
	myfile.open("nodes.txt");

	while (myfile >> nodeLabel) {
		graph.addNode(nodeLabel, i++);
	}

	myfile.close();
	myfile.open("arcs.txt");

	int from, to, weight;
	while (myfile >> from >> to >> weight) {
		graph.addArc(from, to, weight);
	}
	myfile.close();

	// Now traverse the graph.
//	graph.breadthFirst(graph.nodeIndex(0), visit);
	
	system("PAUSE");

}
