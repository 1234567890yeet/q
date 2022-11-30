#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Node
{
    int key;
    int distance;
    struct Node *next;
} Node;
typedef struct PriorityQueue
{
    Node *array[MAX];
    int size;
} PriorityQueue;
typedef struct Graph
{
    int vertices;
    Node **adjList;
} Graph;
PriorityQueue *queue;
void enqueue(Node *n)
{
    if (queue->size == MAX)
        return;
    queue->array[queue->size++] = n;
}
int isEmpty()
{
    if (queue->size == 0)
        return 1;
    return 0;
}
void minHeapify(int i)
{
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < queue->size && queue->array[left]->distance < queue->array[smallest]->distance)
        smallest = left;
    else if (right < queue->size && queue->array[right]->distance < queue->array[smallest]->distance)
        smallest = right;
    if (smallest != i)
    {
        Node *temp = queue->array[smallest];
        queue->array[smallest] = queue->array[i];
        queue->array[i] = temp;
        minHeapify(smallest);
    }
}
void decreaseKey(Node *temp, int val)
{
    int index = 0;
    for (int i = 0; i < queue->size; i++)
    {
        if (queue->array[i]->key == temp->key)
        {
            index = i;
            break;
        }
    }
    if (queue->array[index]->key < val)
        return;
    while (index > 0 && queue->array[index]->key < queue->array[(index - 1) / 2]->key)
    {
        Node *swap = queue->array[index];
        queue->array[index] = queue->array[(index - 1) / 2];
        queue->array[(index - 1) / 2] = swap;
        index = (index - 1) / 2;
    }
}
int getMinDistance()
{
    if (queue->size == 0)
        return -1;
    Node *temp = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    minHeapify(0);
    queue->size--;
    return temp->key;
}
void buildHeap()
{
    for (int i = queue->size / 2 - 1; i >= 0; i--)
    {
        minHeapify(i);
    }
}
int search(Graph *graph, int val)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        if (graph->adjList[i]->key == val)
            return i;
    }
    return -1;
}
Node *createNode(int trg, int weight)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = trg;
    node->next = NULL;
    node->distance = weight;
    return node;
}
Graph *addEdge(Graph *graph, int src, int trg, int weight)
{
    int index = search(graph, src);
    Node *newNode = createNode(trg, weight);
    newNode->next = graph->adjList[index]->next;
    graph->adjList[index]->next = newNode;
    return graph;
}
void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        Node *temp = graph->adjList[i]->next;
        printf("%d->", graph->adjList[i]->key);
        while (temp != NULL)
        {
            int index = search(graph, temp->key);
            printf("%d (wt: %d), ", temp->key, temp->distance);
            temp = temp->next;
        }
        printf("\n");
    }
}
void Dijkstra(Graph *graph, int source)
{
    int parent[graph->vertices], set[graph->vertices];
    for (int i = 0; i < graph->vertices; i++)
    {
        parent[i] = -1;
        set[i] = 0;
        graph->adjList[i]->distance = INT_MAX;
        enqueue(graph->adjList[i]);
    }
    int index = search(graph, source);
    graph->adjList[index]->distance = 0;
    set[index] = 1;
    buildHeap();
    while (!isEmpty())
    {
        index = search(graph, getMinDistance());
        Node *temp = graph->adjList[index]->next;
        set[index] = 1;
        while (temp != NULL)
        {
            int index1 = search(graph, temp->key);
            if (!set[index1] && graph->adjList[index1]->distance > temp->distance + graph->adjList[index]->distance)
            {
                parent[index1] = graph->adjList[index]->key;
                graph->adjList[index1]->distance =
                    temp->distance + graph->adjList[index]->distance;
                decreaseKey(graph->adjList[index1],
                            temp->distance + graph->adjList[index]->distance);
            }
            temp = temp->next;
        }
    }
    for (int i = 0; i < graph->vertices; i++)
    {
        printf("Distance of %d from source: %d\n", graph->adjList[i]->key,
               graph->adjList[i]->distance);
    }
}
int main()
{
    int v1, v2, w;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    printf("Enter number of vertices: ");
    scanf("%d", &graph->vertices);
    queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->size = 0;
    graph->adjList = (Node **)malloc(graph->vertices * sizeof(Node *));
    printf("Enter vertices: ");
    for (int i = 0; i < graph->vertices; i++)
    {
        graph->adjList[i] = (Node *)malloc(sizeof(Node));
        scanf("%d", &graph->adjList[i]->key);
        graph->adjList[i]->next = NULL;
    }
    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter vertex on the edges and the weight: ");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &v1, &v2, &w);
        graph = addEdge(graph, v1, v2, w);
        graph = addEdge(graph, v2, v1, w);
    }
    printGraph(graph);
    printf("\nEnter the source vertex: ");
    scanf("%d", &w);
    Dijkstra(graph, w);
}