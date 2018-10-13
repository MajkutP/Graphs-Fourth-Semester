#ifndef SimpleGraph_h
#define SimpleGraph_h

#include <vector>
#include <iostream>
     
class SimpleGraph final  
{
public:
	/// Simple graph constructor. First argument represents input received from file that stores data 
	/// about graph. Second one represents type of representation - one of the following:
	/// - a - adjacency matrix
	/// - l - adjacency list
	/// - i - incidence matrix
	SimpleGraph(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation);

	// Konstruktor jednoargumentowy, w argumencie przyjmuje wektor stopni wierzchołków. Konstruuje obiekt reprezentujący graf o zadanych
	// stopniach wierzchołków.
	SimpleGraph(std::vector<int> degrees);

	/// This function prints graph informations to specified by argument place
	/// It can be for example file or standard output 
	void PrintGraph(std::ostream& placeToPrint) const ;

	/// Function returning character that describes current graph representation
	/// It can be a, l or i, depending on representation.
	char GetRepresentation() const;

	// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na macierz incydencji. W zaleznosci w jakiej
	// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
	// w tej reprezentacji. 
	void ChangeToIncidenceMatrix();

	// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na macierz sąsiedztwa. W zaleznosci w jakiej
	// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
	// w tej reprezentacji. 
	void ChangeToAdjacencyMatrix();

	// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na listę sąsiedztwa. W zaleznosci w jakiej
	// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
	// w tej reprezentacji. 
	void ChangeToAdjacencyList();
	
	// Funkcja randomizuja ulozenie krawedzi w grafie. Zamienia krawedz a-b, c-d na a-d, b-c pozostajac przy tym grafem prostym.
	// Funkcja operuje na liscie sasiedztwa, sprawdza wpierw warunek czy zamiana nie zaburzy warunkow istnienia grafu prostego, 
	// nastepnie sprawdza czy juz odpowiednie krawedzie nie instnieja dla uprzednio wylosowanych czterech losowych krawedzi.
	// Dodaje do listy nowe krawedzie, usuwa stare powiazania i na koncu sortuje i zamienia reprezentache na macierz sasiedztwa.
	void RandomizeSimpleGraph();
	
	// Funkcja sprawdza czy graf spójny jest hamiltonowski, dziala na zasadzie 'backtrackingu'. Zwraca falsz jezeli nie istnieje
	// zaden cykl hamiltonowski, w przeciwnym wypadku zwraca prawde i wypisuje znaleziony cykl (niekoniecznie jest tylko jeden)
	// Jako ze graf jest nieskierowany, to funkcja zaczyna prace dla indeksu zero w pomocniczej tablicy.
	bool HamiltonianCycle();

	/// Returns number of vertices in a graph
	unsigned GetNumberOfVertices() const {return m_storedRepresentation.size();}

	/// Returns graphic sequence that describes graph
	std::vector<int> GetGraphicSequence();

	std::vector<int> FindSizesOfConnectedComponents();

	std::vector<unsigned> FindMaxConnectedComponent();

	/// Checks if there is only one connected component in graph
	bool isGraphConnected();

	/// Finds Eulerian cycle on a graph
	void FindAndPrintEulerianCycle();


private:

	// Funkcja zamieniajaca liste sasiedztwa na macierz incydencji. Tworzy macierz o wymiarze l.wierzchołków x l.krawedzi, wypełnia zerami.
	// Uzupełnia kolejno kolumny macierzy. Każda kolumna reprezentuje osobna krawedz.
	void ChangeAdjacencyListToIncidenceMatrix();

	// Funkcja zamieniajaca macierz sasiedztwa na macierz incydencji. Tworzy macierz o wymiarze l.wierzchołków x l.krawedzi, wypełnia zerami.
	// Uzupełnia kolejno kolumumny macierzy. Sprawdza pomiędzy którymi wierzchołkami istnieje krawędź. Każda krawędź to osobna kolumna.
	void ChangeAdjacencyMatrixToIncidenceMatrix();

	// Funkcja zamieniajaca macierz incydencji na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
	// Sprawdza czy dla danego wierzchołka istnieje krawędź, jesli tak to poszukuje pozostałe wierzchołki przynależące do danej krawędzi.
	void ChangeIncidenceMatrixToAdjacencyMatrix();

	// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
	// Odczutej kolejno numer sasiada i zgodnie z jego numerem zapisuje go w macierzy na odowiedniej pozycji.
	void ChangeAdjacencyListToAdjacencyMatrix();

	// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
	// Przepisuje kolejno numery sasiadujacych wiercholkow. Usuwa na koncu pola w macierzy zawierajace wartosc 0.
	void ChangeAdjacencyMatrixToAdjacencyList();

	// Funkcja korzysta z funkcji zmieniającej macierz incydencji na macierz sąsiedztwa, nastęnie korzysta z funckji zamiany macierzy 
	// sąsiedztwa na listę sąsiedztwa.
	void ChangeInicidenceMatrixToAdjacencyList();

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
	void PrintHamiltonianCycle(int path[]);

	/// Vector of vectors containing stored graph reperesentation
	std::vector< std::vector <int> > m_storedRepresentation;

	/// Field representing type of stored graph representation
	/// It should be equal to one of following characters:
	/// - a - adjacency matrix
	/// - l - adjacency list
	/// - i - incidence matrix
	char m_representation;

};


// Funkcja generująca losowy graf k-regularny. Jako argument przyjmuje liczbe wierzchołków oraz stopień każdego z wierzchołków.
// Zwraca zrandomizowany graf k-regularny.
SimpleGraph generateKRegularGraph(int verticesNumber, int k);

// Funkcja w argumencie przyjmuje wektor liczb całkowitych. Sprawdza czy taka sekwencja liczb jest graficzna - jeśli tak zwraca true,
// w przeciwnym razie false.
bool IsSequenceGraphic(std::vector<int> degrees);

/// This function gets sequence of integers from user and returns it as a vector
std::vector<int> GetSequenceFromUser();

/// This function checks if sequence of ints can be used to generate Eulerian graph
bool IsSequenceEulerian(std::vector<int> degrees);

/// Returns eulerian graph
SimpleGraph* GenerateEulerianGraph();




#endif
