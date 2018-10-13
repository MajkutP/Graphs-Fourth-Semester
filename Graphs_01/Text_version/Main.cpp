/// Compile with -std=C++11 enabled

#include "Main.h"

int main()
{
	GraphStorage storedGraph;

	std::cout<<"Choose what you want to do."<<std::endl;
	std::cout<<"1.Load graph from file"<<std::endl;
	std::cout<<"2.Generate random graph - G(n,l)"<<std::endl;
	std::cout<<"3.Generate random graph - G(n,p)"<<std::endl;
	int option;
	while (true)
	{
		std::cin>>option;
		if (option == 1 || option == 2 || option == 3)
			break;
		
		std::cout<<"Wrong option, try again!"<<std::endl;

	}

	if (option==1)
	{
		Input inputGetter;
		bool isFileValid = true;
		do 
		{
			inputGetter.OpenFile();
			isFileValid = inputGetter.GetInputFromFile(storedGraph);

		}while (!isFileValid);

	}
	else if (option==2)
	{
		std::vector<std::vector<int>> temp;
		storedGraph.AddGraphToStorage(temp, 'a');
		int numberOfVertices, numberOfEdges;
		std::cout<<"Enter number of vertices: ";
		std::cin>>numberOfVertices;
		std::cout<<"Enter number of edges: ";
		std::cin>>numberOfEdges;
		storedGraph->GenerateRandomGraphBasedOnDensity( numberOfVertices, numberOfEdges);
	}
	else 
	{
		std::vector<std::vector<int>> temp;
		storedGraph.AddGraphToStorage(temp, 'a');
		int numberOfVertices, probability;
		std::cout<<"Enter number of vertices: ";
		std::cin>>numberOfVertices;
		std::cout<<"Enter probability: ";
		std::cin>>probability;
		storedGraph->GenerateRandomGraphBasedOnProbability(numberOfVertices, probability);

	}
	

	storedGraph->PrintGraph(std::cout);
	
	while (storedGraph->AskUserAboutChange()){
		storedGraph->PrintGraph(std::cout);
	}

	Output outputFile;
	outputFile.SaveToFile(storedGraph);
	return 0;
}
