#include "MainGraph.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Graph.h"
#include "GraphNode.h"

using namespace std;

void visit(GraphNode<std::string, int> * node) {
	cout << "Visiting: " << node->data() << endl;
}

MainGraph::MainGraph()
{
}


MainGraph::~MainGraph()
{
}

void MainGraph::CreateGraph() {
	Graph<std::string, int> graph(100);

	std::string nodeLabel;
	int i = 0;
	ifstream myfile;
	myfile.open("Data/nodes.txt");

	while (myfile >> nodeLabel) {
		graph.addNode(nodeLabel, i++);
	}

	myfile.close();
	myfile.open("Data/arcs.txt");

	int from, to, weight;
	while (myfile >> from >> to >> weight) {
		graph.addArc(from, to, weight);
	}
	myfile.close();

	//std::function<void(GraphNode<std::string,int> *)> f_visit = &visit;
	//graph.breadthFirst(graph.nodeIndex(0), f_visit);
}


