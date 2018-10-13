#include "UserInteractionHandler.h"
#include <iostream>

void RenderWindowMenu(sf::RenderWindow& window)
{
	/// white line that separates drawing area from menu
	sf::VertexArray line(sf::LinesStrip, 2);
	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;
	line[0].position = sf::Vector2f(0, 700); 
	line[1].position = sf::Vector2f(1000, 700);
	window.draw(line);

	/// load font
	sf::Font fontArial;
	fontArial.loadFromFile("arial.ttf");

	/// lines of menu text
	sf::Text text(L"L - Load graph from file\t\t\t\t\t\tG - Generate random G(n,p) graph \t\tS - Generate random strongly connected graph", fontArial, 15);
	text.setPosition(30, 710);
	window.draw(text);
	text.setString(L"M - Change to adjacency matrix\t\t  A - Change to adjacency list \t\t\t\t   I - Change to indicence matrix");
	text.setPosition(30, 730);
	window.draw(text);

	text.setString(L"W - Generate weights \t\t\t\t\t\t  K - Kosaraju algorithm \t\t\t\t\t\t\tB - Bellman - Ford algorithm");
	text.setPosition(30, 750);
	window.draw(text);

	text.setString(L"J - Johnson algorithm \t\t\t\t\t\t  ESC - Exit");
	text.setPosition(30, 770);
	window.draw(text);
}

void GetNumberOfVerticesAndProbabilityFromUser(unsigned& numberOfVertices, double& probability)
{
	std::cout << "Please enter number of vertices: ";
	std::cin >> numberOfVertices;
	std::cout << "Please enter probability: ";
	std::cin >> probability;
}