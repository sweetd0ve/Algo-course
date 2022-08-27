#include <iostream>
#include <vector>

std::vector<int> Dijkstra(std::vector<int>& min_distance, int vertex,
                 const std::vector<std::vector<std::pair<int, std::pair<int, int>>>>& graph,
                 std::vector<bool>& used) {
    used[vertex] = true;
    for (auto adjacent_vertex : graph[vertex]) { 
        if (!(used[adjacent_vertex.first]) &&
              adjacent_vertex.second.first >= min_distance[vertex]) {
            if (min_distance[adjacent_vertex.first] > adjacent_vertex.second.second) {
                min_distance[adjacent_vertex.first] = adjacent_vertex.second.second;
            }
        } 
    }
    int min_adjacent = min_distance.size();
    int min_dist = 100000;
    for (size_t i = 0; i < min_distance.size(); ++i) {
        if (!(used[i]) && min_distance[i] != 100000 && min_dist >= min_distance[i]) {
            min_adjacent = i;
            min_dist = min_distance[i];
        }
    }
    vertex = min_adjacent;
    if (vertex < min_distance.size()) min_distance = Dijkstra(min_distance, vertex, graph, used);
    return min_distance;
}

int main() {
    int num_countries;
    std::cin >> num_countries;
    std::vector<std::vector<std::pair<int, std::pair<int, int>>>> graph(num_countries);
    int start, finish;
    std::cin >> start >> finish;

    std::vector<int> min_distance(num_countries, 100000); 
    min_distance[start - 1] = 0;

    int num_runs;
    std::cin >> num_runs;
    int from, departure_time, to, arrival_time;
    for (int i = 0; i < num_runs; ++i) {
        std::cin >> from >> departure_time >> to >> arrival_time;
        graph[from - 1].push_back({to - 1, {departure_time, arrival_time}});
    }

    std::vector<bool> used(num_countries, false);
    int distance = Dijkstra(min_distance, start - 1, graph, used)[finish - 1];

    if (distance == 100000) {
        std::cout << -1;
    } else {
        std::cout << distance;
    }
}
