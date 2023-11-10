#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Graph.h"

//Zmienne opowiedzialne za czas dla algorytmow Brute Force i Branch and Bound
auto globalExecutionTimeBF = std::chrono::microseconds(0);
auto globalExecutionTimeBaB = std::chrono::microseconds(0);

int main()
{
    //Wstepna inicjalizacja struktury danych
    Graph myGraph(13);
    int choose = 0;
    while (choose != 9) {
        std::cout << "Interface:\n";
        std::cout << "1. Import data from file\n";
        std::cout << "2. Random data\n";
        std::cout << "3. Print matrix\n";
        std::cout << "4. Brute force alghoritm\n";
        std::cout << "5. Brute force to file \n";
        std::cout << "6. Branch and Bound alghoritm\n";
        std::cout << "7. Branch and Bound to file\n";
        std::cout << "8. Test on same data\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose[1-9]: "; std::cin >> choose;

        switch (choose)
        {
        //Import data from file
        case 1: {
            std::string file;
            std::cout << "Insert filename: "; std::cin >> file;
            myGraph.loadFromFile(file);
        }break;
        //Random data
        case 2: {
            int vertices;
            std::cout << "Insert ammount of vertices: "; std::cin >> vertices;
            myGraph.setNewVertices(vertices);
            int seed;
            std::cout << "Insert seed to generate random weight's: "; std::cin >> seed;
            myGraph.randomEdges(seed);
        }break;
        //Print matrix       
        case 3: {
            myGraph.printMatrix();
            std::cout << "\n";
        }break;
        //Brute force algorithm
        case 4: {
            std::pair<std::vector<int>, int> bruteForceResult = myGraph.bruteForceTSP(globalExecutionTimeBF);
            std::vector<int> bruteForcePath = bruteForceResult.first;
            int bruteForceTotalWeight = bruteForceResult.second;

            std::cout << "Shortest path using brute-force algorithm: ";
            for (int i = 0; i < bruteForcePath.size(); i++) {
                std::cout << bruteForcePath[i];
                if (i < bruteForcePath.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
            std::cout << "Path length: " << bruteForceTotalWeight << std::endl;
            std::cout << "Execution time: " << globalExecutionTimeBF.count() << std::endl;
            globalExecutionTimeBF = std::chrono::microseconds(0);
        } break;
        //Brute force to file
        case 5: {
            int seed, iterations;
            std::cout << "Algorithm for matrix sizes 5,6,7,8,9,10,11,12\n";
            std::cout << "Give seed to random edge's: "; std::cin >> seed;
            std::cout << "Give amount of iterations: "; std::cin >> iterations;
            std::vector<int> matrix_sizes = { 5,6,7,8,9,10,11,12 };
            for (int size : matrix_sizes) {
                std::ofstream outputFile("result_BF_" + std::to_string(size) + ".txt"); // Otwórz plik wynikowy dla danego rozmiaru
                if (!outputFile.is_open()) {
                    std::cerr << "Failed to open the output file: result_BF_" << size << ".txt" << std::endl;
                    return 1; // Wyjdź z błędem
                }

                for (int i = 0; i < iterations; i++) {
                    Graph myGraph(size);
                    myGraph.randomEdges(seed);
                    //Algorithm start
                    std::pair<std::vector<int>, int> bruteForceResult = myGraph.bruteForceTSP(globalExecutionTimeBF);
                    //Saving int file
                    outputFile << "Iteration BruteForce" << i << ":" << std::endl;
                    outputFile << "Execution time: " << globalExecutionTimeBF.count() << std::endl;

                    outputFile << "Shortest path using brute-force algorithm: ";
                    for (int i = 0; i < bruteForceResult.first.size(); i++) {
                        outputFile << bruteForceResult.first[i];
                        if (i < bruteForceResult.first.size() -1) {
                            outputFile << " -> ";
                        }
                    }
                    outputFile << std::endl;
                    outputFile << "Path length: " << bruteForceResult.second << std::endl;
                    outputFile << "Matrix weight:" << std::endl;
                    myGraph.printMatrixToFile(outputFile);
                    outputFile << "----------------------------------" << std::endl;
                    //
                    globalExecutionTimeBF = std::chrono::microseconds(0);
                }

                outputFile.close();
            }

        } break;
        //Branch and Bound algorithm
        case 6: {
            std::pair<std::vector<int>, int> branchAndBound = myGraph.callBranchAndBound(globalExecutionTimeBaB);
            std::vector<int> branchAndBoundPath = branchAndBound.first;
            int branchAndBoundTotalWeight = branchAndBound.second;

            std::cout << "Shortest path using BranchAndBound algorithm: ";
            for (int i = 0; i < branchAndBoundPath.size(); i++) {
                std::cout << branchAndBoundPath[i];
                if (i < branchAndBoundPath.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
            std::cout << "Path length: " << branchAndBoundTotalWeight << std::endl;
            std::cout << "Execution time: " << globalExecutionTimeBaB.count() << std::endl;
            globalExecutionTimeBaB = std::chrono::microseconds(0);
        } break;
        //Branch and Bound to file
        case 7: {
            int seed, iterations;
            std::cout << "Algorithm for matrix sizes 5,6,7,8,9,10,11,12\n";
            std::cout << "Give seed to random edge's: "; std::cin >> seed;
            std::cout << "Give amount of iterations: "; std::cin >> iterations;
            std::vector<int> matrix_sizes = { 5,6,7,8,9,10,11,12 };
            for (int size : matrix_sizes) {
                std::ofstream outputFile("result_BAB_" + std::to_string(size) + ".txt"); // Otwórz plik wynikowy dla danego rozmiaru
                if (!outputFile.is_open()) {
                    std::cerr << "Failed to open the output file: result_BAB_" << size << ".txt" << std::endl;
                    return 1; // Wyjdź z błędem
                }

                for (int i = 0; i < iterations ; i++) {
                    myGraph.setNewVertices(size);
                    myGraph.randomEdges(seed);

                    std::pair<std::vector<int>, int> branchAndBound = myGraph.callBranchAndBound(globalExecutionTimeBaB);
                    outputFile << "Iteration " << i << ":" << std::endl;
                    outputFile << globalExecutionTimeBaB.count() << std::endl;

                    outputFile << "Shortest path using brute-force algorithm: ";
                    for (int i = 0; i < branchAndBound.first.size(); i++) {
                        outputFile << branchAndBound.first[i];
                        if (i < branchAndBound.first.size() -1) {
                            outputFile << " -> ";
                        }
                    }
                    outputFile << std::endl;
                    outputFile << "Path length: " << branchAndBound.second << std::endl;

                    outputFile << "Matrix weight:" << std::endl;
                    myGraph.printMatrixToFile(outputFile);

                    outputFile << "----------------------------------" << std::endl;
                    globalExecutionTimeBaB = std::chrono::microseconds(0);
                }

                outputFile.close();
            }
        }break;
        //Test both algorithm on same data
        case 8: {
            int seed, iterations;
            std::cout << "BranchAndBound and BruteForce on same data\n";
            std::cout << "Algorithms for matrix sizes 5,6,7,8,9,10,11,12\n";
            std::cout << "Give seed to random edge's: "; std::cin >> seed;
            std::cout << "Give amount of iterations: "; std::cin >> iterations;
            std::vector<int> matrix_sizes = { 5,6,7,8,9,10,11,12 };
            for (int size : matrix_sizes) {
                std::ofstream outputFile("result_BF_BAB_" + std::to_string(size) + ".txt"); // Otwórz plik wynikowy dla danego rozmiaru
                if (!outputFile.is_open()) {
                    std::cerr << "Failed to open the output file: result_size_" << size << ".txt" << std::endl;
                    return 1; // Wyjdź z błędem
                }

                for (int i = 0; i < iterations; i++) {
                    Graph myGraph(size);
                    myGraph.randomEdges(seed);
                    //BruteForce
                    std::pair<std::vector<int>, int> bruteForceResult = myGraph.bruteForceTSP(globalExecutionTimeBF);
                    outputFile << "Iteration BruteForce" << i << ":" << std::endl;
                    outputFile << globalExecutionTimeBF.count() << std::endl;

                    outputFile << "Shortest path using brute-force algorithm: ";
                    for (int i = 0; i < bruteForceResult.first.size(); i++) {
                        outputFile << bruteForceResult.first[i];
                        if (i < bruteForceResult.first.size() - 1) {
                            outputFile << " -> ";
                        }
                    }
                    outputFile << std::endl;
                    outputFile << "Path length: " << bruteForceResult.second << std::endl;

                    outputFile << "Matrix weight:" << std::endl;
                    myGraph.printMatrixToFile(outputFile);

                    outputFile << "--------------------------------------------------" << std::endl;
                    outputFile << "--------------=BranchAndBound=--------------------" << std::endl;
                    globalExecutionTimeBF = std::chrono::microseconds(0);
                    //BranchAndBound
                    std::pair<std::vector<int>, int> branchAndBoundResult = myGraph.callBranchAndBound(globalExecutionTimeBaB);
                    outputFile << "Iteration BranchAndBound" << i << ":" << std::endl;
                    outputFile << globalExecutionTimeBaB.count() << std::endl;

                    outputFile << "Shortest path using BranchAndBound algorithm: ";
                    for (int i = 0; i < branchAndBoundResult.first.size(); i++) {
                        outputFile << branchAndBoundResult.first[i];
                        if (i < branchAndBoundResult.first.size() - 1) {
                            outputFile << " -> ";
                        }
                    }
                    outputFile << std::endl;
                    outputFile << "Path length: " << branchAndBoundResult.second << std::endl;

                    outputFile << "Matrix weight:" << std::endl;
                    myGraph.printMatrixToFile(outputFile);

                    outputFile << "----------------------------------" << std::endl;
                    globalExecutionTimeBaB = std::chrono::microseconds(0);

                }

                outputFile.close();
            }
        }break;
        //Exit
        case 9: {
            std::cout << "Exiting the program." << std::endl;
        }break;
        case 10: {
            std::cout << "Sprawozdanie\n";
            int seed, iterations;
            std::cout << "BranchAndBound and BruteForce on same data\n";
            std::cout << "Algorithms for matrix sizes 5,6,7,8,9,10,11,12\n";
            std::cout << "Give seed to random edge's: "; std::cin >> seed;
            std::cout << "Give amount of iterations: "; std::cin >> iterations;
            std::vector<int> matrix_sizes = { 5,6,7,8,9,10,11,12 };
            for (int size : matrix_sizes) {
                std::ofstream outputFile("result_BF_" + std::to_string(size) + ".txt"); // Otwórz plik wynikowy dla danego rozmiaru
                std::ofstream outputFile2("result_BAB_" + std::to_string(size) + ".txt");
                if (!outputFile.is_open()) {
                    std::cerr << "Failed to open the output file: result_size_" << size << ".txt" << std::endl;
                    return 1; // Wyjdź z błędem
                }

                for (int i = 0; i < (iterations); i++) {
                    Graph myGraph(size);
                    myGraph.randomEdges(seed);
                    //BruteForce
                    std::pair<std::vector<int>, int> bruteForceResult = myGraph.bruteForceTSP(globalExecutionTimeBF);
                    outputFile << globalExecutionTimeBF.count() << std::endl;
                    globalExecutionTimeBF = std::chrono::microseconds(0);
                    //BranchAndBound
                    std::pair<std::vector<int>, int> branchAndBoundResult = myGraph.callBranchAndBound(globalExecutionTimeBaB);
                    outputFile2 << globalExecutionTimeBaB.count() << std::endl;
                    globalExecutionTimeBaB = std::chrono::microseconds(0);

                }

                outputFile.close();
                outputFile2.close();
                std::cout << "================================KONIEC\n";
            }
        }break;
        default:
            std::cout << "Invalid choice. Please select a valid option (1-9)." << std::endl;
            break;
        }

    }
    return 0;
}


