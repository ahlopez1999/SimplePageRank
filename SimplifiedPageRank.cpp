#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
using namespace std;

class AdjacencyList
{
private:
	//maps url -> vector (url , 1 / outdegree)
	map<string, vector<string>> Graph;
	map<string, double> Ranks;
public:
	void AddEdge(string from, string to);
	void PageRank(int n);
};

void AdjacencyList::AddEdge(string from, string to)
{
	//if from is new, also add it to Ranks
	if (Graph.count(from) == 0)
	{
		Ranks[from] = 0;
	}
	//if to is new, add it to Graph
	if (Graph.count(to) == 0)
	{
		Graph[to];
	}
	Graph[from].push_back(to);
	Ranks[to]++;
}

void AdjacencyList::PageRank(int n)
{
	map<string, double> ranks;
	map<string, vector<string>>::iterator itr;
	//initialize ranks to be 1 / |V|
	for (itr = Graph.begin(); itr != Graph.end(); itr++)
	{
		ranks[itr->first] = 1.00 / double(Graph.size());
	}
	//start multiplying
	for (int i = 1; i < n; i++)
	{
		map<string, double> temp;
		for (itr = Graph.begin(); itr != Graph.end(); itr++)
		{
			for (unsigned int j = 0; j < Graph[itr->first].size(); j++)
			{
				temp[Graph[itr->first][j]] += double(1.00 / double(Graph[itr->first].size())) * ranks[itr->first];
			}
		}
		ranks = temp;
	}
	//print
	map<string, double>::iterator itr2;
	for (itr2 = ranks.begin(); itr2 != ranks.end(); itr2++)
	{
		cout << std::setprecision(2) << std::fixed;
		cout << itr2->first << " " << itr2->second << '\n';
	}
}

int main()
{
	int no_of_lines, power_iterations;
	std::string from, to;
	std::cin >> no_of_lines;
	std::cin >> power_iterations;
	AdjacencyList theGraph;
	for (int i = 0; i < no_of_lines; i++)
	{
		std::cin >> from;
		std::cin >> to;
		theGraph.AddEdge(from, to);
	}
	theGraph.PageRank(power_iterations);
}