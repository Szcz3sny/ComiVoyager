#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

class Graph
{
private:
    int V; //Wierzcho�ki
    std::vector<std::vector<int>> Matrix; //Macierz alokowana dynamicznie
    int checkSum = 0;

public:
    Graph(int vertices); // Konstruktor klasy Graph, przyjmuje liczb� wierzcho�k�w jako argument.
    int sizeT(); // Zwraca liczb� wierzcho�k�w w strukturze.
    void setNewVertices(int new_vertices); // Aktualizuje liczb� wierzcho�k�w w strukturze.
    void addEdge(int start, int end, int weight); // Dodaje kraw�d� mi�dzy dwoma wierzcho�kami w strukturze z okre�lonym wag�.
    void loadFromFile(const std::string& filename); // Wczytuje dane z pliku i tworzy strukturze na ich podstawie.
    void printMatrix(); // Wy�wietla macierz s�siedztwa struktury w konsoli.
    void printMatrixToFile(std::ostream& os); // Zapisuje macierz s�siedztwa struktury do strumienia wyj�ciowego
    void randomEdges(int seed); // Tworzy losowe kraw�dzie w strukturze na podstawie podanego ziarna (seed)
    void swap(int& a, int& b); // Zamienia warto�ci dw�ch zmiennych przekazanych jako argumenty.
    bool nextPermutation(std::vector<int>& arr); // Wykonuje nast�pn� permutacj� w podanej tablicy arr. Zwraca true, je�li istnieje kolejna permutacja, w przeciwnym razie false.
    std::pair<std::vector<int>, int> bruteForceTSP(std::chrono::microseconds &globalExecutionTimeBF); // Wykonuje algorytm Brute Force w celu znalezienia najkr�tszej �cie�ki komiwoja�era (TSP). Zwraca par�: (najlepsza �cie�ka, jej koszt) oraz zapisuje czas wykonania w globalExecutionTimeBF.
    // Wywo�uje algorytm Branch and Bound w celu znalezienia najkr�tszej �cie�ki komiwoja�era (TSP). Zwraca par�: (najlepsza �cie�ka, jej koszt) oraz zapisuje czas wykonania w globalExecutionTimeBaB.
    std::pair<std::vector<int>, int> callBranchAndBound(std::chrono::microseconds &globalExecutionTimeBaB);
    // Algorytm Branch and Bound, kt�ry jest wywo�ywany przez callBranchAndBound.Przeszukuje przestrze� stan�w w celu znalezienia najkr�tszej �cie�ki komiwoja�era 
    void branchAndBound(int city, int costSoFar, std::vector<int>& bestPath, std::vector<bool>& visitedCity, std::vector<int>& currentPath, int& bestCost);
};


