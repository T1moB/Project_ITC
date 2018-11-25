#include "MainGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Grid.h"
#include <SFML/Graphics.hpp>

#include "GraphNode.h"

using namespace std;

bool start = false, goal = false;
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

	//std::function<void(GraphNode<std::string,int> *)> f_visit = &visit;
	//m_graph.AStar(m_graph.nodeIndex(5), m_graph.nodeIndex(55));
	//graph.breadthFirst(graph.nodeIndex(0), f_visit);
}

void MainGraph::SetStartGoal(Vector2i pos) {
	Node* n = m_graph.GetNodeFromPos(pos);
	if (!n || n->IsObtacle()) {
		cout << "No node found" << endl;
		return;
	}
	if (!start) {
		cout << "Setting Start to: " << n->data() << endl;
		m_graph.SetStart(n);
		start = true;
	}
	else{
		cout << "Setting Goal to: " << n->data() << endl;
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
