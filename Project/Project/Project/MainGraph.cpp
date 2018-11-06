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
	int from = 0, to= 0;
	float weight;
	while (from != 99 && to != 98) {
		myfile >> from >> to >> weight;
		m_graph.addArc(from, to, weight);
	}
	myfile.close();

	int sizeX = 108;
	int sizeY = 72;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int index = i * 10 + j;
			m_graph.nodeIndex(index)->SetPosition(j * sizeX, i * sizeY);
			int r = (int)std::rand() % 10;
			if (r == 0 || index == 25)
				m_graph.nodeIndex(index)->SetAsObstacle();
		}
	}
	//std::function<void(GraphNode<std::string,int> *)> f_visit = &visit;
	m_graph.AStar(m_graph.nodeIndex(5), m_graph.nodeIndex(55));
	//graph.breadthFirst(graph.nodeIndex(0), f_visit);
}

void MainGraph::AStar() {
	m_graph.AStar(m_graph.nodeIndex(5), m_graph.nodeIndex(55));
}


