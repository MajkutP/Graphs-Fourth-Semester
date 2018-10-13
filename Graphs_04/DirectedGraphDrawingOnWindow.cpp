#include "DirectedGraph.h"

void DirectedGraph::DrawGraph(sf::RenderWindow& window)
{
	sf::RenderTexture img;
	sf::Vector2u windowSize = window.getSize();
	img.create(windowSize.x, windowSize.y - 100);

	GraphRepresentation oldRep = m_currentRepresentation;
	ChangeToAdjacencyMatrix();

	sf::Font fontArial;
	fontArial.loadFromFile("arial.ttf");

	DrawEdges(img, fontArial);
	DrawVertices(img, fontArial);

	img.display();
	window.draw(sf::Sprite(img.getTexture()));

	if (m_currentRepresentation == GraphRepresentation::AdjacencyList)
		ChangeToAdjacencyList();
	else if (m_currentRepresentation == GraphRepresentation::IncidenceMatrix)
		ChangeToIncidenceMatrix();
}

void DirectedGraph::DrawEdges(sf::RenderTexture& img, sf::Font& fontArial)
{
	double pi = 3.14159265359;
	int numberOfVertices = GetNumberOfVertices();
	double angle = 2.0 * pi / numberOfVertices;

	double circleRadius = 300;
	double vertexRadius = 30;

	sf::Vector2u imgSize = img.getSize();

	for (int i = 0; i < numberOfVertices; ++i)
	{
		for (int j = 0; j < numberOfVertices; ++j)
		{
			if (m_encodedGraphData[i][j] == 1)
			{
				double startVertexX = circleRadius * cos(i*angle) + imgSize.x / 2.0;
				double startVertexY = circleRadius * sin(i*angle) + imgSize.y / 2.0;

				double endVertexX = circleRadius * cos(j*angle) + imgSize.x / 2.0;
				double endVertexY = circleRadius * sin(j*angle) + imgSize.y / 2.0;

				double angleDelta = atan2(endVertexY - startVertexY, endVertexX - startVertexX);

				double edgeXOffset = fabs(sin(angleDelta * 180.0 / pi)*vertexRadius * 0.75);
				double edgeYOffset = fabs(cos(angleDelta * 180.0 / pi)*vertexRadius * 0.75);

				if (startVertexX > endVertexX && startVertexY < endVertexY) {
					edgeXOffset = -edgeXOffset;
					edgeYOffset = -edgeYOffset;
				}
				else if (startVertexX > endVertexX && startVertexY > endVertexY) {
					edgeXOffset = -edgeXOffset;
				}
				else if (startVertexX < endVertexX && startVertexY < endVertexY)
					edgeYOffset = -edgeYOffset;


				double startX = startVertexX + edgeXOffset;
				double startY = startVertexY + edgeYOffset;
				double endX = endVertexX + edgeXOffset;
				double endY = endVertexY + edgeYOffset;

				sf::VertexArray line(sf::LinesStrip, 2);
				line[0].color = sf::Color::White;
				line[1].color = sf::Color::White;
				line[0].position = sf::Vector2f(startX, startY);
				line[1].position = sf::Vector2f(endX, endY);
				img.draw(line);

				double edgeLength = sqrt(pow(startVertexX - endVertexX, 2) + pow(startVertexY - endVertexY, 2));

				sf::CircleShape triangle(10, 3);
				triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
				if (fabs(startX - endX) < 1 && endY < startY)
					triangle.setRotation(0);
				else if (fabs(startX - endX) < 1 && endY > startY)
					triangle.setRotation(180);
				else if (fabs(startY - endY) < 1)
					triangle.setRotation(90 + (startX > endX ? 180 : 0));
				else
					triangle.setRotation((angleDelta + pi / 2.0) *180.0 / pi);

				double triangleXPosition = (startVertexX + endVertexX) / 2.0 + edgeLength * cos(angleDelta) / 8.0 + edgeXOffset;
				double triangleYPosition = (startVertexY + endVertexY) / 2.0 + edgeLength * sin(angleDelta) / 8.0 + edgeYOffset;
				triangle.setPosition(triangleXPosition, triangleYPosition);
				triangle.setFillColor(sf::Color::White);
				img.draw(triangle);

				if (HasWeights())
				{
					sf::Text weight(sf::String(std::to_string(m_weightMatrix[i][j])), fontArial, 20);
					weight.setPosition(triangleXPosition, triangleYPosition);
					weight.setColor(sf::Color::Green);
					img.draw(weight);
				}
			}
		}
	}
}

void DirectedGraph::DrawVertices(sf::RenderTexture& img, sf::Font& fontArial)
{
	double pi = 3.14159265359;
	int numberOfVertices = GetNumberOfVertices();
	double angle = 2.0 * pi / numberOfVertices;
	double circleRadius = 300;

	sf::Vector2u imgSize = img.getSize();

	for (unsigned i = 0; i < numberOfVertices; ++i)
	{
		double x = circleRadius * cos(i*angle) + imgSize.x / 2.0;
		double y = imgSize.y - (circleRadius * sin(i*angle) + imgSize.y / 2.0);

		sf::CircleShape circle(30);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(x, imgSize.y - y);
		circle.setFillColor(sf::Color::Red);
		img.draw(circle);

		sf::Text vertexNumber(sf::String(std::to_string(i)), fontArial, 20);
		vertexNumber.setColor(sf::Color::White);
		vertexNumber.setOrigin(vertexNumber.getLocalBounds().width / 2.0, vertexNumber.getLocalBounds().height / 2.0);
		vertexNumber.setPosition(x, imgSize.y - y);
		img.draw(vertexNumber);
	}
}