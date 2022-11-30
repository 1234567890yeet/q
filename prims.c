#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Node
{
    int key;
    int weight;
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
    if (left < queue->size && queue->array[left]->weight < queue->array[smallest]->weight)
        smallest = left;
    else if (right < queue->size && queue->array[right]->weight < queue->array[smallest]->weight)
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
int getMin()
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
    node->weight = weight;
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
            printf("%d (wt: %d), ", temp->key, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}
void Prims(Graph *graph, int source)
{
    int parent[graph->vertices], mst[graph->vertices];
    for (int i = 0; i < graph->vertices; i++)
    {
        parent[i] = -1;
        mst[i] = 0;
        graph->adjList[i]->weight = INT_MAX;
        enqueue(graph->adjList[i]);
    }
    int index = search(graph, source);
    graph->adjList[index]->weight = 0;
    mst[index] = 1;
    buildHeap();
    while (!isEmpty())
    {
        index = search(graph, getMin());
        Node *temp = graph->adjList[index]->next;
        mst[index] = 1;
        while (temp != NULL)
        {
            int index1 = search(graph, temp->key);
            if (!mst[index1] && graph->adjList[index1]->weight > temp->weight)
            {
                parent[index1] = graph->adjList[index]->key;
                graph->adjList[index1]->weight = temp->weight;
                decreaseKey(graph->adjList[index1], temp->weight);
            }
            temp = temp->next;
        }
    }
    int sum = 0;
    for (int i = 0; i < graph->vertices; i++)
    {
        sum += graph->adjList[i]->weight;
    }
    printf("Total cost of tree: %d", sum);
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
    printf("\nEnter the vertex to start with: ");
    scanf("%d", &w);
    Prims(graph, w);
}