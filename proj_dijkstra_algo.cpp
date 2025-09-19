#include <iostream>
using namespace std;

const int UNREACHABLE = 999999;   // A very big number to show "no connection"
const int MAX_VERTICES = 100;     // Maximum vertices allowed in the graph

int main() {
    int vertexCount, edgeCount;

    // Ask user how many vertices and edges are in the graph
    cout << "Enter total number of vertices: ";
    cin >> vertexCount;

    cout << "Enter total number of edges: ";
    cin >> edgeCount;

    // Make adjacency matrix to store graph edges
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (i == j) adjacencyMatrix[i][j] = 0;       // Same vertex has distance 0
            else adjacencyMatrix[i][j] = UNREACHABLE;    // No edge yet, set as infinity
        }
    }

    // Take edge input (start, end, weight)
    cout << "Enter each edge in format (start end cost):\n";
    for (int i = 0; i < edgeCount; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        adjacencyMatrix[from][to] = cost;
        adjacencyMatrix[to][from] = cost; // For undirected graph
    }

    // Ask for source and destination
    int sourceVertex, destinationVertex;
    cout << "Enter source vertex: ";
    cin >> sourceVertex;
    cout << "Enter destination vertex: ";
    cin >> destinationVertex;

    // Arrays to help Dijkstra
    int tentativeDistance[MAX_VERTICES]; // Current best distance
    int shortestPathTree[MAX_VERTICES];  // Marks if vertex is done
    int predecessor[MAX_VERTICES];       // Stores the path

    // Initialize arrays
    for (int i = 0; i < vertexCount; i++) {
        tentativeDistance[i] = UNREACHABLE; // Start with infinity
        shortestPathTree[i] = 0;            // No vertex finished yet
        predecessor[i] = -1;                // Path unknown
    }
    tentativeDistance[sourceVertex] = 0;    // Source distance is always 0

    // Main loop of Dijkstra
    for (int step = 0; step < vertexCount - 1; step++) {
        // Find vertex with smallest distance not finished yet
        int chosenVertex = -1;
        int smallestDistance = UNREACHABLE;

        for (int v = 0; v < vertexCount; v++) {
            if (!shortestPathTree[v] && tentativeDistance[v] < smallestDistance) {
                smallestDistance = tentativeDistance[v];
                chosenVertex = v;
            }
        }

        // If no vertex found, stop
        if (chosenVertex == -1) break;

        // Mark chosen vertex as finished
        shortestPathTree[chosenVertex] = 1;

        // Update distances for neighbors of chosen vertex
        for (int neighbor = 0; neighbor < vertexCount; neighbor++) {
            if (!shortestPathTree[neighbor] && adjacencyMatrix[chosenVertex][neighbor] != UNREACHABLE) {
                int newDistance = tentativeDistance[chosenVertex] + adjacencyMatrix[chosenVertex][neighbor];
                if (newDistance < tentativeDistance[neighbor]) {
                    tentativeDistance[neighbor] = newDistance;
                    predecessor[neighbor] = chosenVertex; // Remember the path
                }
            }
        }
    }

    // Show result
    if (tentativeDistance[destinationVertex] == UNREACHABLE) {
        cout << "No path exists from " << sourceVertex << " to " << destinationVertex << endl;
    } else {
        cout << "Minimum cost from " << sourceVertex << " to " << destinationVertex
             << " = " << tentativeDistance[destinationVertex] << endl;

        // Print path
        int path[MAX_VERTICES], pathLength = 0;
        for (int v = destinationVertex; v != -1; v = predecessor[v]) {
            path[pathLength++] = v;
        }

        cout << "Path taken: ";
        for (int i = pathLength - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}
