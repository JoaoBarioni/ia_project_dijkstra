#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <stack>

using namespace std;

// Definindo a estrutura de dados para representar o grafo
typedef map<string, vector<pair<string, int>>> Graph;

// Função para encontrar o caminho mais curto usando o algoritmo Dijkstra
map<string, pair<int, string>> dijkstra(const Graph &graph, const string &start_node)
{
    map<string, pair<int, string>> shortest_distance; // Pair para armazenar distância e nó predecessor
    set<string> visited_nodes;

    // Inicializa as distâncias com infinito e o nó de origem com distância zero e nenhum predecessor
    for (const auto &entry : graph)
    {
        shortest_distance[entry.first] = {numeric_limits<int>::max(), ""};
    }
    shortest_distance[start_node] = {0, ""};

    // Loop principal do algoritmo Dijkstra
    while (visited_nodes.size() != graph.size())
    {
        //declaração de variáveis
        string current_node;
        int min_distance = numeric_limits<int>::max();

        // Encontra o nó não visitado com a menor distância atual
        for (const auto &entry : graph)
        {
            if (visited_nodes.find(entry.first) == visited_nodes.end() &&
                shortest_distance[entry.first].first < min_distance)
            {
                current_node = entry.first;
                min_distance = shortest_distance[entry.first].first;
            }
        }

        // Marca o nó atual como visitado
        visited_nodes.insert(current_node);

        // Atualiza as distâncias para os vizinhos do nó atual
        for (const auto &neighbor : graph.at(current_node))
        {
            int distance = min_distance + neighbor.second;
            if (distance < shortest_distance[neighbor.first].first)
            {
                shortest_distance[neighbor.first] = {distance, current_node};
            }
        }
    }

    return shortest_distance;
}

// Função para exibir o caminho a partir do nó de destino
void printPath(const map<string, pair<int, string>> &shortest_distances, const string &destination)
{
    stack<string> path;
    string current_node = destination;
    int total_distance = shortest_distances.at(destination).first; // Obtenha a distância total

    // Rastreia o caminho a partir do destino até a origem
    while (!current_node.empty())
    {
        path.push(current_node);
        current_node = shortest_distances.at(current_node).second;
    }

    // Exibe o caminho e a distância total
    cout << "Caminho para " << destination << ": ";
    while (!path.empty())
    {
        cout << path.top();
        path.pop();
        if (!path.empty())
        {
            cout << " -> ";
        }
    }
    cout << " (Distancia: " << total_distance << ")" << endl;
}

int main()
{
    Graph graph = {
        {"C", {{"PP1", 83}, {"PP2", 86}, {"PP3", 233}, {"PP4", 203}, {"PP5", 146}}},

        {"PP1", {{"PS1", 218}, {"PS2", 228}, {"PS3", 219}, {"PS4", 432}, {"PS5", 339}, {"PS6", 139}, {"PS7", 288}}},
        {"PP2", {{"PS1", 321}, {"PS2", 289}, {"PS3", 299}, {"PS4", 422}, {"PS5", 224}, {"PS6", 84}, {"PS7", 217}}},
        {"PP3", {{"PS1", 326}, {"PS2", 588}, {"PS3", 570}, {"PS4", 76}, {"PS5", 401}, {"PS6", 241}, {"PS7", 565}}},
        {"PP4", {{"PS1", 425}, {"PS2", 548}, {"PS3", 551}, {"PS4", 255}, {"PS5", 195}, {"PS6", 159}, {"PS7", 419}}},
        {"PP5", {{"PS1", 91}, {"PS2", 397}, {"PS3", 365}, {"PS4", 313}, {"PS5", 450}, {"PS6", 217}, {"PS7", 491}}},

        {"PS1", {{"PT1", 457}, {"PT2", 210}, {"PT3", 543}, {"PT4", 105}, {"PT5", 422}}},
        {"PS2", {{"PT1", 665}, {"PT2", 469}, {"PT3", 571}, {"PT4", 242}, {"PT5", 237}}},
        {"PS3", {{"PT1", 661}, {"PT2", 443}, {"PT3", 591}, {"PT4", 205}, {"PT5", 281}}},
        {"PS4", {{"PT1", 84}, {"PT2", 204}, {"PT3", 368}, {"PT4", 461}, {"PT5", 553}}},
        {"PS5", {{"PT1", 350}, {"PT2", 380}, {"PT3", 83}, {"PT4", 472}, {"PT5", 260}}},
        {"PS6", {{"PT1", 280}, {"PT2", 197}, {"PT3", 235}, {"PT4", 250}, {"PT5", 218}}},
        {"PS7", {{"PT1", 579}, {"PT2", 484}, {"PT3", 361}, {"PT4", 471}, {"PT5", 88}}},

        {"PT1", {{"PF1", 626}, {"PF2", 284}, {"PF3", 107}, {"PF4", 645}}},
        {"PT2", {{"PF1", 384}, {"PF2", 102}, {"PF3", 318}, {"PF4", 494}}},
        {"PT3", {{"PF1", 642}, {"PF2", 473}, {"PF3", 173}, {"PF4", 492}}},
        {"PT4", {{"PF1", 131}, {"PF2", 276}, {"PF3", 539}, {"PF4", 331}}},
        {"PT5", {{"PF1", 393}, {"PF2", 498}, {"PF3", 485}, {"PF4", 142}}},

        {"PF1", {{"PT1", 626}, {"PT2", 384}, {"PT3", 642}, {"PT4", 131}, {"PT5", 393}}},
        {"PF2", {{"PT1", 284}, {"PT2", 102}, {"PT3", 473}, {"PT4", 276}, {"PT5", 498}}},
        {"PF3", {{"PT1", 107}, {"PT2", 318}, {"PT3", 173}, {"PT4", 539}, {"PT5", 485}}},
        {"PF4", {{"PT1", 645}, {"PT2", 494}, {"PT3", 492}, {"PT4", 331}, {"PT5", 142}}}};

    string origin_node = "C";

    map<string, pair<int, string>> shortest_distances = dijkstra(graph, origin_node);

    // Exiba os caminhos para PF1, PF2, PF3 e PF4
    for (const string &destination : {"PF1", "PF2", "PF3", "PF4"})
    {
        printPath(shortest_distances, destination);
    }

    return 0;
}
