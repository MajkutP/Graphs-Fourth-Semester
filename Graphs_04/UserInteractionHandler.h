#ifndef UserInteractionHandler_h
#define UserInteractionHandler_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/// This function draws simple menu on SFML window that contains
/// all posible options user can choose from (representation changing
/// particular algorithms etc.) This functions only argument represents
/// reference to window this function will draw on
void RenderWindowMenu(sf::RenderWindow& window);

/// This function gets from user two numbers - one unsigned andf one double
/// which represent number of vertices and probability of edge occurence
void GetNumberOfVerticesAndProbabilityFromUser(unsigned& numberOfVertices, double& probability);

#endif
