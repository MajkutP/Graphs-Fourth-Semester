#ifndef SimpleGraph_h
#define SimpleGraph_h

#include <vector>
#include <iostream>
     
class SimpleGraph final  
{
public:

	SimpleGraph();

	/// Simple graph constructor. First argument represents input received from file that stores data 
	/// about graph.
	SimpleGraph(std::vector<std::vector<int>> inputFromFile);

	/// This function prints graph informations to specified by argument place
	/// It can be for example file or standard output 
	void PrintGraph(std::ostream& placeToPrint) const ;

	void PrintWeightMatrix(std::ostream& placeToPrint) const;

	int SumCosts(int path[]);

	// Funkcja sprawdza czy graf spójny jest hamiltonowski, dziala na zasadzie 'backtrackingu'. Zwraca falsz jezeli nie istnieje
	// zaden cykl hamiltonowski, w przeciwnym wypadku zwraca prawde i wypisuje znaleziony cykl (niekoniecznie jest tylko jeden)
	// Jako ze graf jest nieskierowany, to funkcja zaczyna prace dla indeksu zero w pomocniczej tablicy.
	bool HamiltonianCycle();

	void SimulatedAnnealing();

	void PrintCycleWeightMatrix(std::ostream& placeToPrint) const;

private:

	/// This  function counts number of edges in a graph and returns it. 
	/// Works for every type of representation.
	int EdgesCounter() const;
	
	// Funckja opierajaca sie na rekurencji rozwiazujaca problem hamiltonowski. W pierwszym wypadku sprawdza czy wszystkie wierzcholki sa juz 
	// zawarte w tablicy, jezeli tak i istnieje krawedz z ostatniego do pierwszego wierzcholka to zwraca true, w przeciwnym wypadku false.
	// W drugim przypadku sprawdza kolejne wierzcholki poza zerowym, wywolujac funkcje IsSafe(). Jezeli tak to wywoluja samo siebie, jezeli kolejny
	// obieg funkcji zabrania dodania konkretnego wierzcholka to usuwa nowo dodany wierzcholek do listy cyklu. Ostatecznie, jezeli zaden wierzcholek
	// nie moze byc dodany, to funkcja zwraca false.
	bool HamiltonianCycleUtil(int path[], int position, int Vertices);

	// Funkcja sprawdza czy wierzcholek v moze byc dodany do tablicy cyklu hamiltonowskiego. Sprawdza dwa warunki.
	// Pierwszy czy wierzcholek jest sasiadem poprzednio dodanego wierzcholka, drugi warunek sprawdza czy wierzcholek
	// nie byl juz uprzzednio dodany.
	bool IsSafe(int v, int path[], int position);

	// Funkcja zwracaja efekt sprawdzania cyklu hamiltonowskiego na ekran. Wypisuje na ekran znaleziony cykl Hamiltona
	// Funkcja ta nie zostaje wywolana, jesli graf nie posiada takiego cyklu
	void PrintHamiltonianCycle();

	/// Vector of vectors containing stored graph reperesentation
	std::vector< std::vector <int> > m_storedGraph;

	/// Macierz zawierajaca wagi krawedzi
	std::vector< std::vector <int> > m_weightMatrix;

	/// Wektor zawierający aktualny cykl Hamiltona
	int* m_storedCycle;

	/// Dlugosc aktualnie przechowywanego cyklu
	int m_storedCost;
};

#endif