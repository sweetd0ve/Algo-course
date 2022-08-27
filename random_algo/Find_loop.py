def matrix_of_graph(num_vertices):
    graph = [[] for _ in range(num_vertices)]
    for i in range(num_vertices):
        graph[i] = list(map(int, input().split()))
    return graph


def dfs_loop(graph, colors, vertex, edge_from, loop):
    colors[vertex] = 1
    for adjacent_vertex in range(len(graph)):
        if graph[vertex][adjacent_vertex] == 1:
            if adjacent_vertex not in colors:
                edge_from[adjacent_vertex] = vertex
                if dfs_loop(graph, colors, adjacent_vertex, edge_from, loop):
                    return True
            elif edge_from[vertex] != adjacent_vertex:
                loop.append(adjacent_vertex)
                loop.append(vertex)
                return True
    colors[vertex] = 2
    return False


def find_loop(graph, num_vertices):
    edge_from = {}
    colors = {}
    for vertex in range(num_vertices):
        if vertex not in colors:
            loop = []
            if dfs_loop(graph, colors, vertex, edge_from, loop):
                next_vertex = edge_from[loop[1]]
                while next_vertex != loop[0]:
                    loop.append(next_vertex)
                    next_vertex = edge_from[next_vertex]
                return loop
    return loop


def print_loop_if_it_exists(graph, num_vertices):
    loop = find_loop(graph, num_vertices)
    if len(loop) > 0:
        print("YES")
        print(len(loop))
        print(*map(lambda x: x + 1, loop))
    else:
        print("NO")


def main():
    num_vertices = int(input())
    graph = matrix_of_graph(num_vertices)
    print_loop_if_it_exists(graph, num_vertices)


if __name__ == '__main__':
    main()
