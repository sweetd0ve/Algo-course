def matrix_of_graph(num_vertices):
    graph = [[] for _ in range(num_vertices)]
    for i in range(num_vertices):
        graph[i] = list(map(int, input().split()))
    return graph


def Dijkstra(num_vertices, vertex_from, matrix):
    used = [False] * num_vertices
    weight = [1000000] * num_vertices
    weight[vertex_from] = 0
    for i in range(num_vertices):
        min_weight = 1000001
        index = -1
        for j in range(num_vertices):
            if (not used[j]) and weight[j] < min_weight:
                min_weight = weight[j]
                index = j
        if index != -1:
            used[index] = True
            for j in range(num_vertices):
                if (not used[j]) and matrix[index][j] > 0:
                    if weight[index] + matrix[index][j] < weight[j]:
                        weight[j] = weight[index] + matrix[index][j]
    return weight


def min_distance(num_vertices, vertex_from, vertex_to, matrix):
    weight = Dijkstra(num_vertices, vertex_from, matrix)
    if weight[vertex_to] == 1000000:
        return -1
    return weight[vertex_to]


def main():
    num_vertices, vertex_from, vertex_to = map(int, input().split())
    graph = matrix_of_graph(num_vertices)
    print(min_distance(num_vertices, vertex_from - 1, vertex_to - 1, graph))


if __name__ == '__main__':
    main()
