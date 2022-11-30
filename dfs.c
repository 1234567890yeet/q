#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int key;
    struct Node *next;
} Node;
typedef struct Graph
{
    int vertices;
    Node **adjList;
    int *visited;
} Graph;
int search(Graph *graph, int val)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        if (graph->adjList[i]->key == val)
            return i;
    }
    return -1;
}
Node *createNode(int src)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = src;
    node->next = NULL;
    return node;
}
Graph *addEdge(Graph *graph, int src, int trg)
{
    int index = search(graph, src);
    Node *newNode = createNode(trg);
    newNode->next = graph->adjList[index]->next;
    graph->adjList[index]->next = newNode;
    index = search(graph, trg);
    newNode = createNode(src);
    newNode->next = graph->adjList[index]->next;
    graph->adjList[index]->next = newNode;
    return graph;
}
void DFSVisit(Graph *graph, int u)
{
    int index = search(graph, u);
    graph->visited[index] = 1;
    printf("%d ", u);
    Node *temp = graph->adjList[index]->next;
    while (temp != NULL)
    {
        if (graph->visited[search(graph, temp->key)] == 0)
        {
            DFSVisit(graph, temp->key);
        }
        temp = temp->next;
    }
}
void DFS(Graph *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        if (graph->visited[i] == 0)
            DFSVisit(graph, graph->adjList[i]->key);
    }
}
void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        Node *temp = graph->adjList[i]->next;
        printf("%d->", graph->adjList[i]->key);
        while (temp != NULL)
        {
            printf("%d ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}
int main()
{
    int v1, v2;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    printf("Enter number of vertices: ");
    scanf("%d", &graph->vertices);
    graph->adjList = (Node **)malloc(graph->vertices * sizeof(Node *));
    graph->visited = (int *)malloc(graph->vertices * sizeof(int));
    printf("Enter vertices: ");
    for (int i = 0; i < graph->vertices; i++)
    {
        graph->adjList[i] = (Node *)malloc(sizeof(Node));
        scanf("%d", &graph->adjList[i]->key);
        graph->adjList[i]->next = NULL;
        graph->visited[i] = 0;
    }
    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter vertex on the edges: ");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &v1, &v2);
        graph = addEdge(graph, v1, v2);
    }
    printGraph(graph);
    DFS(graph);
}