#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <Windows.h>

using namespace std;
using namespace sf;

template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    This is the graph class, it contains all the
//                  nodes.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph {
private:

    // typedef the classes to make our lives easier.
    typedef GraphArc<NodeType, ArcType> Arc;
    typedef GraphNode<NodeType, ArcType> Node;

// ----------------------------------------------------------------
//  Description:    A container of all the nodes in the graph.
// ----------------------------------------------------------------

	std::vector<Node *> m_nodes;
	Node* start = m_nodes[11];
	Node* goal = m_nodes[88];

	int los;

public:           
    // Constructor and destructor functions
    Graph( int size );
    ~Graph();

	vector<Vector2f> hitPoints;
	vector<Vector2f> hitNodes;
	bool foundGoal;
    // Accessors
    Node * nodeIndex(int index) const {
		return m_nodes.at(index);
    }
	
    // Public member functions.
	void SetStart(Node* s) { start = s; }
	void SetGoal(Node* g) { goal = g; }
	Node* GetStart() { return start; }
	Node* GetGoal() { return goal; }
	Node* GetNodeFromPos(Vector2i pos);
    bool addNode( NodeType data, int index );
    void removeNode( int index );
    bool addArc( int from, int to, ArcType weight );
    void removeArc( int from, int to );
    Arc* getArc( int from, int to );        
    void clearMarks();
    void depthFirst( Node* pNode, std::function<void(Node *)> f_visit);
    void breadthFirst( Node* pNode, std::function<void(Node *)> f_visit);
	void adaptedBreadthFirst( Node* pCurrent, Node* pGoal );
	void Reset();
	void AStar();	
	Node* GetCheapestNode(vector<Node*> openList);
	void ThetaStar(sf::Image image);
	void LazyThetaStar(sf::Image image);
	bool LineOfSight(Node* pCurrent, Node* pNeighbour, sf::Image image);
	void ShowInfo(string info);
};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    Constructor, this constructs an empty graph
//  Arguments:      The maximum number of nodes.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph( int maxNodes ) : m_nodes( maxNodes, nullptr) 
{  
}


template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::Reset() {
	goal->SetPath(false);
	hitPoints.clear();
	hitNodes.clear();
	foundGoal = false;
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes.at(i)->setPrevious(NULL);
	}
}

// ----------------------------------------------------------------
//  Name:           ~Graph
//  Description:    destructor, This deletes every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
   for( int index = 0; index < m_nodes.size(); index++ ) {
        if( m_nodes[index] != nullptr ) {
			delete m_nodes.at(index);
        }
   }
}

// ----------------------------------------------------------------
//  Name:           addNode
//  Description:    This adds a node at a given index in the graph.
//  Arguments:      The first parameter is the data to store in the node.
//                  The second parameter is the index to store the node.
//  Return Value:   true if successful
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode( NodeType data, int index ) {
   bool nodeNotPresent = false;
   // find out if a node does not exist at that index.
   if ( nullptr == m_nodes.at(index) ) {
      nodeNotPresent = true;
      // create a new node, put the data in it, and unmark it.
	  m_nodes.at(index) = new Node;
	  m_nodes.at(index)->setData(data);
	  m_nodes.at(index)->setMarked(false);
    }
        
    return nodeNotPresent;
}

// ----------------------------------------------------------------
//  Name:           removeNode
//  Description:    This removes a node from the graph
//  Arguments:      The index of the node to return.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode( int index ) {
     // Only proceed if node does exist.
     if( nullptr != m_nodes.at(index) ) {
         // now find every arc that points to the node that
         // is being removed and remove it.        
         Arc* arc;

         // loop through every node
         for( int node = 0; node < m_nodes.size(); node++ ) {
              // if the node is valid...
              if( nullptr != m_nodes.at(node) ) {
                  // see if the node has an arc pointing to the current node.
                  arc = m_nodes.at(node)->getArc(m_nodes.at(index) );
              }
              // if it has an arc pointing to the current node, then
              // remove the arc.
              if( arc != 0 ) {
                  removeArc( node, index );
              }
         }
        

        // now that every arc pointing to the current node has been removed,
        // the node can be deleted.
        delete m_nodes.at(index);
		m_nodes.at(index) = nullptr;       
    }
}

// ----------------------------------------------------------------
//  Name:           addArd
//  Description:    Adds an arc from the first index to the 
//                  second index with the specified weight.
//  Arguments:      The first argument is the originating node index
//                  The second argument is the ending node index
//                  The third argument is the weight of the arc
//  Return Value:   true on success.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc( int from, int to, ArcType weight ) {
     bool proceed = true; 
     // make sure both nodes exist.
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) {
         proceed = false;
     }
        
     // if an arc already exists we should not proceed
     if( m_nodes.at(from)->getArc( m_nodes.at(to) ) != nullptr ) {
         proceed = false;
     }

     if (proceed == true) {
        // add the arc to the "from" node.
		 m_nodes.at(from)->addArc(m_nodes.at(to), weight );
     }
        
     return proceed;
}

// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This removes the arc from the first index to the second index
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc( int from, int to ) {
     // Make sure that the node exists before trying to remove
     // an arc from it.
     bool nodeExists = true;
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) {
         nodeExists = false;
     }

     if (nodeExists == true) {
        // remove the arc.
		 m_nodes.at(from)->removeArc(m_nodes.at(to) );
     }
}


// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    Gets a pointer to an arc from the first index
//                  to the second index.
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   pointer to the arc, or 0 if it doesn't exist.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc( int from, int to ) {
     Arc* arc = 0;
     // make sure the to and from nodes exist
     if( nullptr != m_nodes.at(from) && nullptr != m_nodes.at(to) ) {
         arc = m_nodes.at(from)->getArc(m_nodes.at(to) );
     }
                
     return arc;
}


// ----------------------------------------------------------------
//  Name:           clearMarks
//  Description:    This clears every mark on every node.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks() {
     for( int index = 0; index < m_nodes.size(); index++ ) {
          if( nullptr != m_nodes.at(index) ) {
			  m_nodes.at(index)->setMarked(false);
          }
     }
}


// ----------------------------------------------------------------
//  Name:           depthFirst
//  Description:    Performs a depth-first traversal on the specified 
//                  node.
//  Arguments:      The first argument is the starting node
//                  The second argument is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::depthFirst( Node* node, std::function<void(Node *)> f_visit ) {
     if( nullptr != node ) {
           // process the current node and mark it
           f_visit( node );
           node->setMarked(true);

           // go through each connecting node
           auto iter = node->arcList().begin();
           auto endIter = node->arcList().end();
        
		   for( ; iter != endIter; ++iter) {
			    // process the linked node if it isn't already marked.
                if ( (*iter).node()->marked() == false ) {
                   depthFirst( (*iter).node(), f_visit);
                }            
           }
     }
}


// ----------------------------------------------------------------
//  Name:           breadthFirst
//  Description:    Performs a depth-first traversal the starting node
//                  specified as an input parameter.
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::breadthFirst( Node* node, std::function<void(Node *)> f_visit) {
   if( nullptr != node ) {
	  queue<Node*> nodeQueue;        
	  // place the first node on the queue, and mark it.
      nodeQueue.push( node );
      node->setMarked(true);

      // loop through the queue while there are nodes in it.
      while( nodeQueue.size() != 0 ) {
         // process the node at the front of the queue.
		 f_visit( nodeQueue.front() );

         // add all of the child nodes that have not been 
         // marked into the queue
         auto iter = nodeQueue.front()->arcList().begin();
         auto endIter = nodeQueue.front()->arcList().end();
         
		 for( ; iter != endIter; iter++ ) {
              if ( (*iter).node()->marked() == false) {
				 // mark the node and add it to the queue.
                 (*iter).node()->setMarked(true);
                 nodeQueue.push( (*iter).node() );
              }
         }

         // dequeue the current node.
         nodeQueue.pop();
      }
   }  
}


// ----------------------------------------------------------------
//  Name:           adaptedBreadthFirst
//  Description:    Performs a breadth-first traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::adaptedBreadthFirst( Node* current, Node *goal ) {
     
}

template<class NodeType, class ArcType>
GraphNode<NodeType, ArcType>* Graph<NodeType, ArcType>::GetNodeFromPos(Vector2i pos) {
	for (size_t i = 0; i < m_nodes.size(); i++)
	{
		if (pos.x > m_nodes.at(i)->GetXPos() - m_nodes.at(i)->sizeX / 2 && pos.x < m_nodes.at(i)->GetXPos() + m_nodes.at(i)->sizeX / 2 &&
			pos.y > m_nodes.at(i)->GetYPos() - m_nodes.at(i)->sizeY / 2 && pos.y < m_nodes.at(i)->GetYPos() + m_nodes.at(i)->sizeY / 2)
			return m_nodes.at(i);
	}
	return NULL;
}

template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::ShowInfo(string info) {
	int a = 0;
	int s = 0;
	Clock clock;
	while (!foundGoal) {
		switch (a)
		{
		case 0:
			cout << "Working " << info << endl;
			a++;
			break;
		case 1:
			cout << "Working " << info << "." << endl;
			a++;
			break;
		case 2:
			cout << "Working " << info << ".." << endl;
			a++;
			break;
		case 3:
			cout << "Working " << info << "..." << endl;
			a++;
			break;
		case 4:
			cout << "Working " << info << "...." << endl;
			a = 0;
			break;
		default:
			break;
		}
		
		this_thread::sleep_for(chrono::seconds(1));
	}
	float time = clock.getElapsedTime().asSeconds();
	//cout << info << " took " << time << " seconds." << endl;
}

// ----------------------------------------------------------------
//  Name:           AStar
//  Description:    Performs a AStar traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::AStar() {
	Reset();
	thread* t1 = new thread(&Graph<NodeType, ArcType>::ShowInfo, this, "A Star");
	Clock clock;

	vector<Node*> closedList;
	vector<Node*> openList = { start };
	vector<Node*> cameFrom;
	int nodes = 0, nb = 0;
	
	start->gValue = 0;
	start->hValue = start->Diagonal(goal);
	while (!openList.empty()) {
		nodes++;
		Node* cheapest;

		float bestF = 9999999;
		float index = -1;

		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->GetFValue() < bestF)//Finding the cheapest cell in this list
			{
				bestF = openList[i]->GetFValue();
				index = i;
			}
		}

		cheapest = openList[index];
		auto ite = openList.begin();
		advance(ite, index);
		openList.erase(ite);
		Node* current = cheapest;// GetCheapestNode(openList);
		closedList.push_back(current);

		//cout << "Checking current: " << current->data() << endl;
		if (current == goal) {
			cout << "Found Goal" << endl;
			foundGoal = true;
			goal->SetPath(true);
			break;
		}
		typedef list<Arc> arclist;
		list<Arc> arcs = current->arcList();
		auto it = arcs.begin();
		for (; it != arcs.end(); ++it)
		{
			nb++;
			Arc arc = *it;
			Node* neighbour = arc.node();
			//cout << "Checking neighbour: " << neighbour->data() << endl;
			if (neighbour->IsObtacle()) { continue; }
			bool inClosed = false;
			for (int j = 0; j < closedList.size(); j++)
			{
				if (neighbour == closedList[j]) { inClosed = true; }
			}
			if (inClosed) { continue; }
			float gScore = current->gValue + arc.weight();

			bool inOpen = false;
			for (int j = 0; j < openList.size(); j++)
			{
				if (openList[j] == neighbour)
				{
					inOpen = true;
				}
			}
			if (!inOpen) {
				neighbour->gValue = 99999999;
				//neighbour->setPrevious(NULL);
			}
			float oldGValue = neighbour->gValue;
			if (current->gValue + arc.weight() < neighbour->gValue) {
				neighbour->gValue = current->gValue + arc.weight();
				neighbour->hValue = neighbour->Diagonal(goal);
				if (neighbour != current->previous()) {
					neighbour->setPrevious(current);
				}
				if ( neighbour->gValue < oldGValue) {
					for (int i = 0; i < openList.size(); i++)
					{
						if (openList[i] == neighbour) {
							auto it = openList.begin();
							advance(it, i);
							openList.erase(it);
						}
					}
					openList.push_back(neighbour);
				}
			}
		}
	}

	float time = clock.getElapsedTime().asSeconds();
	cout << "A* took " << time << " seconds." << endl;
	float pathLength = 0;
	for (Node* node = goal; node != NULL; node = node->previous()) {
		if (node->previous()) {
			float a = abs(node->GetXPos() - node->previous()->GetXPos());
			float b = abs(node->GetYPos() - node->previous()->GetYPos());
			float l = sqrtf(powf(a, 2) + powf(b, 2));
			pathLength += l;
		}
	}
	cout << "Length of the path is: " << pathLength << endl;
	cout << nodes << " nodes expanded" << endl;
	cout << nb << " neighbours checked" << endl;
	t1->join();
}


// ----------------------------------------------------------------
//  Name:           GetCheapestNode
//  Description:    Get the node with the lowest f value
//  Arguments:      None
//  Return Value:   The Node with the lowest f value.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
GraphNode<NodeType, ArcType>* Graph<NodeType, ArcType>::GetCheapestNode(vector<Node*> openList) {
	Node* cheapest;

	float bestF = 9999;
	float index = -1;

	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->GetFValue() < bestF)//Finding the cheapest cell in this list
		{
			bestF = openList[i]->GetFValue();
			index = i;
		}
	}

	cheapest = openList[index];
	auto it = openList.begin();
	advance(it, index);
	openList.erase(it);

	return cheapest;
}

// ----------------------------------------------------------------
//  Name:           ThetaStar
//  Description:    Performs a ThetaStar traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::ThetaStar(sf::Image image) {
	Reset();

	thread* t1 = new thread(&Graph<NodeType, ArcType>::ShowInfo, this, "Theta Star");
	Clock clock;
	vector<Node*> closedList;
	vector<Node*> openList = { start };
	vector<Node*> cameFrom;
	int nodes = 0, nb = 0;
	los = 0;
	start->gValue = 0;
	start->hValue = start->Euclidean(goal);
	//start->setPrevious(start);
	while (!openList.empty()) {
		nodes++;
		Node* cheapest;

		float bestF = 9999;
		float index = -1;

		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->GetFValue() < bestF)//Finding the cheapest cell in this list
			{
				bestF = openList[i]->GetFValue();
				index = i;
			}
		}

		cheapest = openList[index];
		auto ite = openList.begin();
		advance(ite, index);
		openList.erase(ite);
		Node* current = cheapest;//GetCheapestNode(openList);
		closedList.push_back(current);
		//cout << "Checking current: " << current->data() << endl;
		if (current == goal) {
			cout << "Found Goal" << endl;
			foundGoal = true;
			goal->SetPath(true);
			break;
		}
		typedef list<Arc> arclist;
		list<Arc> arcs = current->arcList();
		auto it = arcs.begin();
		for (; it != arcs.end(); ++it)
		{
			nb++;
			Arc arc = *it;
			Node* neighbour = arc.node();
			//cout << "Checking neighbour: " << neighbour->data() << endl;
			if (neighbour->IsObtacle()) { continue; }
			bool inClosed = false;
			for (int j = 0; j < closedList.size(); j++)
			{
				if (neighbour == closedList[j]) { inClosed = true; }
			}
			if (inClosed) { continue; }
			float gScore = current->gValue + arc.weight();

			bool inOpen = false;
			for (int j = 0; j < openList.size(); j++)
			{
				if (openList[j] == neighbour)
				{
					inOpen = true;
				}
			}
			if (!inOpen) {
				neighbour->gValue = 99999;
				//neighbour->setPrevious(NULL);
			}
			float oldGValue = neighbour->gValue;
			if (LineOfSight(current->previous(), neighbour, image)) {
				if (current->previous()->gValue + current->previous()->Euclidean(neighbour) < neighbour->gValue) {
					neighbour->gValue = current->previous()->gValue + current->previous()->Euclidean(neighbour);
					neighbour->hValue = neighbour->Euclidean(goal);
					if (neighbour != current->previous()->previous()) {
						neighbour->setPrevious(current->previous());
					}
					//if (neighbour->gValue < oldGValue) {
						for (int i = 0; i < openList.size(); i++)
						{
							if (openList[i] == neighbour) {
								auto it = openList.begin();
								advance(it, i);
								openList.erase(it);
							}
						}
						openList.push_back(neighbour);
					//}
				}
			}
			else {
				if (current->gValue + arc.weight() < neighbour->gValue) {
					neighbour->gValue = current->gValue + arc.weight();
					neighbour->hValue = neighbour->Euclidean(goal);
					if (neighbour != current->previous()) {
						neighbour->setPrevious(current);
					}

					//if (neighbour->gValue < oldGValue) {
					for (int i = 0; i < openList.size(); i++)
					{
						if (openList[i] == neighbour) {
							auto it = openList.begin();
							advance(it, i);
							openList.erase(it);
						}
					}
					openList.push_back(neighbour);
					//}
				}

			}
		}
	}

	float time = clock.getElapsedTime().asSeconds();
	cout << "Theta* took " << time << " seconds." << endl;

	float pathLength = 0;
	for (Node* node = goal; node != NULL; node = node->previous()) {
		if (node->previous()) {			
			float a = abs(node->GetXPos() - node->previous()->GetXPos());
			float b = abs(node->GetYPos() - node->previous()->GetYPos());
			float l = sqrtf(powf(a, 2) + powf(b, 2));
			pathLength += l;
		}
	}
	cout << "Length of the path is: " << pathLength << endl;
	cout << nodes << " nodes expanded" << endl;
	cout << nb << " neighbours checked" << endl;
	cout << los << " amount of line-of-sight checks" << endl;

	t1->join();
}

// ----------------------------------------------------------------
//  Name:           LazyThetaStar
//  Description:    LazyPerforms a ThetaStar traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::LazyThetaStar(sf::Image image) {
	Reset();
	string g = "No Goal Found";
	thread* t1 = new thread(&Graph<NodeType, ArcType>::ShowInfo, this, "Lazy Theta Star");
	Clock clock;
	vector<Node*> closedList;
	vector<Node*> openList = { start };
	vector<Node*> cameFrom;
	int nodes = 0, nb = 0;
	los = 0;
	start->gValue = 0;
	start->hValue = start->Euclidean(goal);
	start->setPrevious(start);
	while (!openList.empty()) {
		nodes++;
		Node* cheapest;

		float bestF = 99999;
		float index = -1;

		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->GetFValue() < bestF)//Finding the cheapest cell in this list
			{
				bestF = openList[i]->GetFValue();
				index = i;
			}
		}

		cheapest = openList[index];
		auto ite = openList.begin();
		advance(ite, index);
		openList.erase(ite);
		//cheapest = openList.back();
		//openList.pop_back();
		Node* current = cheapest;//GetCheapestNode(openList);

		if (!(LineOfSight(current->previous(), current, image))) {
			current->gValue = 999999;
			typedef list<Arc> arclist;
			list<Arc> arcs = current->arcList();
			auto it = arcs.begin();
			for (; it != arcs.end(); ++it)
			{
				Arc arc = *it;
				Node* neighbour = arc.node();
				for (int i = 0; i < closedList.size(); i++)
				{
					if (closedList[i] == neighbour) {
						float newG = neighbour->gValue + current->Euclidean(neighbour);
						if (newG <= current->gValue) {
							current->gValue = newG;
							current->hValue = current->Euclidean(goal);
							current->setPrevious(neighbour);
						}

					}
				}
			}
		}

		closedList.push_back(current);
		//cout << "Checking current: " << current->data() << endl;
		if (current == goal) {
			g = "Found Goal";
			foundGoal = true;
			goal->SetPath(true);
			break;
		}
		typedef list<Arc> arclist;
		list<Arc> arcs = current->arcList();
		auto it = arcs.begin();
		for (; it != arcs.end(); ++it)
		{
			nb++;
			Arc arc = *it;
			Node* neighbour = arc.node();
			//cout << "Checking neighbour: " << neighbour->data() << endl;
			if (neighbour->IsObtacle() || neighbour == start) {
				continue;
			}
			bool inClosed = false;
			for (int j = 0; j < closedList.size(); j++)
			{
				if (neighbour == closedList[j]) { inClosed = true; }
			}
			if (inClosed) { continue; }

			bool inOpen = false;
			for (int j = 0; j < openList.size(); j++)
			{
				if (openList[j] == neighbour)
				{
					inOpen = true;
					break;
				}
			}
			if (!inOpen) {
				neighbour->gValue = 99999;
				//neighbour->setPrevious(NULL);
			}
			float newG = current->previous()->gValue + current->previous()->Euclidean(neighbour);
			if (newG <= neighbour->gValue) {
				if (neighbour != current->previous()->previous()) {
					neighbour->gValue = current->previous()->gValue + current->previous()->Euclidean(neighbour);
					neighbour->hValue = neighbour->Euclidean(goal);
					neighbour->setPrevious(current->previous());
					openList.push_back(neighbour);
				}
			}

		}
	}
	cout << g << endl;

	float time = clock.getElapsedTime().asSeconds();
	cout << "Lazy Theta* took " << time << " seconds." << endl;

	float pathLength = 0;
	for (Node* node = goal; node != NULL; node = node->previous()) {
		
		cout << node->data() << endl;
		if (node->previous()) {
			float a = abs(node->GetXPos() - node->previous()->GetXPos());
			float b = abs(node->GetYPos() - node->previous()->GetYPos());
			float l = sqrtf(powf(a, 2) + powf(b, 2));
			pathLength += l;
		}
		if (node == start) { break; }
	}
	cout << "Length of the path is: " << pathLength << endl;
	cout << nodes << " nodes expanded" << endl;
	cout << nb << " neighbours checked" << endl;
	cout << los << " line-of-sight checks" << endl;

	t1->join();
}

// ----------------------------------------------------------------
//  Name:           LineOfSight
//  Description:    Does a line-of-sight check between two nodes
//  Arguments:      The first parameter is the current node.
//                  The second parameter is the neighbour node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::LineOfSight(Node* current, Node *neighbour, sf::Image image) {
	if (!current || !neighbour ) { return false; } //||current == neighbour
	los++;
	Vector2f line(neighbour->GetXPos() - current->GetXPos(),  neighbour->GetYPos() - current->GetYPos());
	//normalize the vector
	float length = sqrtf(powf(line.x, 2) + powf(line.y, 2));
	line.x  = line.x / length;
	line.y  = line.y / length;
	//set the lengt of the vector to 40(half the length of one tile)
	float templength = 20;
	Vector2f tempLine(line.x * templength, line.y * templength);
	while (templength < length) {
		tempLine.x = line.x * templength; 
		tempLine.y = line.y * templength;
		Color pixel = image.getPixel(current->GetXPos() + tempLine.x, current->GetYPos() + tempLine.y);
		if (pixel == Color(128, 128, 128)) { 
			hitPoints.push_back(Vector2f(current->GetXPos() + tempLine.x, current->GetYPos() + tempLine.y));
			hitNodes.push_back(Vector2f(current->GetXPos(), current->GetYPos()));
			return false; 
		}
		templength += 20;
	}
	return true;

}

#include "GraphNode.h"
#include "GraphArc.h"

#endif