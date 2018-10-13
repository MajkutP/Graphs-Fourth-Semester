#include "SimpleGraph.h"

#include <stdlib.h>     
#include <time.h>  

SimpleGraph::SimpleGraph(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation)
{
	m_storedRepresentation = inputFromFile;
	m_representation = typeOfRepresentation;
}

void SimpleGraph::PrintGraph(std::ostream& placeToPrint) const 
{
	for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
	{
		for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			placeToPrint<<m_storedRepresentation.at(i).at(j)<<" ";
		placeToPrint<<std::endl;
	}
}

char SimpleGraph::GetRepresentation() const
{
	return m_representation;
}

void SimpleGraph::ChangeAdjacencyListToIncidenceMatrix()
{
	std::vector<std::vector<int>> incidenceMatrix(m_storedRepresentation.size(), std::vector<int>(EdgesCounter(), 0));
	int counter=0;
	if(m_representation=='l')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(i+1 < (unsigned)m_storedRepresentation[i][j])
				{
					incidenceMatrix[i][counter]=1;
					incidenceMatrix[m_storedRepresentation[i][j]-1][counter]=1;
					counter++;
				}
			}
		}
	}
	m_storedRepresentation=incidenceMatrix;
	m_representation='i';
}

void SimpleGraph::ChangeAdjacencyMatrixToIncidenceMatrix()
{
	std::vector<std::vector<int>> incidenceMatrix(m_storedRepresentation.size(), std::vector<int>(EdgesCounter(), 0));
	int counter=0;
	if(m_representation=='a')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = i; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(m_storedRepresentation[i][j]==1)
				{
					incidenceMatrix[i][counter]=1;
					incidenceMatrix[j][counter]=1;
					counter++;
				}
			}
		}
	}
	m_storedRepresentation=incidenceMatrix;
	m_representation='i';

}

void SimpleGraph::ChangeIncidenceMatrixToAdjacencyMatrix()
{
	std::vector<std::vector<int>> adjacencyMatrix(m_storedRepresentation.size(), std::vector<int>(m_storedRepresentation.size(), 0));
	if(m_representation == 'i')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if (m_storedRepresentation[i][j] == 1)
				{
					for (unsigned k = 0; k < m_storedRepresentation.size(); ++k)
					{
						if((m_storedRepresentation[k][j] == 1) && (k != i))
							adjacencyMatrix[i][k] = 1;
					}
				}
			}
		}
	}

	m_storedRepresentation=adjacencyMatrix;
	m_representation='a';	
}

void SimpleGraph::ChangeAdjacencyListToAdjacencyMatrix()
{
	std::vector<std::vector<int>> adjacencyMatrix(m_storedRepresentation.size(), std::vector<int>(m_storedRepresentation.size(), 0));
	if(m_representation == 'l')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(m_storedRepresentation[i][j] != 0)
				{
					adjacencyMatrix[i][m_storedRepresentation[i][j]-1] = 1;
				}
			}		
		}			
	}
	m_storedRepresentation=adjacencyMatrix;
	m_representation='a';
}

void SimpleGraph::ChangeAdjacencyMatrixToAdjacencyList()
{
	std::vector<std::vector<int>> adjacencyList(m_storedRepresentation.size(), std::vector<int>(m_storedRepresentation.size(), 0));
	int counter;
	if(m_representation == 'a'){
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			counter = 0;
			for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(m_storedRepresentation[i][j] == 1)
				{
					adjacencyList[i][counter] = j+1;
					counter++;
				}
			}
		}
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = 0; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(adjacencyList[i][j] == 0)
				{
					adjacencyList.at(i).erase(adjacencyList.at(i).begin()+j, adjacencyList.at(i).end());
					break;
				}
			}
		}
	}
	m_storedRepresentation=adjacencyList;
	m_representation='l';
}

void SimpleGraph::ChangeInicidenceMatrixToAdjacencyList()
{
	ChangeIncidenceMatrixToAdjacencyMatrix();
	ChangeAdjacencyMatrixToAdjacencyList();
}

int SimpleGraph::EdgesCounter() const
{
	int edges=0;
	if(m_representation=='l')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
			edges+=m_storedRepresentation.at(i).size();
		edges/=2;
	}
	if(m_representation=='a')
	{
		for (unsigned i = 0; i < m_storedRepresentation.size(); ++i)
		{
			for (unsigned j = i+1; j < m_storedRepresentation.at(i).size(); ++j)
			{
				if(m_storedRepresentation[i][j]==1)
					edges++;
			}
		}
	}
	if(m_representation=='i')
		edges=m_storedRepresentation.at(0).size();
	return edges;
}

void SimpleGraph::ChangeToIncidenceMatrix()
{
	if(m_representation=='l')
		ChangeAdjacencyListToIncidenceMatrix();
	else if(m_representation=='a')
		ChangeAdjacencyMatrixToIncidenceMatrix();
	else if(m_representation=='i')
		std::cout<<"Graph is already represented by an incidence matrix."<<std::endl;
}

void SimpleGraph::ChangeToAdjacencyMatrix()
{
	if(m_representation=='l')
		ChangeAdjacencyListToAdjacencyMatrix();
	else if(m_representation=='a')
		std::cout<<"Graph is already represented by an adjacency matrix."<<std::endl;
	else if(m_representation=='i')
		ChangeIncidenceMatrixToAdjacencyMatrix();

}

void SimpleGraph::ChangeToAdjacencyList()
{
	if(m_representation=='l')
		std::cout<<"Graph is already represented by an adjacency list."<<std::endl;
	else if(m_representation=='a')
		ChangeAdjacencyMatrixToAdjacencyList();
	else if(m_representation=='i')
		ChangeInicidenceMatrixToAdjacencyList();
}

bool SimpleGraph::AskUserAboutChange()
{
	char newRepresentation;
	std::cout<<"In which representation you want to have your graph?"<<std::endl;
	std::cout<<"Options: \nl - adjacency list \na - adjacency matrix \ni - incidence matrix \ne - exit "<<std::endl;
	std::cin>>newRepresentation;
	if(newRepresentation=='l')
		ChangeToAdjacencyList();
	else if(newRepresentation=='a')
		ChangeToAdjacencyMatrix();
	else if(newRepresentation=='i')
		ChangeToIncidenceMatrix();
	else if (newRepresentation=='e')
		return false;
	else
		std::cout<<"Wrong option."<<std::endl;

	return true;
}

void SimpleGraph::GenerateRandomGraphBasedOnDensity(int verticesNumber, double density)
{
	srand (time(NULL));
	std::vector<std::vector<int>> adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));

	int maxEdges = verticesNumber*(verticesNumber-1)/2;
	if(density<0)
		density = -density;
	if (density<1)
	{
		for(int i=0; i<verticesNumber; i++)
		{
			for(int j=i+1; j<verticesNumber; j++)
			{
				double probability=(double)(std::rand()%(maxEdges+1))/(double)maxEdges;
				if(density>=probability)
				{
					adjacencyMatrix[i][j] = 1;
					adjacencyMatrix[j][i] = 1;
				}
			}
		}
	}
	else
	{
		int edgesNumber=density;
		if (edgesNumber>maxEdges) 
			edgesNumber=maxEdges;
		while(edgesNumber>0)
		{
			for(int i=0; i<verticesNumber; i++)
			{
				for(int j=i+1; j<verticesNumber; j++)
				{
					double probability=(double)(std::rand()%(maxEdges+1))/(double)maxEdges;
					double rest=((double)maxEdges-edgesNumber)/(double)maxEdges;
					if(probability>=rest && adjacencyMatrix[i][j] == 0 && edgesNumber>0)
					{
						adjacencyMatrix[i][j] = 1;
						adjacencyMatrix[j][i] = 1;
						edgesNumber--;
					}
				}
			}
		}
	}

	
	m_storedRepresentation=adjacencyMatrix;
	m_representation='a';
}




void SimpleGraph::GenerateRandomGraphBasedOnProbability(int verticesNumber, int probability)
{
	srand (time(NULL));
	int randomNumber;
	bool randomize = true; 
	std::vector<std::vector<int>> adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));

	if(!probability)
		randomize = false;

	if(randomize)
	{
		for (int i = 0; i < verticesNumber; ++i)
		{
			for (int j = i; j < verticesNumber; ++j)
			{
				randomNumber = rand() % 100 + 1;
				if((randomNumber <= probability) && (i != j))
				{
					adjacencyMatrix[i][j] = 1;
					adjacencyMatrix[j][i] = 1;
				}
			}
		}
	}
	
	m_storedRepresentation=adjacencyMatrix;
	m_representation='a';
}
				
