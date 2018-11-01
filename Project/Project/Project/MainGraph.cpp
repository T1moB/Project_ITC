#include "MainGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Grid.h"

#include "Graph.h"
#include "GraphNode.h"

using namespace std;

void visit(GraphNode<std::string, int> * node) {
	cout << "Visiting: " << node->data() << endl;
}

MainGraph::MainGraph() : m_graph(100)
{
}


MainGraph::~MainGraph()
{
}

void MainGraph::CreateGraph() {
	//Graph<std::string, int> graph(100);

	std::string nodeLabel;
	int i = 0;
	ifstream myfile;
	myfile.open("Data/nodes.txt");

	while (myfile >> nodeLabel) {
		m_graph.addNode(nodeLabel, i++);
	}

	myfile.close();
	myfile.open("Data/arcs.txt");

	int from, to, weight;
	while (myfile >> from >> to >> weight) {
		m_graph.addArc(from, to, weight);
	}
	myfile.close();

	//Grid grid;
	//grid.CreateGridFromGraph(graph);
	m_graph.AStar(m_graph.nodeIndex(5), m_graph.nodeIndex(55));
	//std::function<void(GraphNode<std::string,int> *)> f_visit = &visit;
	//graph.breadthFirst(graph.nodeIndex(0), f_visit);
}


