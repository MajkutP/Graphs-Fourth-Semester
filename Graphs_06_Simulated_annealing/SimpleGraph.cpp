#include "SimpleGraph.h"
#include <random>
#include <ctime>

SimpleGraph::SimpleGraph()
{
	srand(time(0));
	unsigned verticesNumber = rand() % 10 + 4;
	std::vector< std::vector <int> > adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));
	std::vector< std::vector <int> > weightMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));
	for(unsigned i=0; i<verticesNumber; i++)
	{
		for(unsigned j=0; j<i; j++)
		{
			adjacencyMatrix[i][j] = 1;
			adjacencyMatrix[j][i] = 1;
			weightMatrix[i][j] = rand() % 20 + 1;
			weightMatrix[j][i] = weightMatrix[i][j];
		}
	}
	m_storedGraph = adjacencyMatrix;
	m_weightMatrix = weightMatrix;
	HamiltonianCycle();
}


SimpleGraph::SimpleGraph(std::vector<std::vector<int>> inputFromFile)
{
	m_weightMatrix = inputFromFile;
	unsigned verticesNumber=m_weightMatrix.size();
	std::vector< std::vector <int> > adjacencyMatrix(verticesNumber, std::vector<int>(verticesNumber, 0));
	for(unsigned i=0; i<verticesNumber; i++)
	{
		for(unsigned j=0; j<i; j++)
		{
			adjacencyMatrix[i][j] = 1;
			adjacencyMatrix[j][i] = 1;
		}
	}
	m_storedGraph = adjacencyMatrix;
	HamiltonianCycle();
}


void SimpleGraph::PrintGraph(std::ostream& placeToPrint) const 
{
	for (unsigned i = 0; i < m_storedGraph.size(); ++i)
	{
		for (unsigned j = 0; j < m_storedGraph.at(i).size(); ++j)
			placeToPrint<<m_storedGraph.at(i).at(j)<<" ";
		placeToPrint<<std::endl;
	}
}


void SimpleGraph::PrintWeightMatrix(std::ostream& placeToPrint) const 
{
	for (unsigned i = 0; i < m_weightMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < m_weightMatrix.at(i).size(); ++j)
			placeToPrint<<m_weightMatrix.at(i).at(j)<<" ";
		placeToPrint<<std::endl;
	}
}


int SimpleGraph::SumCosts(int path[])
{
	int cost=0;
	for(unsigned i=0; i < m_storedGraph.size()-1; i++)
 	{
 		cost += m_weightMatrix[path[i]][path[i+1]];
 	}
 	cost += m_weightMatrix[path[0]][path[m_storedGraph.size()-1]];
 	return cost;
}


bool SimpleGraph::HamiltonianCycle()
{
	int Vertices =  m_storedGraph.size();

    int *path = new int[Vertices];
    for (int i = 0; i < Vertices; i++)
        path[i] = -1;
 
    path[0] = 0;
    if ( HamiltonianCycleUtil(path, 1, Vertices) == false )
    {
        std::cout<<"Solution does not exist, graph is NOT Hamiltonian"<<std::endl;
        return false;
    }
 	m_storedCycle=path;
 	m_storedCost=SumCosts(path);
    PrintHamiltonianCycle();
    return true;
}


bool SimpleGraph::HamiltonianCycleUtil(int path[], int pos, int Vertices)
{
    if (pos == Vertices)
    {
        if ( m_storedGraph[ path[pos-1] ][ path[0] ] == 1 )
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
    if (m_storedGraph[ path[pos-1] ][ v ] == 0)
        return false;
 
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
 
    return true;
}


void SimpleGraph::PrintHamiltonianCycle()
{
	int Vertices =  m_storedGraph.size();

    std::cout<<"Following Hamiltonian cycle has been found: "<<std::endl;

    for (int i = 0; i < Vertices; i++)
        std::cout<<m_storedCycle[i]+1<<"->";
 
    std::cout<<m_storedCycle[0]+1<<std::endl;
    std::cout<<"This cycle cost: "<<m_storedCost<<std::endl;
    std::cout<<std::endl;
}


void SimpleGraph::SimulatedAnnealing()
{
	srand(time(0));
	double T = 0.0;
	int a, b, c, d = -1;
	int size = m_storedGraph.size();
	int* newCycle = new int[size];
	int newCost;
	
	for(int i=100; i>=0; i--)
	{
		T = 0.005*i*i;

		for(int it=0; it <= 1000; it++)
		{
			newCost=0;
			for(int i=0; i<size; i++)
				newCycle[i]=m_storedCycle[i];

			a =  rand() % size;
			if(a != size-1)
				b=a+1;
			else
				b=0;

			c = rand() % size;
			if(c != a || c != b)
			{
				if(c != size-1)
					d=c+1;
				else
					d=0;
			}

			while(c == a || c==b || d==a || d==b)
			{
				c = rand() % size;
				if(c != size-1)
					d=c+1;
				else
					d=0;
			}

			newCycle[b]=m_storedCycle[d];
			newCycle[d]=m_storedCycle[b];
			newCost=SumCosts(newCycle);

			// std::cout<<"New cycle: "<<std::endl;
			// for (int i = 0; i < size; i++)
		 //        std::cout<<newCycle[i]+1<<"->";
		 //    std::cout<<newCycle[0]+1<<std::endl;
		 //    std::cout<<"This cycle cost: "<<newCost<<std::endl;
		 //    std::cout<<std::endl;

		    if(newCost < m_storedCost)
		    {
		    	// std::cout<<"Accept new cycle.\n"<<std::endl;
		    	for(int i=0; i<size; i++)
					m_storedCycle[i]=newCycle[i];
		    	m_storedCost=newCost;
		    }
		    else
		    {
		    	double x = ((double) rand() / (RAND_MAX));
		    	if(x < exp(-(newCost - m_storedCost)/T))
		    	{
		    		// std::cout<<"Accept new cycle however new cost is higher than old.\n"<<std::endl;
		    		for(int i=0; i<size; i++)
						m_storedCycle[i]=newCycle[i];
		    		m_storedCost=newCost;
		    	}
		    }
		}
	}

	std::cout<<"Accepted cycle:"<<std::endl;
	for (int i = 0; i < size; i++)
		std::cout<<m_storedCycle[i]+1<<"->";
	 std::cout<<m_storedCycle[0]+1<<std::endl;
	std::cout<<"This cycle cost: "<<m_storedCost<<std::endl;
	std::cout<<std::endl;
}


void SimpleGraph::PrintCycleWeightMatrix(std::ostream& placeToPrint) const
{
	std::vector< std::vector <int> > weightMatrix(m_storedGraph.size(), std::vector<int>(m_storedGraph.size(), 0));
	for (unsigned i = 0; i < m_storedGraph.size()-1; ++i)
	{
        weightMatrix[m_storedCycle[i]][m_storedCycle[i+1]] = m_weightMatrix[m_storedCycle[i]][m_storedCycle[i+1]];
        weightMatrix[m_storedCycle[i+1]][m_storedCycle[i]] = m_weightMatrix[m_storedCycle[i+1]][m_storedCycle[i]];
	}
	weightMatrix[m_storedCycle[0]][m_storedCycle[m_storedGraph.size()-1]] = m_weightMatrix[m_storedCycle[0]][m_storedCycle[m_storedGraph.size()-1]];
	weightMatrix[m_storedCycle[m_storedGraph.size()-1]][m_storedCycle[0]] = m_weightMatrix[m_storedCycle[m_storedGraph.size()-1]][m_storedCycle[0]];
	for (unsigned i = 0; i < weightMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < weightMatrix.at(i).size(); ++j)
			placeToPrint<<weightMatrix.at(i).at(j)<<" ";
		placeToPrint<<std::endl;
	}
}
