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
    int V; //Wierzcho³ki
    std::vector<std::vector<int>> Matrix; //Macierz alokowana dynamicznie
    int checkSum = 0;

public:
    Graph(int vertices); // Konstruktor klasy Graph, przyjmuje liczbê wierzcho³ków jako argument.
    int sizeT(); // Zwraca liczbê wierzcho³ków w strukturze.
    void setNewVertices(int new_vertices); // Aktualizuje liczbê wierzcho³ków w strukturze.
    void addEdge(int start, int end, int weight); // Dodaje krawêdŸ miêdzy dwoma wierzcho³kami w strukturze z okreœlonym wag¹.
    void loadFromFile(const std::string& filename); // Wczytuje dane z pliku i tworzy strukturze na ich podstawie.
    void printMatrix(); // Wyœwietla macierz s¹siedztwa struktury w konsoli.
    void printMatrixToFile(std::ostream& os); // Zapisuje macierz s¹siedztwa struktury do strumienia wyjœciowego
    void randomEdges(int seed); // Tworzy losowe krawêdzie w strukturze na podstawie podanego ziarna (seed)
    void swap(int& a, int& b); // Zamienia wartoœci dwóch zmiennych przekazanych jako argumenty.
    bool nextPermutation(std::vector<int>& arr); // Wykonuje nastêpn¹ permutacjê w podanej tablicy arr. Zwraca true, jeœli istnieje kolejna permutacja, w przeciwnym razie false.
    std::pair<std::vector<int>, int> bruteForceTSP(std::chrono::microseconds &globalExecutionTimeBF); // Wykonuje algorytm Brute Force w celu znalezienia najkrótszej œcie¿ki komiwoja¿era (TSP). Zwraca parê: (najlepsza œcie¿ka, jej koszt) oraz zapisuje czas wykonania w globalExecutionTimeBF.
    // Wywo³uje algorytm Branch and Bound w celu znalezienia najkrótszej œcie¿ki komiwoja¿era (TSP). Zwraca parê: (najlepsza œcie¿ka, jej koszt) oraz zapisuje czas wykonania w globalExecutionTimeBaB.
    std::pair<std::vector<int>, int> callBranchAndBound(std::chrono::microseconds &globalExecutionTimeBaB);
    // Algorytm Branch and Bound, który jest wywo³ywany przez callBranchAndBound.Przeszukuje przestrzeñ stanów w celu znalezienia najkrótszej œcie¿ki komiwoja¿era 
    void branchAndBound(int city, int costSoFar, std::vector<int>& bestPath, std::vector<bool>& visitedCity, std::vector<int>& currentPath, int& bestCost);
};


