#pragma once
#include "Graph.h"
class MainGraph
{

	typedef GraphArc<std::string, int> Arc;
	typedef GraphNode<std::string, int> Node;

public:
	MainGraph();
	~MainGraph();
	void CreateGraph();
	
};

