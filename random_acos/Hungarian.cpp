#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <climits>

double Hungarian(const std::vector<std::vector<double>>& a) {
  int n = a.size() - 1;
  std::vector<double> potintial_x(n + 1), potential_y(n + 1);
  std::vector<int> p(n + 1), way(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::vector<double> min_y(n + 1, INT_MAX);
    std::vector<bool> visited(n + 1, false);
    p[0] = i;
    int marked_j = 0;
    do {
      visited[marked_j] = true;
      int marked_i = p[marked_j];
      double delta = INT_MAX;
      int j1 = -1;
      for (int j = 1; j <= n; ++j) {
        if (visited[j]) continue;
        if (a[marked_i][j] - potintial_x[marked_i] - potential_y[j] < min_y[j]) {
          min_y[j] = a[marked_i][j] - potintial_x[marked_i] - potential_y[j];
          way[j] = marked_j;
        }
        if (min_y[j] < delta) {
          delta = min_y[j];
          j1 = j;
        }
      }
      for (int j = 0; j <= n; ++j) {
        if (visited[j]) {
          potintial_x[p[j]] += delta;
          potential_y[j] -= delta;
        } else {
          min_y[j] -= delta;
        }
      }
      marked_j = j1;
    } while (p[marked_j] != 0);
    for (; marked_j != 0; marked_j = way[marked_j]) {
      p[marked_j] = p[way[marked_j]];
    }
  }
  return -potential_y[0];
}

int main() {

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::ifstream fin("input.txt");
  std::ofstream fout("output.txt");

  std::vector<int> firm_a;
  std::vector<int> firm_b;

  firm_a.push_back(0);
  firm_b.push_back(0);

  while (fin.peek() != '\n') {
    int x;
    fin >> x;
    firm_a.push_back(x);
    while (fin.peek() == ' ') {
      fin.ignore();
    }
  }

  while (!fin.eof()) {
    int x;
    fin >> x;
    firm_b.push_back(x);
    while (fin.peek() == ' ' || fin.peek() == '\n') {
      fin.ignore();
    }
  }

  int n = firm_a.size();
  int k = firm_b.size();

  if (n < k) {
    firm_a.swap(firm_b);
    std::swap(n, k);
  }

  sort(firm_a.begin(), firm_a.end());
  sort(firm_b.begin(), firm_b.end());


  std::vector<std::vector<double>> graph(n, std::vector<double>(n, 0));

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < k; ++j) {
      graph[i][j] = std::fabs(firm_a[i] - firm_b[j]);
    }
    for (int j = k; j < n; ++j) {
      graph[i][j] = (double) firm_a[i] / 2;
    }
  }

  fout << std::fixed << std::setprecision(1) << Hungarian(graph) << '\n';
}
