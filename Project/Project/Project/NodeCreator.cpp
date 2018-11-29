#include "NodeCreator.h"

#include <iostream>
#include <fstream>
using namespace std;



NodeCreator::NodeCreator()
{
}


NodeCreator::~NodeCreator()
{
}

void NodeCreator::Create() {
	int size = 10;
	ofstream arcsFile;
	ofstream nodesFile;
	arcsFile.open("Data/arcs.txt");
	nodesFile.open("Data/nodes.txt");
	if (arcsFile.is_open()) {
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int from, to;
				float cost;
				from = i * size + j;
				nodesFile << from << "\n";
				//left top
				to = from - 11;
				if (to >= 0 && from % 10 != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//top
				to = from - 10;
				if (to >= 0) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//right top
				to = from - 9;
				if (to >= 0 && from % 9 != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//left
				to = from - 1;
				if (to >= 0 && from % 10 != 0) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//right
				to = from + 1;
				if (to >= 0 && from % 9 != 0) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//left bot
				to = from + 9;
				if (to >= 0 && to < 100 && from % 10 != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//bot
				to = from + 10;
				if (to >= 0 && to < 100) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//right bot
				to = from + 11;
				if (to >= 0 && to < 100 && from % 9 != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
			}
		}
	}
}

void NodeCreator::Create2(int s) {
	int size = s;
	ofstream arcsFile;
	ofstream nodesFile;
	arcsFile.open("Data/arcs2.txt");
	nodesFile.open("Data/nodes2.txt");
	if (arcsFile.is_open()) {
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int from, to;
				float cost;
				from = i * size + j;
				nodesFile << from << "\n";
				//left top
				to = from - (size + 1);
				if (to >= 0 && from % size != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//top
				to = from - size;
				if (to >= 0) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//right top
				to = from - (size - 1);
				if (to >= 0 && from % (size - 1) != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//left
				to = from - 1;
				if (to >= 0 && from % size != 0) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//right
				to = from + 1;
				if (to >= 0 && from %(size - 1) != 0) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//left bot
				to = from + (size - 1);
				if (to >= 0 && to < size * size && from % size != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//bot
				to = from + size;
				if (to >= 0 && to < size * size) {
					cost = 1;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
				//right bot
				to = from + (size + 1);
				if (to >= 0 && to < size * size && from % (size - 1) != 0) {
					cost = 1.414;
					arcsFile << from << " " << to << " " << cost << "\n";
				}
			}
		}
	}
}
