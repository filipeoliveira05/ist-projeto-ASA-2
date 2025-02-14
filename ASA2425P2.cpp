#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>

using namespace std;


// Estrutura para armazenar o grafo por estações e linhas
struct MetroGraph
{
    unordered_map<int, unordered_set<int>> stationToLines; // Estação -> Linhas que passam nela
    unordered_map<int, unordered_set<int>> lineToStations; // Linha -> Estações que ela conecta
};


// Função para construir o grafo a partir do input
MetroGraph buildGraph(const vector<tuple<int, int, int>> &connections)
{
    MetroGraph graph;

    for (const auto &conn : connections)
    {
        int station1 = get<0>(conn);
        int station2 = get<1>(conn);
        int line = get<2>(conn);

        // Atualizar o grafo de estações para linhas
        graph.stationToLines[station1].insert(line);
        graph.stationToLines[station2].insert(line);

        // Atualizar o grafo de linhas para estações
        graph.lineToStations[line].insert(station1);
        graph.lineToStations[line].insert(station2);
    }

    return graph;
}


// Verificar conectividade global usando BFS
unordered_set<int> bfs(const MetroGraph &graph, int startStation)
{
    unordered_set<int> visitedStations;
    queue<int> q;
    q.push(startStation);
    visitedStations.insert(startStation);

    while (!q.empty())
    {
        int currentStation = q.front();
        q.pop();

        // Percorrer todas as linhas conectadas à estação atual
        for (auto line : graph.stationToLines.at(currentStation))
        {
            // Percorrer todas as estações conectadas por essa linha
            for (auto neighborStation : graph.lineToStations.at(line))
            {
                if (!visitedStations.count(neighborStation))
                {
                    visitedStations.insert(neighborStation);
                    q.push(neighborStation);
                }
            }
        }
    }

    return visitedStations;
}


// Construir o grafo de cores (linhas conectadas por estações de troca)
unordered_map<int, unordered_set<int>> buildLineGraph(const MetroGraph &graph)
{
    unordered_map<int, unordered_set<int>> lineGraph;

    // Para cada estação, conecte todas as linhas que passam por ela
    for (const auto &stationEntry : graph.stationToLines)
    {
        const auto &lines = stationEntry.second;
        for (auto line1 : lines)
        {
            for (auto line2 : lines)
            {
                if (line1 != line2)
                {
                    lineGraph[line1].insert(line2);
                }
            }
        }
    }

    return lineGraph;
}


// Function to perform BFS and calculate the maximum distance from a given start vertex
int bfsMaxDistance(int start, const unordered_map<int, unordered_set<int>> &graph)
{
    unordered_map<int, int> distance; // Map to store distances
    queue<int> q;

    if (graph.find(start) == graph.end())
    {
        cout << "Error: Start vertex " << start << " does not exist in the graph." << endl;
        return 0; // Return 0 for invalid start vertex
    }

    distance[start] = 0;
    q.push(start);

    int maxDistance = 0;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        // Ensure the vertex exists in the graph
        if (graph.find(current) != graph.end())
        {
            for (int neighbor : graph.at(current))
            {
                if (distance.find(neighbor) == distance.end())
                {
                    distance[neighbor] = distance[current] + 1;
                    maxDistance = max(maxDistance, distance[neighbor]);
                    q.push(neighbor);
                }
            }
        }
    }

    return maxDistance;
}


// Function to calculate the maximum path length between any two vertices
int findMaxPath(const unordered_map<int, unordered_set<int>> &graph)
{
    int maxPathLength = 0;

    for (const auto &entry : graph)
    {
        int startVertex = entry.first;
        maxPathLength = max(maxPathLength, bfsMaxDistance(startVertex, graph));
    }

    return maxPathLength;
}


// Função para verificar os casos específicos
int checkSpecificCases(const MetroGraph &graph, int n)
{
    // Caso 0: Uma linha cobre todas as estações
    for (const auto &entry : graph.lineToStations)
    {
        if (entry.second.size() == static_cast<size_t>(n))
        {
            return 0; // Existe uma linha que conecta todas as estações
        }
    }

    // Caso -1: Estação desconectada
    unordered_set<int> visitedStations;
    for (const auto &entry : graph.lineToStations)
    {
        visitedStations.insert(entry.second.begin(), entry.second.end());
    }
    
    if (visitedStations.size() < static_cast<size_t>(n))
    {
        return -1; // Existe ao menos uma estação sem conexão
    } 
    
    // Verificar conectividade global (caso -1: duas ou mais árvores distintas)
    if (bfs(graph, 1).size() != static_cast<size_t>(n))
    {
        return -1;
    }

    return -2; // Caso geral (não resolvido aqui ainda)
}


int main()
{
    int n, m, l;
    cin >> n >> m >> l;

    if (n < 2 || m < 0 || l < 0)
    {
        cerr << "Entrada inválida!" << endl;
        return -1;
    }

    vector<tuple<int, int, int>> connections;
    for (int i = 0; i < m; ++i)
    {
        int x, y, line;
        cin >> x >> y >> line;
        connections.emplace_back(x, y, line);
    }

    if (n > m + 1)
    {
        cout << -1 << endl;
        return 0;
    }

    // Construir o grafo
    MetroGraph graph = buildGraph(connections);
    int specificCaseResult = checkSpecificCases(graph, n);

    // Imprimir resultado dos casos específicos ou continuar para análise geral
    if (specificCaseResult == -1 || specificCaseResult == 0)
    {
        cout << specificCaseResult << endl;
        return 0;
    }

    // Caso geral: Calcular o número mínimo de transferências
    unordered_map<int, unordered_set<int>> lineGraph = buildLineGraph(graph);
    int result = findMaxPath(lineGraph);

    cout << result << endl;
    return 0;
}
