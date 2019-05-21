#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 100

//перестановка элементов местами
void swap(char *a,char *b)
{
    char tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}

//список смежности
typedef struct node {
    int vertex, weight;
    struct node * next;
}node;

typedef struct vertex
{
    int vertex, dist;
}vertex;

//вставка значений в граф
node * addEdge(node * head, int vertex, int weight)
{
    node * new_node = (struct node *) malloc(sizeof(struct node));

    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = head;

    return new_node;
}

//построение бинарного дерева
void heapify(vertex *minHeap, int size, int i, int *position)
{
    vertex tmp;

    while ((2 * i) <= size) {
        if ((2 * i) + 1 > size) {
            if (minHeap[i].dist > minHeap[2 * i].dist) {
                position[minHeap[i].vertex] = 2 * i;
                position[minHeap[2 * i].vertex] = i;

                tmp = minHeap[i];
                minHeap[i] = minHeap[2 * i];
                minHeap[2 * i] = tmp;
            }

            break;
        }

        if (minHeap[i].dist > minHeap[2 * i].dist || minHeap[i].dist > minHeap[2 * i + 1].dist) {
            if (minHeap[2 * i].dist <= minHeap[(2 * i) + 1].dist) {
                position[minHeap[i].vertex] = 2 * i;
                position[minHeap[2 * i].vertex] = i;

                tmp = minHeap[2 * i];
                minHeap[2 * i] = minHeap[i];
                minHeap[i] = tmp;

                i = 2 * i;
            } else if (minHeap[2 * i].dist > minHeap[(2 * i) + 1].dist) {
                position[minHeap[i].vertex] = 2 * i + 1;
                position[minHeap[2 * i + 1].vertex] = i;

                tmp = minHeap[(2 * i) + 1];
                minHeap[(2 * i) + 1] = minHeap[i];
                minHeap[i] = tmp;

                i = (2 * i) + 1;
            }
        } else {
            break;
        }
    }
}

//создание бинарной кучи
void buildHeap(vertex *minHeap, int size, int *position)
{
    int i;

    for (i = size / 2; i >= 1; --i) {
        heapify(minHeap, size, i, position);
    }
}

void decreaseKey(vertex *minHeap, struct vertex newNode, int *position)
{
    minHeap[position[newNode.vertex]].dist = newNode.dist;

    int i = position[newNode.vertex];
    vertex tmp;

    while (i > 1) {
        if (minHeap[i / 2].dist > minHeap[i].dist) {
            position[minHeap[i].vertex] = i / 2;
            position[minHeap[i / 2].vertex] = i;

            tmp = minHeap[i / 2];
            minHeap[i / 2] = minHeap[i];
            minHeap[i] = tmp;

            i = i / 2;
        } else {
            break;
        }
    }
}

//извлечение минимального элемента
vertex extractMin(vertex *minHeap, int size, int *position)
{
    position[minHeap[1].vertex] = size;
    position[minHeap[size].vertex] = 1;

    vertex min = minHeap[1];

    minHeap[1] = minHeap[size];
    --size;
    heapify(minHeap, size, 1, position);

    return min;
}

//алгоритм Дейкстры
void Dijkstra(node **adjacencyList, int vertices, int start, int *distances, int *parent)
{
    int i;
    vertex minVertex;
    vertex priorityQueue[vertices + 1];
    int position[vertices + 1];

    for (i = 1; i <= vertices; ++i) {
        distances[i] = INT_MAX;
        parent[i] = 0;
        priorityQueue[i].dist = INT_MAX;
        priorityQueue[i].vertex = i;
        position[i] = priorityQueue[i].vertex;
    }

    distances[start] = 0;
    priorityQueue[start].dist = 0;
    buildHeap(priorityQueue, vertices, position);

    for (i = 1; i <= vertices; ++i) {
        minVertex = extractMin(priorityQueue, vertices, position);
        node * path = adjacencyList[minVertex.vertex];

        while (path != NULL) {
            int u = minVertex.vertex;
            int v = path->vertex;
            int w = path->weight;

            if (distances[u] != INT_MAX && distances[v] > distances[u] + w) {
                distances[v] = distances[u] + w;
                parent[v] = u;

                vertex changedVertex;

                changedVertex.vertex = v;
                changedVertex.dist = distances[v];
                decreaseKey(priorityQueue, changedVertex, position);
            }

            path = path->next;
        }
    }
}

//релаксация пути
void printPath(int *parent, int vertex, int start)
{
    if (vertex == start) {
        printf("%d ", start);
        return;
    }
    if (parent[vertex] == 0) {
        printf("%d ", vertex);
        return;
    }
    printPath(parent, parent[vertex], start);
    printf("%d ", vertex);
}

//задача коммивояжёра
int *TSP(int vertex, int n, int adj[SIZE][SIZE], const int completed[SIZE], int cost, int *problem)
{
    int nearestVertex = INT_MAX;
    int min = INT_MAX, minWeight = 0;

    for (int i = 0; i < n; i++)
    {
        if ((adj[vertex][i] != 0) && (completed[i] == 0))
            if (adj[vertex][i] + adj[i][vertex] < min)
            {
                min = adj[i][vertex] + adj[vertex][i];
                minWeight = adj[vertex][i];
                nearestVertex = i;
            }
    }

    if (min != INT_MAX)
    {
        cost += minWeight;
        problem[0] += cost;
    }

    problem[1] = nearestVertex;
    return problem;
}


void findMinWeight(int vertex, int n, int completed[SIZE], int cost, int adj[SIZE][SIZE], int *problem)
{
    int nearestVertex;

    completed[vertex] = 1;

    printf("%d->", vertex + 1);
    problem = TSP(vertex, n, adj, completed, cost, problem);
    nearestVertex = problem[1];
    if (nearestVertex == INT_MAX)
    {
        nearestVertex = 0;
        printf("%d", nearestVertex + 1);
        cost += adj[vertex][nearestVertex];
        problem[0] += cost;
        return;
    }

    findMinWeight(nearestVertex, n, completed, cost, adj, problem);
}

int main()
{

    printf("<----Поиск наикратчайшего пути от конкретной вершины до всех остальных---->\n\n");

    int vertices, edges, v1, v2, w;

    printf("Введите количество вершин:");
    scanf("%d", &vertices);
    printf("Введите количество дуг:");
    scanf("%d", &edges);

    node * adjacencyList[vertices + 1];
    int distances[vertices + 1];
    int parent[vertices + 1];

    //инициализируем список смежности
    for (int i = 0; i <= vertices; ++i) {
        adjacencyList[i] = NULL;
    }

    printf("Введите элементы списка смежности в формате 'Начальная вершина' 'Конечная вершина' 'Вес дуги':\n");
    for (int i = 1; i <= edges; ++i) {
        scanf("%d %d %d", &v1, &v2, &w);
        adjacencyList[v1] = addEdge(adjacencyList[v1], v2, w);
    }

    int start;
    printf("Введите начальную вершину:");
    scanf("%d",&start);
    Dijkstra(adjacencyList, vertices, start, distances, parent);
    printf("Список кратчайших путей из вершины %d:\n\n",start);

    for (int i = 1; i <= vertices; ++i) {
        if (distances[i]!=INT_MAX)
        {
           printf("Длина маршрута %d->%d = %d\n",start,i,distances[i]);
           printf("Кратчайший путь проходит через вершины:");
           printPath(parent, i, start);
        }
        else {
           printf("Длина маршрута %d->%d = маршрут недоступен\n",start,i);
        }

        printf("\n\n");

    }

    printf("<----Задача коммивояжера методом грубой силы---->\n\n");

    int problem[2];

    int adjacencyMatrix[SIZE][SIZE], completed[SIZE], n, cost = 0;
    int i, j;

    printf("Введите количество вершин:");
    scanf("%d",&n);

    printf("Введите матрицу смежности:\n");
    for(int i=0;i < n;i++)
    {
        for(int j=0;j < n;j++)
           scanf("%d",&adjacencyMatrix[i][j]);
        completed[i]=0;
    }

    printf("\nКратчайший путь проходит через вершины:\n");
    findMinWeight(0, n, completed, cost, adjacencyMatrix, problem);
    printf("\nДлина маршрута = %d",problem[0]);
    printf("\n");

    return 0;
}
