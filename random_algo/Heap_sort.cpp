#include <iostream>
#include <algorithm>
#include <vector>

void heapifyDown(std::vector<int>& v, int k, int n) {
    int largest = k;
    int l = 2 * k + 1;
    int r = 2 * k + 2;

    if (l < n && v[l] > v[largest]) 
        largest = l;

    if (r < n && v[r] > v[largest]) 
        largest = r;

    if (largest != k) { 
        std::swap(v[k], v[largest]); 
        heapifyDown(v, largest, n); 
    } 
}

void heapSort(std::vector<int>& v, int size) {
    for(int i = size / 2 - 1; i >= 0; --i) heapifyDown(v, i, size);
    for(int i = size - 1; i > 0; --i) {
        std::swap(v[0], v[i]);
        heapifyDown(v, 0, i);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i)
        std::cin >> v[i];

    heapSort(v, n);

    for (int i = 0; i < n; ++i)
        std::cout << v[i] << " ";

}