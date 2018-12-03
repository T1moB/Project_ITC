#include "MainGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Grid.h"
#include <SFML/Graphics.hpp>

#include "GraphNode.h"

using namespace std;

bool start = false;
void visit(GraphNode<std::string, int> * node) {
	cout << "Visiting: " << node->data() << endl;
}

MainGraph::MainGraph(int size) : m_graph(size*size)
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
	myfile.open("Data/nodes2.txt");

	while (myfile >> nodeLabel) {
		m_graph.addNode(nodeLabel, i++);
	}

	myfile.close();
	myfile.open("Data/arcs2.txt");
	int from = 0, to= 0;
	float weight;
	while (from != 399  && to != 398) {
		myfile >> from >> to >> weight;
		m_graph.addArc(from, to, weight);
	}
	myfile.close();
}

void MainGraph::SetStartGoal(Vector2i pos) {
	Node* n = m_graph.GetNodeFromPos(pos);
	if (!n || n->IsObtacle()) {
		cout << "No node found or is an obstacle" << endl;
		return;
	}
	m_graph.Reset();
	if (!start) {
		m_graph.SetStart(n);
		start = true;
	}
	else{
		m_graph.SetGoal(n);
		start = false;
	}
}
void MainGraph::SetAObstacle(Vector2i pos) {
	Node* n = m_graph.GetNodeFromPos(pos);
	if (!n) {
		cout << "No node found" << endl;
		return;
	}
	n->SetObstacle(!n->IsObtacle());
}

void MainGraph::AStar() {
	m_graph.AStar();
}

void MainGraph::ThetaStar(sf::Image image) {
	m_graph.ThetaStar(image);
}

void MainGraph::LazyThetaStar(sf::Image image) {
	m_graph.LazyThetaStar(image);
}

void MainGraph::Draw(sf::RenderWindow & window) {
	for (int i = 0; i < m_graph.hitPoints.size(); i++)
	{
		CircleShape circle(5);
		circle.setFillColor(Color::Red);
		circle.setPosition(m_graph.hitPoints[i] - Vector2f(2.5,2.5));

		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].position = sf::Vector2f(m_graph.hitPoints[i]);
		line[0].color = sf::Color::Red;
		line[1].position = sf::Vector2f(m_graph.hitNodes[i]);
		line[1].color = sf::Color::Red;

		window.draw(circle);
		window.draw(line);
	}
	
}
