#include "UserChoiceHandlers.h"
#include <limits>
#include <iostream>
#include "InputFromFileHandler.h"
#include "OutputToFileHandler.h"

int GetExerciseChoiceFromUser()
{
	std::cout<<"Choose what do you want to do: "<<std::endl;
	std::cout<<" 1. Check if sequence is graphic and generate simple graph if it is." <<std::endl;
	std::cout<<" 2. Randomize simple graph generated from graphic sequence." <<std::endl;
	std::cout<<" 3. Find max connected component on a given graph." <<std::endl;
	std::cout<<" 4. Generate random graph that contains Eulerian cycle and find this cycle." <<std::endl;
	std::cout<<" 5. Generate random k-regular graph." <<std::endl;
	std::cout<<" 6. Check if graph is hamiltonian." <<std::endl;
	std::cout<<" (Other number) Quit."<<std::endl;

	int userChoice;

	while (true)
	{
		if (std::cin>>userChoice)
			return userChoice;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}	
}


int ChooseGraphInputType()
{
	std::cout<<"What do you want to do?"<<std::endl;
	std::cout<<" 1. Load graph from file. "<<std::endl;
	std::cout<<" 2. Input graphic sequence." <<std::endl;

	int userChoice;

	while (true)
	{
		if (!(std::cin>>userChoice))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (userChoice == 1 || userChoice ==2)
			break;
	}

	return userChoice;
}

SimpleGraph* GetGraphFromUser()
{
	SimpleGraph* graph = nullptr;
	int userChoice = ChooseGraphInputType();

	if (userChoice==1)
	{
		InputFromFileHandler graphGetter;
		graphGetter.OpenFile();
		graph = graphGetter.GetInputFromFile();
	}
	else
	{
		while (true)
		{
			std::vector<int> deg = GetSequenceFromUser();
			if (!IsSequenceGraphic(deg))
				continue;

			graph = new SimpleGraph(deg);	
			break;
		}
	}

	graph->ChangeToAdjacencyMatrix();
	return graph;
}

void FirstAndSecondOption(int userChoice)
{
	std::vector<int> deg = GetSequenceFromUser();

	if(IsSequenceGraphic(deg))
	{
		SimpleGraph graph(deg);
		graph.ChangeToAdjacencyMatrix();
		std::cout<<"Your graph: "<<std::endl;
		graph.PrintGraph(std::cout);

		if (userChoice == 2)
		{
			std::cout<<"After randomization:"<<std::endl;;
			graph.RandomizeSimpleGraph(); 
			graph.PrintGraph(std::cout);
			SaveGraphToFile(graph, "Exercise_2.txt");
		}
		else
			SaveGraphToFile(graph, "Exercise_1.txt");
	}

}