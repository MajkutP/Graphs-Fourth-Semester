#include "Main.h"
#include <iostream>
#include <limits>
#include <memory>

int main()
{
	std::cout<<std::endl<<std::endl;
	std::cout<<"On what graph you want to execute the simulated annealing algorithm? Choose correct option: "<<std::endl;
	std::cout<<"1. Load graph from file. "<<std::endl;
	std::cout<<"2. Generate random graph. "<<std::endl;

	int userChoice;


	if (!(std::cin>>userChoice))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if(userChoice == 1)
	{
		std::unique_ptr<SimpleGraph> graph (GetGraphFromUser());
		graph->PrintWeightMatrix(std::cout);
		graph->SimulatedAnnealing();
		SaveToFile(*graph);
	}

	if (userChoice == 2)
	{
		SimpleGraph myGraph;
		std::cout<<std::endl;
		myGraph.PrintWeightMatrix(std::cout);
		myGraph.SimulatedAnnealing();
		SaveToFile(myGraph);
	}
	

	return 0;
}