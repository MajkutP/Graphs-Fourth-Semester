#ifndef SimpleGraph_h
#define SimpleGraph_h

#include <vector> /// std::vector
#include <utility> /// std::pair
#include "ui_mainwindow.h"

/// Class that represents simple graph
class SimpleGraph final  
{
public:
	/// Simple graph constructor. First argument represents input received from file that stores data 
	/// about graph. Second one represents type of representation - one of the following:
	/// - a - adjacency matrix
	/// - l - adjacency list
	/// - i - incidence matrix
	SimpleGraph(std::vector<std::vector<int>> inputFromFile, char typeOfRepresentation);

	/// This function prints graph informations to specified by argument place
    void PrintGraph(Ui::MainWindow& place) const ;

	/// Function returning character that describes current graph representation
	/// It can be a, l or i, depending on representation.
	char GetRepresentation() const;
	
    /// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na macierz incydencji. W zaleznosci w jakiej
    /// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
    /// w tej reprezentacji.
	void ChangeToIncidenceMatrix();

    /// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na macierz sąsiedztwa. W zaleznosci w jakiej
    /// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
    /// w tej reprezentacji.
	void ChangeToAdjacencyMatrix();

    /// Funkcja zamieniajaca reprezentacje grafu przechowywana przez obiekt klasy SimpleGraph na listę sąsiedztwa. W zaleznosci w jakiej
    /// reprezentacji jest graf funkcja wywoluje inna funkcje zamieniajaca, lub wypisuje informacje ze graf jest juz
    /// w tej reprezentacji.
	void ChangeToAdjacencyList();

    /// Funkcja generujaca graf losowy G(n, p) o zadanej liczbie wierzcholkow oraz prawdopodobienstwa wystapienia kazdej z krawedzi.
    /// Drugi argument traktowany jest jako procent. Na podstawie losowanych liczb generuje się nowe polaczenia w grafie.
    void GenerateRandomGraphBasedOnProbability(int verticesNumber, int probability);

    /// Funkcja generujaca graf losowy G(n, l) o zadanej liczbie wierzcholkow oraz gestosci. Jeśli drugi argument jest liczba
    /// ujemna zamieniamy ja na dodatnia, jesli jest mniejszy od 1 traktujemy go jako gestosc (jaka czesc maksymalnej liczby
    /// krawedzi ma sie znalezc w grafie), jesli wiekszy od 1 traktujemy go jako ilosc krawedzi.
    void GenerateRandomGraphBasedOnDensity(int verticesNumber, double density);

    /// Function that returns vector of edges. Edge is represented as std::pair<int, int>
    /// where template arguments stand for vetrices connected by the edge. This function
    /// is designed to be used during the process of printing graph as a circle.
    std::vector<std::pair<int, int>> GetEdges();

    /// Simple function that returns number of vertices in the stored graph
    unsigned getNumberOfVertices() const;

    /// Getter function that returns reference to stored graph representation
    const std::vector< std::vector <int> >& GetRepresentationVector() const;


private:

    /// Funkcja zamieniajaca liste sasiedztwa na macierz incydencji. Tworzy macierz o wymiarze l.wierzchołków x l.krawedzi, wypełnia zerami.
    /// Uzupełnia kolejno kolumny macierzy. Każda kolumna reprezentuje osobna krawedz.
	void ChangeAdjacencyListToIncidenceMatrix();

    /// Funkcja zamieniajaca macierz sasiedztwa na macierz incydencji. Tworzy macierz o wymiarze l.wierzchołków x l.krawedzi, wypełnia zerami.
    /// Uzupełnia kolejno kolumumny macierzy. Sprawdza pomiędzy którymi wierzchołkami istnieje krawędź. Każda krawędź to osobna kolumna.
	void ChangeAdjacencyMatrixToIncidenceMatrix();

    /// Funkcja zamieniajaca macierz incydencji na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
    /// Sprawdza czy dla danego wierzchołka istnieje krawędź, jesli tak to poszukuje pozostałe wierzchołki przynależące do danej krawędzi.
	void ChangeIncidenceMatrixToAdjacencyMatrix();

    /// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
    /// Odczutej kolejno numer sasiada i zgodnie z jego numerem zapisuje go w macierzy na odowiedniej pozycji.
	void ChangeAdjacencyListToAdjacencyMatrix();

    /// Funkcja zamieniajaca macierz sasiedztwa na liste sasiedztwa. Tworzy macierz o wymiarze l.wierzcholkow x l.wierzcholkow, wypelnia zerami.
    /// Przepisuje kolejno numery sasiadujacych wiercholkow. Usuwa na koncu pola w macierzy zawierajace wartosc 0.
	void ChangeAdjacencyMatrixToAdjacencyList();

    /// Funkcja korzysta z funkcji zmieniającej macierz incydencji na macierz sąsiedztwa, nastęnie korzysta z funckji zamiany macierzy
    /// sąsiedztwa na listę sąsiedztwa.
	void ChangeInicidenceMatrixToAdjacencyList();

	/// This  function counts number of edges in a graph and returns it. 
	/// Works for every type of representation.
	int EdgesCounter() const;

	/// Vector of vectors containing stored graph reperesentation
	std::vector< std::vector <int> > m_storedRepresentation;

	/// Field representing type of stored graph representation
	/// It should be equal to one of following characters:
	/// - a - adjacency matrix
	/// - l - adjacency list
	/// - i - incidence matrix
	char m_representation;

};

#endif
