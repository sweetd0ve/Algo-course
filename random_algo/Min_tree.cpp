#include <iostream>
#include <algorithm>
#include <vector>

const int INF = 1000000;
class Heap {
public:

    void heapifyDown(int k, int n) {
        int largest = k;
        int l = 2 * k + 1;
        int r = 2 * k + 2;
        if (l < n && heap[l].second < heap[largest].second) 
            largest = l;

        if (r < n && heap[r].second < heap[largest].second) 
            largest = r;

        if (largest != k) { 
            std::swap(heap[k], heap[largest]); 
            heapifyDown(largest, n); 
           } 
    }

    void heapifyUp(int i) {
        if (i != 0 && heap[(i - 1) / 2].second > heap[i].second) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            heapifyUp((i - 1) / 2);
        }
    }

    void insert(std::pair<int, int> v) {
        heap.push_back(v);
        heapifyUp(heap.size() - 1);
    }

    std::pair<int, int> extractMin() {
        std::pair<int, int> result = heap[0];
        heap[0] = heap[heap.size() - 1];

        heap.pop_back();
        heapifyDown(0, heap.size());
        return result;
    }

    bool isEmpty() {
        return heap.size() == 0 ? true : false;
    }

private:
    std::vector<std::pair<int, int>> heap;
};



int main() {
    int num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;
    if (num_edges == 0) return 0;
    std::vector<std::vector<int>> graph(num_vertices);
    for (size_t i = 0; i < num_vertices; ++i)
        graph[i].resize(num_vertices, -1);

    int from, to, weight;
    for (size_t i = 0; i < num_edges; ++i) {
        std::cin >> from >> to >> weight;
        graph[from - 1][to - 1] = weight;
        graph[to - 1][from - 1] = weight;
    }

    Heap heap;
    std::vector<bool> used(num_vertices, false);
    std::vector<int> cost(num_vertices, INF);
    cost[0] = 0;

    heap.insert({ 0, 0 });

    std::vector<int> parent(num_vertices, -1);

    while (!heap.isEmpty()) {

        std::pair<int, int> min = heap.extractMin();
        int vertex = min.first;

        used[vertex] = true;

        for (int adjacent_vertex = 0; adjacent_vertex < num_vertices; adjacent_vertex++) {
            if (graph[vertex][adjacent_vertex] != -1 && !used[adjacent_vertex] &&
                graph[vertex][adjacent_vertex] < cost[adjacent_vertex]) {

                parent[adjacent_vertex] = vertex;
                cost[adjacent_vertex] = graph[vertex][adjacent_vertex];

                heap.insert({ adjacent_vertex, graph[vertex][adjacent_vertex] });
            }
        }
    }

    long weight_MST = 0;
    for (int i = 1; i < num_vertices; ++i)
        weight_MST += graph[parent[i]][i];


    std::cout << weight_MST;
}