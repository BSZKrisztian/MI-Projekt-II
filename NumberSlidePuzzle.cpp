// NumberSlidePuzzle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

const int n = 3;
int hType = 0;
int visited = 0;
bool solseq = false;
bool pcost = false;
bool nvisited = false;

typedef struct NODE
{
	int state[n][n];
	int fn = 0;
	int gn = 0;
	int hn = 0;
	NODE* father;

} NODE;



bool compareStates(int a[n][n], int b[n][n])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] != b[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool stateExistsAndBetter(NODE node, std::vector<NODE> list)
{
	for (int j = 0; j < list.size(); j++)
	{
		if (compareStates(node.state, list[j].state) && node.fn >= list[j].fn)
		{
			return true;
		}
	}
	return false;
}

std::vector<NODE> removeFromList(NODE node, std::vector<NODE> list)
{
	for (int i = list.size() - 1; i >= 0; i--)
	{
		if (compareStates(node.state, list[i].state))
		{
			list.erase(list.begin() + i);
		}
	}
	return list;
}

void printArray(int a[n][n])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << a[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void printSolSeq(NODE node)
{
	if (node.father == NULL)
		return;
	else
	{
		printArray(node.state);
		printSolSeq(*node.father);
	}
}

NODE minFnNode(std::vector<NODE> nodes)
{
	int min = INT_MAX, minIndex;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].fn < min)
		{
			min = nodes[i].fn;
			minIndex = i;
		}
	}
	return nodes[minIndex];
}

std::vector<NODE> generateSuccessorNodes(NODE node)
{
	std::vector<NODE> succesorsList;

	//Getting the empty space coordinates (0 in matrix)
	int a, b;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (node.state[i][j] == 0)
			{
				a = i;
				b = j;
			}
		}
	}

	//LeftUpward Corner
	if (a == 0 && b == 0)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a + 1][b]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a][b + 1]);
		succesorsList.push_back(sNode2);
	}
	//LeftBorder
	if (a != 0 && a != n - 1 && b == 0)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a - 1][b]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a][b + 1]);
		succesorsList.push_back(sNode2);
		NODE sNode3 = node;
		std::swap(sNode3.state[a][b], sNode3.state[a + 1][b]);
		succesorsList.push_back(sNode3);

	}
	//LeftDownward Corner
	if (a == n - 1 && b == 0)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a][b + 1]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a - 1][b]);
		succesorsList.push_back(sNode2);
	}
	//Downward Border
	if (a == n - 1 && b != 0 && b != n - 1)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a][b - 1]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a - 1][b]);
		succesorsList.push_back(sNode2);
		NODE sNode3 = node;
		std::swap(sNode3.state[a][b], sNode3.state[a][b + 1]);
		succesorsList.push_back(sNode3);
	}
	//RightDownward Corner
	if (a == n - 1 && b == n - 1)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a][b - 1]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a - 1][b]);
		succesorsList.push_back(sNode2);
	}
	//Right Border
	if (a != 0 && a != n - 1 && b == n - 1)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a - 1][b]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a][b - 1]);
		succesorsList.push_back(sNode2);
		NODE sNode3 = node;
		std::swap(sNode3.state[a][b], sNode3.state[a + 1][b]);
		succesorsList.push_back(sNode3);
	}
	//RightUpward Corner
	if (a == 0 && b == n - 1)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a][b - 1]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a + 1][b]);
		succesorsList.push_back(sNode2);
	}
	//Upward Border
	if (a == 0 && b != 0 && b != n - 1)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a][b - 1]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a + 1][b]);
		succesorsList.push_back(sNode2);
		NODE sNode3 = node;
		std::swap(sNode3.state[a][b], sNode3.state[a][b + 1]);
		succesorsList.push_back(sNode3);
	}
	//Somewhere in the middle
	if (a != 0 && a != n - 1 && b != 0 && b != n - 1)
	{
		NODE sNode1 = node;
		std::swap(sNode1.state[a][b], sNode1.state[a - 1][b]);
		succesorsList.push_back(sNode1);
		NODE sNode2 = node;
		std::swap(sNode2.state[a][b], sNode2.state[a][b + 1]);
		succesorsList.push_back(sNode2);
		NODE sNode3 = node;
		std::swap(sNode3.state[a][b], sNode3.state[a + 1][b]);
		succesorsList.push_back(sNode3);
		NODE sNode4 = node;
		std::swap(sNode4.state[a][b], sNode4.state[a][b - 1]);
		succesorsList.push_back(sNode4);
	}
	return succesorsList;
}

int badTileHeuristics(NODE node)
{
	int mask[n*n] = {0, 1, 2, 3, 4, 5, 6, 7, 8 }, k=0;
	int hn = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (node.state[i][j] == 0)
			{
				k++;
				continue;
			}
			if (node.state[i][j] != mask[k])
			{
				hn++;
			}
			k++;
		}
	}
	return hn;
}

int manhattanHeuristics(NODE node)
{
	int hn = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (node.state[i][j] == 1)
			{
				hn += i;
				hn += abs(j - 1);
			}
			if (node.state[i][j] == 2)
			{
				hn += i;
				hn += abs(j - 2);
			}
			if (node.state[i][j] == 3)
			{
				hn += abs(i - 1);
				hn += j;
			}
			if (node.state[i][j] == 4)
			{
				hn += abs(i - 1);
				hn += abs(j - 1);
			}
			if (node.state[i][j] == 5)
			{
				hn += abs(i - 1);
				hn += abs(j - 2);
			}
			if (node.state[i][j] == 6)
			{
				hn += abs(i - 2);
				hn += j;
			}
			if (node.state[i][j] == 7)
			{
				hn += abs(i - 2);
				hn += abs(j - 1);
			}
			if (node.state[i][j] == 1)
			{
				hn += abs(i - 2);
				hn += abs(j - 2);
			}
		}
	}
	return hn;
}

NODE initializeNode(int array[n*n])
{
	NODE node;
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			node.state[i][j] = array[k];
			k++;
		}
	}

	if (hType == 1)
	{
		node.hn = badTileHeuristics(node);
	}
	else if (hType == 2)
	{
		node.hn = manhattanHeuristics(node);
	}

	node.fn = node.hn + node.gn;

	return node;
}

void AStarAlgorithm(std::vector<NODE> OpenList, std::vector<NODE> ClosedList, NODE startNode, NODE goalNode)
{
	OpenList.push_back(startNode);

	while (!OpenList.empty())
	{
		NODE node = minFnNode(OpenList);
		visited++;
		OpenList = removeFromList(node, OpenList);

		ClosedList.push_back(node);

		if (compareStates(node.state, goalNode.state))
		{
			printArray(node.state);
			if (pcost)
			{
				std::cout<<"The cost of solution is "<< node.gn << " step(s)"<< '\n';
			}
			if(solseq)
			{
				std::cout << "The solution sequence is " << '\n';
				printSolSeq(node);
			}
			if (nvisited)
			{
				std::cout << "The number of visited nodes is " << visited << '\n';
			}
		
			break;
		}

		std::vector<NODE> successorNodes = generateSuccessorNodes(node);
		for (int i = 0; i < successorNodes.size(); i++)
		{
			successorNodes[i].father = &node;
			if (hType == 1)
			{
				successorNodes[i].hn = badTileHeuristics(successorNodes[i]);
			}
			else if (hType == 2)
			{
				successorNodes[i].hn = manhattanHeuristics(successorNodes[i]);
			}
			successorNodes[i].gn = node.gn + 1;
			successorNodes[i].fn = successorNodes[i].hn + successorNodes[i].gn;

			if (stateExistsAndBetter(successorNodes[i], OpenList))
			{
				continue;
			}

			if (stateExistsAndBetter(successorNodes[i], ClosedList))
			{
				continue;
			}

			OpenList = removeFromList(successorNodes[i], OpenList);
			ClosedList = removeFromList(successorNodes[i], ClosedList);

			OpenList.push_back(successorNodes[i]);
		}
	}
}




int main(int argc, char* argv[])
{
	//Initializations and declarations
	std::vector<NODE> OpenList;
	std::vector<NODE> ClosedList;
	NODE goalNode, startNode;
	int arrayNode[n*n] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	goalNode = initializeNode(arrayNode);

	bool isInput = false;
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (std::string(argv[i]) == std::string("-input"))
			{
				i++;
				if (i < argc)
				{
					int number;
					std::ifstream file;
					std::string filename = argv[i];
					file.open(filename);
					if (file.is_open())
					{
						isInput = true;
						for (int i = 0; i < n*n; i++)
						{
							file >> arrayNode[i];
						}
						startNode = initializeNode(arrayNode);
						std::cout << "Input state from text file:\n";
						printArray(startNode.state);
						file.close();
					}
					else
					{
						std::cout << "Couldn't open file\n";
						system("pause");
						return 0;
					}
				}
			}

			else if (std::string(argv[i]) == "-solseq")
			{
				solseq = true;
			}

			else if (std::string(argv[i]) == "-pcost")
			{
				pcost = true;
			}

			else if (std::string(argv[i]) == "-nvisited")
			{
				nvisited = true;
			}

			else if (std::string(argv[i]) == "-h")
			{
				i++;
				if (i < argc)
				{
					hType = atoi(argv[i]);
					if (hType && hType > 0)
					{
						if (hType == 1)
						{
							std::cout << "Heuristic used: Bad tile placement" << "\n";
						}
						if (hType == 2)
						{
							std::cout << "Heuristic used: Manhattan Distance " << "\n";
						}
						
					}
					else
					{
						std::cout << "Invalid number\n";
					}
				}
			}
		}
	}

	if (isInput == false)
	{
		int k = 0;
		std::cout << "Please write the input manually\n";
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << "[" << i << "]" << "[" << j << "]: ";
				std::cin >> arrayNode[k];
				k++;
			}
		}
		std::cout << '\n';
		startNode = initializeNode(arrayNode);
	}

	AStarAlgorithm(OpenList, ClosedList, startNode, goalNode);

	system("pause");
	return 0;
}