#include "SimpleGraph.h"
#include <algorithm>
#include <stack>

SimpleGraph::SimpleGraph(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation)
{
	m_storedRepresentation = inputFromFile;
	m_representation = typeOfRepresentation;
}

SimpleGraph::SimpleGraph(std::vector<int> degrees)
{
	std::sort(degrees.begin(), degrees.end(), [](const int a, const int b) {return a > b; });
	int maxEdges = degrees.size()*(degrees.size()-1)/2;
	std::vector<std::vector<int>> incidenceMatrix(degrees.size(), std::vector<int>(maxEdges, 0));

	int counter=0;
	for (unsigned i = 0; i < degrees.size(); ++i)
	{
		int j=i+1;
		while(degrees[i])
		{
			if(degrees[j])
			{
				incidenceMatrix[i][counter]=1;
				incidenceMatrix[j][counter]=1;
				
				degrees[i]--;
				degrees[j]--;
				counter++;
			}
			j++;
		}

		for(unsigned k=i+1; k<degrees.size(); k++)
        {
            for(unsigned j=k+1; j<degrees.size(); j++)
            {
                if(degrees[k]<degrees[j])
                {
                    int tempDeg=degrees[j];
                    degrees[j]=degrees[k];
                    degrees[k]=tempDeg;

                    std::vector<int> tempVec(incidenceMatrix[j]);
                    incidenceMatrix[j]=incidenceMatrix[k];
                    incidenceMatrix[k]=tempVec;
                }
            }
        }
	}
	m_storedRepresentation=incidenceMatrix;
	m_representation='i';
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
}

void SimpleGraph::ChangeToAdjacencyMatrix()
{
	if(m_representation=='l')
		ChangeAdjacencyListToAdjacencyMatrix();
	else if(m_representation=='i')
		ChangeIncidenceMatrixToAdjacencyMatrix();

}
	
void SimpleGraph::ChangeToAdjacencyList()
{
	if(m_representation=='a')
		ChangeAdjacencyMatrixToAdjacencyList();
	else if(m_representation=='i')
		ChangeInicidenceMatrixToAdjacencyList();
}

void SimpleGraph::RandomizeSimpleGraph()
{
	srand (time(NULL));
	int rand_a, rand_b, rand_c, rand_d;
	int temp_b, temp_d;
	int many_times = 1000;
	bool randomize;

	if(m_representation != 'l')
		ChangeToAdjacencyList();

	for(int i = 0; i < many_times; i++)
	{
		randomize = false;
		rand_a = rand() % m_storedRepresentation.size();        
		rand_c = rand() % m_storedRepresentation.size();
		
		if (m_storedRepresentation.at(rand_a).size() == 0 || m_storedRepresentation.at(rand_c).size() == 0)
			continue;
		
		rand_b = rand() % m_storedRepresentation.at(rand_a).size();
		rand_d = rand() % m_storedRepresentation.at(rand_c).size();
		temp_b = rand_b;
		temp_d = rand_d;
		rand_b = m_storedRepresentation[rand_a][rand_b];
		rand_d = m_storedRepresentation[rand_c][rand_d];
		rand_a += 1;
		rand_c += 1;


		if( (rand_a != rand_d) && (rand_b != rand_c) ) randomize = true;

		for(unsigned j = 0; j < m_storedRepresentation.at(rand_a-1).size(); j++)
		{
			if(m_storedRepresentation[rand_a-1][j] == rand_d) randomize = false;
		}

		for(unsigned j = 0; j < m_storedRepresentation.at(rand_b-1).size(); j++)
		{
			if(m_storedRepresentation[rand_b-1][j] == rand_c) randomize = false;
		}


		if(randomize)
		{
		 	m_storedRepresentation.at(rand_a-1).push_back(rand_d);
		 	m_storedRepresentation.at(rand_d-1).push_back(rand_a);
		 	m_storedRepresentation.at(rand_b-1).push_back(rand_c);
		 	m_storedRepresentation.at(rand_c-1).push_back(rand_b);
		
		 	m_storedRepresentation.at(rand_a-1).erase(m_storedRepresentation.at(rand_a-1).begin()+temp_b);
		 	m_storedRepresentation.at(rand_c-1).erase(m_storedRepresentation.at(rand_c-1).begin()+temp_d);
		 
		 	for(unsigned j = 0; j < m_storedRepresentation.at(rand_b-1).size(); j++)
		 	{
		 	 	if(m_storedRepresentation[rand_b-1][j] == rand_a)
		 	 		m_storedRepresentation.at(rand_b-1).erase(m_storedRepresentation.at(rand_b-1).begin()+j);
		 	}
		 	
		 	for(unsigned j = 0; j < m_storedRepresentation.at(rand_d-1).size(); j++)
		 	{
		 		if(m_storedRepresentation[rand_d-1][j] == rand_c)
		 			m_storedRepresentation.at(rand_d-1).erase(m_storedRepresentation.at(rand_d-1).begin()+j);
		 	}
		 	
			for(unsigned j = 0; j < m_storedRepresentation.size(); ++j)
			{
				std::sort(m_storedRepresentation.at(j).begin(), m_storedRepresentation.at(j).end(), [](const int a, const int b) {return a > b; });
			}

		 }
	}
	ChangeToAdjacencyMatrix();
}


std::vector<int> SimpleGraph::FindSizesOfConnectedComponents()
{
	char oldRepresentation = m_representation;
	ChangeToAdjacencyList();
	std::vector<unsigned> vertices (m_storedRepresentation.size(), 0);
	std::stack<unsigned> stackForVertices;
	unsigned currentConnectedComponent = 0;
	for (unsigned i = 0; i<vertices.size(); ++i)
	{
		if (vertices[i]>0)
			continue;

		currentConnectedComponent++;

		stackForVertices.push(i);
		vertices[i] = currentConnectedComponent;

		while (stackForVertices.empty() == false) 
		{
			unsigned v = stackForVertices.top();
			stackForVertices.pop();
			for (unsigned j = 0; j<m_storedRepresentation.at(v).size(); ++j)
			{
				unsigned u = m_storedRepresentation.at(v).at(j) - 1;
				if (vertices.at(u)>0)
					continue;
				stackForVertices.push(u);
				vertices.at(u) = currentConnectedComponent;
			}
		}
	}

	std::vector <int> sizesOfComponents (currentConnectedComponent, 0);
	for (unsigned i =1; i<=currentConnectedComponent; ++i) 
	{
		for (unsigned j= 0; j<vertices.size(); ++j)
		{
			if (vertices[j]==i)
				sizesOfComponents.at(i-1)++;
		}
	}

	if (oldRepresentation=='a')
		ChangeToAdjacencyMatrix();
	else if (oldRepresentation == 'i')
		ChangeToIncidenceMatrix();


	return sizesOfComponents;

}

std::vector<unsigned> SimpleGraph::FindMaxConnectedComponent()
{
	/// save old representation to come back to it after algorithm has ended
	char oldRepresentation = m_representation;
	ChangeToAdjacencyList();

	std::vector<unsigned> vertices (m_storedRepresentation.size(), 0);
	std::stack<unsigned> stackForVertices;
	unsigned currentConnectedComponent = 0;

	for (unsigned i = 0; i<vertices.size(); ++i)
	{
		if (vertices[i]>0)
			continue;

		currentConnectedComponent++;

		stackForVertices.push(i);
		vertices[i] = currentConnectedComponent;

		while (stackForVertices.empty() == false) /// DFS using stack
		{
			unsigned v = stackForVertices.top();
			stackForVertices.pop();
			for (unsigned j = 0; j<m_storedRepresentation.at(v).size(); ++j)
			{
				unsigned u = m_storedRepresentation.at(v).at(j) - 1;
				if (vertices.at(u)>0)
					continue;
				stackForVertices.push(u);
				vertices.at(u) = currentConnectedComponent;
			}
		}
	}

	std::vector <unsigned> sizesOfComponents (currentConnectedComponent, 0);
	for (unsigned i =1; i<=currentConnectedComponent; ++i) 
	{
		for (unsigned j= 0; j<vertices.size(); ++j)
			if (vertices[j]==i)
				sizesOfComponents.at(i-1)++;
	}

	std::vector <unsigned> maxComponent;
	unsigned numberOfMax = std::distance(sizesOfComponents.begin(), std::max_element(sizesOfComponents.begin(), sizesOfComponents.end())) + 1; /// find max component
	for (unsigned j= 0; j<vertices.size(); ++j) /// print max component
		if (vertices[j]==numberOfMax)
			maxComponent.push_back(j+1);

	if (oldRepresentation=='a')
		ChangeToAdjacencyMatrix();
	else if (oldRepresentation == 'i')
		ChangeToIncidenceMatrix();

	return maxComponent;
}


SimpleGraph generateKRegularGraph(int verticesNumber, int k)
{
	while(verticesNumber<=0)
	{
		std::cout<<"Too small number of vertices. Try again. "<<std::endl;
		std::cout<<"Enter number of vertices: ";
		std::cin>>verticesNumber;
	}
	if(k<=0)
	{
		std::vector<std::vector<int>> adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));
		SimpleGraph graph(adjacencyMatrix, 'a');
		return graph;
	}
	std::vector<int> degrees(verticesNumber, k);

	while(IsSequenceGraphic(degrees) == false)
	{
		std::cout<<"Sequence is not graphic. Try again. "<<std::endl;
		std::cout<<"Enter number of vertices: ";
		std::cin>>verticesNumber;
		std::cout<<"Enter k number: ";
		std::cin>>k;
		while(verticesNumber<=0)
		{
			std::cout<<"Too small number of vertices. Try again. "<<std::endl;
			std::cout<<"Enter number of vertices: ";
			std::cin>>verticesNumber;
		}
		if(k<=0)
		{
			std::vector<std::vector<int>> adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));
			SimpleGraph graph(adjacencyMatrix, 'a');
			return graph;
		}

		degrees.resize(verticesNumber);
		for(unsigned i=0; i<degrees.size(); i++)
			degrees[i]=k;
	}
	SimpleGraph graph(degrees);
	graph.RandomizeSimpleGraph();
	return graph;
}


std::vector<int> SimpleGraph::GetGraphicSequence()
{
	std::vector<int> graphicSequence;

	char oldRepresentation = m_representation;
	ChangeToAdjacencyList();

	for (unsigned i = 0; i<m_storedRepresentation.size(); ++i)
		graphicSequence.push_back(m_storedRepresentation.at(i).size());

	if (oldRepresentation=='a')
		ChangeToAdjacencyMatrix();
	else if (oldRepresentation == 'i')
		ChangeToIncidenceMatrix();

	return graphicSequence;
}


bool SimpleGraph::isGraphConnected()
{
	if (m_storedRepresentation.size() != FindMaxConnectedComponent().size())
		return false;
	return true;
}


bool IsSequenceGraphic(std::vector<int> degrees)
{
	bool graphic=true;
	int sum=0;

	for(unsigned i=0; i<degrees.size(); i++)
		sum+=degrees[i];

	if ( sum % 2 != 0) 
		graphic=false;
	else
		std::sort(degrees.begin(), degrees.end(), [](const int a, const int b) {return a > b; });

	while ((degrees[0]!=0) && (graphic==1))
	{
		sum=0;

		for(unsigned i=1; i<degrees.size(); i++)
			if (degrees[i]!=0) 
				sum++;

		if (degrees[0]>sum) 
			graphic=false;
		else 
			for(int i=1; i<=degrees[0]; i++) 
				degrees[i]--;

		degrees[0]=0;
		std::sort(degrees.begin(), degrees.end(), [](const int a, const int b) {return a > b; });
	}

	if (graphic)
		std::cout<<"Sequence is graphic."<<std::endl;
	else
		std::cout<<"This sequence is not graphic. "<<std::endl;

	return graphic;
}


bool SimpleGraph::HamiltonianCycle()
{
	if(m_representation != 'a')
		ChangeToAdjacencyMatrix();

	int Vertices =  m_storedRepresentation.size();

    int *path = new int[Vertices];
    for (int i = 0; i < Vertices; i++)
        path[i] = -1;
 
    path[0] = 0;
    if ( HamiltonianCycleUtil(path, 1, Vertices) == false )
    {
        std::cout<<"Solution does not exist, graph is NOT Hamiltonian"<<std::endl;
        return false;
    }
 
    PrintHamiltonianCycle(path);
    return true;
}

 
bool SimpleGraph::HamiltonianCycleUtil(int path[], int pos, int Vertices)
{
    if (pos == Vertices)
    {
        if ( m_storedRepresentation[ path[pos-1] ][ path[0] ] == 1 )
           return true;
        else
           return false;
    }
 
    for (int v = 1; v < Vertices; ++v)
    {
        if (IsSafe(v, path, pos))
        {
            path[pos] = v;
 
            if (HamiltonianCycleUtil (path, pos+1, Vertices) == true)
                return true;
 
            path[pos] = -1;
        }
    }
 
    return false;
}

bool SimpleGraph::IsSafe(int v, int path[], int pos)
{
    if (m_storedRepresentation[ path[pos-1] ][ v ] == 0)
        return false;
 
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
 
    return true;
}


void SimpleGraph::PrintHamiltonianCycle(int path[])
{
	int Vertices =  m_storedRepresentation.size();

    std::cout<<"Solution Exists:"<<std::endl;
    std::cout<<"Following Hamiltonian cycle has been found: "<<std::endl;

    for (int i = 0; i < Vertices; i++)
        std::cout<<path[i]+1<<"->";
 
    std::cout<<path[0]+1<<std::endl;
}


bool IsSequenceEulerian(std::vector<int> degrees)
{
	if (!IsSequenceGraphic(degrees))
		return false;

	for (unsigned i = 0; i<degrees.size(); ++i)
		if (degrees.at(i) % 2 != 0)
			return false;

	return true;
}


SimpleGraph* GenerateEulerianGraph()
{
	std::vector<int> degrees;
	while (true)
	{
		degrees = GetSequenceFromUser();

		if (!IsSequenceEulerian(degrees))
		{
			std::cout<<"You can not generate Eulerian Graph using this sequence. Try again."<<std::endl<<std::endl;
			continue;
		}		
		break;
	}

	SimpleGraph * eulerianGraph = new SimpleGraph(degrees);

	if (eulerianGraph->isGraphConnected())
	{
		std::cout<<"Do you want to randomize this graph?"<<std::endl;
		std::cout<<"1.Yes"<<std::endl;
		std::cout<<"2.No"<<std::endl;
		while (true)
		{
			int userInput;
			if (std::cin>>userInput)
			{
				if (userInput==2)
					return eulerianGraph;
				else if (userInput==1)
					break;
				else continue;
			}
		}
	}

	for (unsigned i = 0; i<1000; ++i)
		eulerianGraph->RandomizeSimpleGraph();

	while (true)
	{
		if (eulerianGraph->isGraphConnected())
			break;

		std::vector<int> size = eulerianGraph->FindSizesOfConnectedComponents();
		int numberOfIsolatedVertices = 0;
		for (unsigned i = 0; i<size.size(); ++i)
			if (size.at(i)==1)
				numberOfIsolatedVertices ++;

		if (eulerianGraph->FindMaxConnectedComponent().size() + numberOfIsolatedVertices == eulerianGraph->GetNumberOfVertices())
			break;

		eulerianGraph->RandomizeSimpleGraph();
	}
	return eulerianGraph;
}

void SimpleGraph::FindAndPrintEulerianCycle()
{
	std::vector<int> degreeSequence = GetGraphicSequence();
	if (!IsSequenceEulerian(degreeSequence))
	{
		std::cout<<"This graph is not Eulerian. There is no Euler cycle. Aborting. "<<std::endl;
		return;
	}

	ChangeToAdjacencyList();
	std::vector<std::vector<int>> copy = m_storedRepresentation;
	int currentVertex = 0;

	for (unsigned i = 0; i<m_storedRepresentation.size(); ++i)
	{
		if (m_storedRepresentation.at(i).size() != 0)
		{
			currentVertex = i;
			break;
		}
	}

	std::vector<int> eulerianCycle;
	eulerianCycle.push_back(currentVertex);
	int deletedVertices = 0;

	std::vector<int> helper= FindSizesOfConnectedComponents();
	int numberOfIsolatedVertices =0;

	for (unsigned i =0; i< helper.size(); ++i)
		if (helper.at(i)==1)
			numberOfIsolatedVertices++;

	while(true)
	{
		if(m_storedRepresentation.at(currentVertex).size()==0)
			break;
		int nextVertex;

		for (unsigned i =0; i<m_storedRepresentation.at(currentVertex).size(); ++i)
		{
			nextVertex = m_storedRepresentation.at(currentVertex).at(i);
			m_storedRepresentation.at(currentVertex).erase(m_storedRepresentation.at(currentVertex).begin() + i);
			if (m_storedRepresentation.at(currentVertex).size()==0)
				deletedVertices++;

			m_storedRepresentation.at(nextVertex-1).erase(std::remove(m_storedRepresentation.at(nextVertex-1).begin(), m_storedRepresentation.at(nextVertex-1).end(), 
				currentVertex+1), m_storedRepresentation.at(nextVertex-1).end());
			if (m_storedRepresentation.at(nextVertex-1).size()== 0)
				deletedVertices++;


			if (FindMaxConnectedComponent().size() != 1 && ((m_storedRepresentation.at(nextVertex-1).size()==0 && m_storedRepresentation.at(currentVertex).size()>0) 
				|| FindMaxConnectedComponent().size() != m_storedRepresentation.size() - deletedVertices - numberOfIsolatedVertices))
			{
				if (m_storedRepresentation.at(currentVertex).size()==0)
					deletedVertices--;
				if (m_storedRepresentation.at(nextVertex-1).size()== 0)
					deletedVertices--;
				auto iter = m_storedRepresentation.at(currentVertex).begin();
				m_storedRepresentation.at(currentVertex).insert(iter + i, nextVertex);
				iter = m_storedRepresentation.at(nextVertex-1).begin();
				m_storedRepresentation.at(nextVertex-1).insert(iter, currentVertex+1);
				continue;
			}


			if (FindMaxConnectedComponent().size() == 1 || FindMaxConnectedComponent().size() == m_storedRepresentation.size() - deletedVertices - numberOfIsolatedVertices)
			{
				eulerianCycle.push_back(nextVertex-1);
				currentVertex = nextVertex-1;
				break;
			}	
		}
	}
	m_storedRepresentation = copy;
	ChangeToAdjacencyMatrix();

	for (unsigned i =0; i<eulerianCycle.size()-1; ++i)
		std::cout<<eulerianCycle.at(i)+1<<"->";
	std::cout<<eulerianCycle.at(eulerianCycle.size()-1)+1<<std::endl;
}


std::vector<int> GetSequenceFromUser()
{
	std::cout<<"Please enter sequence of integers (type any letter to stop)."<<std::endl;
	int number;
	std::vector<int> deg;

	while (true)
	{
		while (std::cin>>number)
			deg.push_back(number);

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (deg.size() == 0)
		{
			std::cout<<"No valid sequence was entered. Try again. "<<std::endl;
			continue;
		}
		break;

	}		
	return deg;
}