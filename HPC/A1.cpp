#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;
class Graph
{

private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int vertices)
    {
        this->vertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";
            for (int j = 0; j < adjList[i].size(); j++)
            {
                cout << adjList[i][j] << " ";
            }
            cout << endl;
        }
    }

    void BFS(int start)
    {
        vector<bool> visited(vertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int current;

#pragma omp parallel shared(q, visited)
            {
#pragma omp single
                {
                    current = q.front();
                    q.pop();
                    cout << "Thread " << omp_get_thread_num() << " visited " << current << endl;
                }
#pragma omp for
                for (int i = 0; i < adjList[current].size(); i++)
                {
                    if (!visited[adjList[current][i]])
                    {
#pragma omp critical
                        {
                            q.push(adjList[current][i]);
                            visited[adjList[current][i]] = true;
                        }
                    }
                }
            }
        }
    }
    void DFSUtil(int v, vector<bool> &visited)
    {
#pragma omp critical
        {
            visited[v] = true;
            cout << "Thread " << omp_get_thread_num() << " visited" << v << endl;
        }
#pragma omp parallel for
        for (int i = 0; i < adjList[v].size(); i++)
        {
            int u = adjList[v][i];
            if (!visited[adjList[v][i]])
            {
                DFSUtil(u, visited);
            }
        }
    }
    void DFS(int start)
    {
        vector<bool> visited(vertices, false);
        DFSUtil(start, visited);
    }
};

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 1);
    g.addEdge(2, 4);

    g.printGraph();

    cout << endl;
    cout << "BFS TRAVERSAL : ";
    g.BFS(0);
    cout << endl;

    cout << "DFS TRAVERSAL : ";
    g.DFS(0);
    cout << endl;

    return 0;
}