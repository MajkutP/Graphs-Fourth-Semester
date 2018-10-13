#include "Main.h"

int main()
{
	std::cout<<std::endl<<std::endl;

	int userChoice = GetExerciseChoiceFromUser();

	if (userChoice == 1 || userChoice == 2)
		FirstAndSecondOption(userChoice);
	else if (userChoice == 3)
	{
		std::unique_ptr<SimpleGraph> graph (GetGraphFromUser());
		graph->PrintGraph(std::cout);
		std::vector<unsigned> maxConnectedComponent = graph->FindMaxConnectedComponent();
		std::cout<<"Max connected component: ";
		for (unsigned i =0; i<maxConnectedComponent.size(); ++i)
			std::cout<<maxConnectedComponent.at(i)<<" ";
		std::cout<<std::endl;
		SaveGraphToFile(*graph, "Exercise_3.txt");
	}
	else if (userChoice == 4)
	{
		SimpleGraph* graph = GenerateEulerianGraph();
		graph->FindAndPrintEulerianCycle();
		graph->PrintGraph(std::cout);
		SaveGraphToFile(*graph, "Exercise_4.txt");
	}
	else if (userChoice == 5)
	{
		std::cout<<"k - regular graph:"<<std::endl;
		std::cout<<"Please enter number of vertices: ";
		int numberOfVertices;
		std::cin>>numberOfVertices;
		std::cout<<"Please enter degree: ";
		int degree;
		std::cin>>degree;
		SimpleGraph regularG=generateKRegularGraph(numberOfVertices, degree); 
		regularG.PrintGraph(std::cout);
		SaveGraphToFile(regularG, "Exercise_5.txt");
	}
	else if (userChoice == 6)
	{
		std::unique_ptr<SimpleGraph> graph (GetGraphFromUser());
		graph->HamiltonianCycle();
		SaveGraphToFile(*graph, "Exercise_6.txt");
	}
	return 0;
}
