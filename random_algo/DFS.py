import sys

sys.setrecursionlimit(10000)


class Graph:
    def __init__(self, num_vertexes):
        self.graph = [[] for _ in range(num_vertexes)]

    def add_edge(self, vertex_first, vertex_second):
        if vertex_first != vertex_second:
            self.graph[vertex_first].append(vertex_second)
            self.graph[vertex_second].append(vertex_first)

    def dfs(self, vertex, visited):
        visited[vertex] = 1
        for adjacent_vertex in self.graph[vertex]:
            if visited[adjacent_vertex] == 0:
                self.dfs(adjacent_vertex, visited)

    def call_dfs_for_vertex(self, vertex):
        visited = [0] * (len(self.graph))
        self.dfs(vertex, visited)
        return visited


def component_with_first_vertex(graph):
    component = graph.call_dfs_for_vertex(0)
    count = 0
    for index in range(len(component)):
        if component[index] == 1:
            count += 1
    print(count)
    for index in range(len(component)):
        if component[index] == 1:
            print(index + 1, end=' ')


def main():
    num_vertexes, num_edges = map(int, input().split())
    graph = Graph(num_vertexes)
    for _ in range(num_edges):
        edge = tuple(map(int, input().split()))
        graph.add_edge(edge[0] - 1, edge[1] - 1)
    component_with_first_vertex(graph)


if __name__ == '__main__':
    main()
