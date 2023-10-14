#include <utility>

#include "iostream"
#include "vector"
#include "map"
#include "fstream"
using namespace std;
struct edge{
    string u;
    string v;
    string weight;
    edge(string u, string v, string w) {
        this->u = std::move(u);
        this->v = std::move(v);
        this->weight = std::move(w);
    }
};
struct graph {
private:
    vector<edge> edges;
    int number_of_vertices;
public:
    graph(int number_of_vertices) {
        this->number_of_vertices = number_of_vertices;
    }
    void addEdge(const string& source, const string& intake, const string& weight) {
        edge e(source, intake, weight);
        edges.push_back(e);
    }
    void printGraph() {
        map<string, vector<pair<string, string>>> vertices_with_connections;
        for (int i = 0; i < edges.size(); i++) {
            string source_vertice = edges[i].u;
            string intake_vertice = edges[i].v;
            string weight = edges[i].weight;
            pair<string, string> temp;
            temp.first = intake_vertice;
            temp.second = weight;
            vertices_with_connections[source_vertice].push_back(temp);
        }
        for (const auto& [source_vertice, connected_vertices_with_weights] : vertices_with_connections) {
            cout << "Source vertice: " << source_vertice  << "; ";
            vector<pair<string, string>> temp = connected_vertices_with_weights;
            for (int i = 0; i < temp.size(); i++) {
                cout << "(input vertice: " << temp[i].first << ", weight: "
                     << temp[i].second << ")";
                if (i != temp.size()-1) {
                    cout << ", ";
                }
            }
            cout << endl << endl;
        }
    }
    map<string, int> bellmanFord(const string& source_vertice) {
        map<string, int> dist;
        for (auto & edge : edges) {
            dist[edge.u] = 2e9;
        }
        dist[source_vertice] = 0;
        for (int i = 0; i < number_of_vertices-1; i++) {
            for (int j = 0; j < edges.size(); j++) {
                string u = edges[j].u;
                string v = edges[j].v;
                int w = stoi(edges[j].weight);
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
        return dist;
    }
};

int main() {
    graph g(9);
    ifstream fin;
    fin.open("/Users/evgenij/Desktop/graph.txt");
    string v;
    cout << "Введите вершину, от которой нужно найти кратчайшие пути: ";
    cin >> v;
    while (true) {
        vector<string> data(3);
        int ind = 0;
        string input;
        getline(fin, input);
        if (input.empty()) {
            break;
        }
        for (char i : input) {
            if (i != ' ') {
                data[ind] += i;
            }
            else {
                ind++;
            }
        }
        g.addEdge(data[0], data[1], data[2]);
    }
    fin.close();
    cout << "Построен граф со следующими соединениями: " << endl;
    g.printGraph();
    map<string, int> dist = g.bellmanFord(v);
    for (const auto& [vertice, distance] : dist) {
        cout << "Вершина: " << vertice << "; минимальное расстояние до неё от " << v << " составляет: " << distance << endl;
    }

}
