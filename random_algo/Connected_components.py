import sys

sys.setrecursionlimit(100000)


class Graph:
    def __init__(self, num_vertexes):
        self.graph = [[] for _ in range(num_vertexes)]

    def add_edge(self, vertex_first, vertex_second):
        if vertex_first != vertex_second:
            self.graph[vertex_first].append(vertex_second)
            self.graph[vertex_second].append(vertex_first)

    def component_with_vertex(self, vertex, component, visited):
        visited.add(vertex + 1)
        component.add(vertex + 1)
        for adjacent_vertex in self.graph[vertex]:
            if adjacent_vertex + 1 not in component:
                self.component_with_vertex(adjacent_vertex, component, visited)

    def find_components(self, components):
        visited = set()
        for vertex in range(len(self.graph)):
            if vertex + 1 not in visited:
                component = set()
                self.component_with_vertex(vertex, component, visited)
                components.append(component)
        return components

    def print_components(self):
        components = list()
        self.find_components(components)
        print(len(components))
        for component in components:
            print(len(component))
            print(*component)


def main():
    num_vertexes, num_edges = map(int, input().split())
    graph = Graph(num_vertexes)
    for _ in range(num_edges):
        edge = tuple(map(int, input().split()))
        graph.add_edge(edge[0] - 1, edge[1] - 1)
    graph.print_components()


if __name__ == '__main__':
    main()
