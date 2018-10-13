#include "DirectedGraph.h"
#include "FileInput.h"
#include "UserInteractionHandler.h"
#include <iostream>
#include <cmath>
#include <random>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Directed Graph", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	wchar_t currently_pressed = L' ';
	window.setFramerateLimit(60);

	DirectedGraph* graph = nullptr;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) 
					window.close();

				else if (event.key.code == sf::Keyboard::L) {
					if (graph)
						delete graph;
					graph = LoadGraphFromFile();
					graph->PrintGraph(std::cout);
				}
				else if (event.key.code == sf::Keyboard::G)
				{
					if (graph)
						delete graph;
				
					unsigned numberOfVertices;
					double probability;
					GetNumberOfVerticesAndProbabilityFromUser(numberOfVertices, probability);
					graph =  DirectedGraph::GenerateRandomGraphBasedOnProbability(numberOfVertices, probability);
					graph->PrintGraph(std::cout);
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					if (graph)
						delete graph;

					graph = DirectedGraph::GenerateRandomStronglyConnectedGraph();
					graph->PrintGraph(std::cout);

				}
				else if (graph != nullptr)
				{
					if (event.key.code == sf::Keyboard::M) {
						graph->ChangeToAdjacencyMatrix();
						graph->PrintGraph(std::cout);
					}
					else if (event.key.code == sf::Keyboard::A)
					{
						graph->ChangeToAdjacencyList();
						graph->PrintGraph(std::cout);
					}
					else if (event.key.code == sf::Keyboard::I)
					{
						graph->ChangeToIncidenceMatrix();
						graph->PrintGraph(std::cout);
					}
					else if (event.key.code == sf::Keyboard::W)
					{
						graph->GenerateWeights(-5, 10);
						graph->PrintWeightMatrix(std::cout);
					}
					else if (event.key.code == sf::Keyboard::K)
						graph->Kosaraju();

					if (graph->HasWeights() && event.key.code == sf::Keyboard::B) {
						if (graph->Kosaraju().size() == graph->GetNumberOfVertices()) 
						{
							std::cout << "Choose vertex: " << std::endl;
							int vertex;
							std::cin >> vertex;
							graph->BellmanFord(vertex);
						}
						else
							std::cout << "Graph is not strongly connected" << std::endl;
					}

					if (graph->HasWeights() && event.key.code == sf::Keyboard::J) {
							try {
								if (graph->Kosaraju().size() == graph->GetNumberOfVertices())
									graph->Johnson();
							}catch(...) {}
					}
				}	
			}
		}
		if (graph != nullptr) {
			graph->DrawGraph(window);
		}
		RenderWindowMenu(window);
		window.display();
	}

	if (graph)
		delete graph;

	return 0;
}
