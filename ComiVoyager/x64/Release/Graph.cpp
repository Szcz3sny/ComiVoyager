#include "Graph.h"

Graph::Graph(int vertices):V(vertices)
{
	Matrix.resize(vertices, std::vector<int>(vertices, -1));
}

int Graph::sizeT()
{
	return Matrix.size();
}

void Graph::setNewVertices(int new_vertices)
{
	Matrix.clear();
	V = new_vertices;
	Matrix.resize(new_vertices, std::vector<int>(new_vertices, -1));
	checkSum = 0;
}

void Graph::addEdge(int start, int end, int weight)
{
	if (start >= 0 && start < V && end >= 0 && end < V) {
		Matrix[start][end] = weight;
	}
	else {
		std::cerr << "Invalid vertice indices." << std::endl;
	}
}

void Graph::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
    }
    //Read vertices
    int nV;
    file >> nV;

    Matrix.clear();
    setNewVertices(nV);
    //Read matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            file >> Matrix[i][j];
        }
    }
    //Read checksum form file
    std::string emptyline;
    file >> emptyline;
    size_t index = emptyline.find('=');
    std::string sum = emptyline.substr(index + 1);
    checkSum = std::stoi(sum);
    file.close();
}

void Graph::printMatrix()
{
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (j % V == 0) {
                std::cout << std::endl;
            }
            if (Matrix[i][j] == -1) {
                std::cout << "[" << std::setw(3) << Matrix[i][j] << "] ";
            }
            else {
                std::cout << "[" << std::setw(3) << Matrix[i][j] << "] ";
            }
        }
    }
    std::cout << "\n\nSizes:\n";
    std::cout << "Vertices: " << sizeT() << "\nSum: " << checkSum << std::endl;
}

void Graph::printMatrixToFile(std::ostream& os)
{
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            os << Matrix[i][j] << " ";
        }
        os << std::endl;
    }
}

void Graph::randomEdges(int seed)
{
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                Matrix[i][j] = rand() % seed;
            }
            else {
                Matrix[i][j] = -1; //-1 
            }
        }
    }
}

void Graph::swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

bool Graph::nextPermutation(std::vector<int>& arr)
{
    int n = arr.size();
    int i = n - 2;

    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i < 0) {
        return false; // Nie ma wiêcej permutacji
    }

    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    swap(arr[i], arr[j]);

    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }

    return true;
}

std::pair<std::vector<int>, int> Graph::bruteForceTSP(std::chrono::microseconds &globalExecutionTimeBF)
{
    std::vector<int> bestPath;
    int bestCost = INT_MAX;

    std::vector<int> vertices(V);
    for (int i = 0; i < V; i++) {
        vertices[i] = i;
    }
    auto start = std::chrono::high_resolution_clock::now();

    do {
        int currentCost = 0;
        std::vector<int> currentPath;
        currentPath.push_back(vertices[0]);

        for (int i = 1; i < V; i++) {
            int u = vertices[i - 1];
            int v = vertices[i];
            if (Matrix[u][v] == -1) {
                currentCost = INT_MAX;
                break;
            }
            currentCost += Matrix[u][v];
            currentPath.push_back(v);
        }
        if (currentCost != INT_MAX) {
            if (Matrix[vertices[V - 1]][vertices[0]] != -1) {
                currentCost += Matrix[vertices[V - 1]][vertices[0]];
                currentPath.push_back(vertices[0]);
                if (currentCost < bestCost) {
                    bestCost = currentCost;
                    bestPath = currentPath;
                }
            }
        }
    } while (nextPermutation(vertices));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Execution time for brute-force algorithm: " << duration.count() << " microseconds" << std::endl;
    globalExecutionTimeBF = duration;

    return std::make_pair(bestPath, bestCost);
}

std::pair<std::vector<int>, int> Graph::callBranchAndBound(std::chrono::microseconds& globalExecutionTimeBaB)
{
    //Inicjalizacja zmiennych
    std::vector<int> bestPath(V);
    std::vector<bool> visitedCity(V, false);
    std::vector<int> currentPath(V);
    int bestCost = INT_MAX;

    //Inicjalizacja zmiennych dla pierwszego miasta
    currentPath[0] = 0;
    visitedCity[0] = true;
    auto start = std::chrono::high_resolution_clock::now();

    branchAndBound(1, 0, bestPath, visitedCity, currentPath, bestCost);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    globalExecutionTimeBaB = duration;
    std::cout << "Execution time for Branch&Bound: " << duration.count() << " microseconds" << std::endl;
    bestPath.push_back(currentPath[0]);
    return std::make_pair(bestPath, bestCost);
}

void Graph::branchAndBound(int city, int costSoFar, std::vector<int>&bestPath, std::vector<bool>&visitedCity, std::vector<int>&currentPath, int& bestCost) {
    if (city == V) {
        int lastCity = currentPath[city - 1];
        if (Matrix[lastCity][0] != -1) {
            costSoFar += Matrix[lastCity][0];
            if (costSoFar < bestCost) {
                bestCost = costSoFar;
                bestPath = currentPath;
            }
        }
        return;
    }
    for (int i = 0; i < V; ++i) {
        if (!visitedCity[i] && Matrix[currentPath[city - 1]][i] != -1) {
            int newCost = costSoFar + Matrix[currentPath[city - 1]][i];
            if (newCost < bestCost) {
                visitedCity[i] = true;
                currentPath[city] = i;
                branchAndBound(city + 1, newCost, bestPath, visitedCity, currentPath, bestCost);
                visitedCity[i] = false;
            }
        }
    }
  }




