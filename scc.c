#include <stdio.h>
#include <stdlib.h>
#define MAX 100
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
typedef struct Stack
{
    int array[MAX];
    int top;
} Stack;
Stack *stack;
void push(int val)
{
    if (stack->top == MAX - 1)
        return;
    stack->array[++stack->top] = val;
}
int pop()
{
    if (stack->top == -1)
        return -1;
    return stack->array[stack->top--];
}
int isEmpty()
{
    return stack->top == -1;
}
int search(Graph *graph, int v1)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        if (graph->adjList[i]->key == v1)
        {
            return i;
        }
    }
    return -1;
}
void DFSVisit(Graph *graph, int value)
{
    int index = search(graph, value);
    Node *temp = graph->adjList[index]->next;
    graph->visited[index] = 1;
    while (temp != NULL)
    {
        printf("%d ", temp->key);
        int i = search(graph, temp->key);
        if (graph->visited[i] == 0)
        {
            DFSVisit(graph, temp->key);
        }
        temp = temp->next;
    }
    push(value);
}
void DFS(Graph *graph, int v)
{
    for (int i = 0; i < v; i++)
    {
        graph->visited[i] = 0;
    }
    for (int i = 0; i < v; i++)
    {
        if (graph->visited[i] == 0)
            DFSVisit(graph, graph->adjList[i]->key);
    }
}
void DFSVisitPrint(Graph *graph, int value)
{
    int index = search(graph, value);
    Node *temp = graph->adjList[index]->next;
    graph->visited[index] = 1;
    printf("%d", value);
    while (temp != NULL)
    {
        int i = search(graph, temp->key);
        if (graph->visited[i] == 0)
        {
            DFSVisitPrint(graph, temp->key);
        }
        temp = temp->next;
    }
}
void SCC(Graph *graph, Graph *transGraph)
{
    DFS(graph, graph->vertices);
    for (int i = 0; i < graph->vertices; i++)
    {
        transGraph->visited[i] = 0;
    }
    while (!isEmpty())
    {
        int u = pop();
        if (!transGraph->visited[search(transGraph, u)])
        {
            printf("Component: ");
            DFSVisitPrint(transGraph, u);
            printf("\n");
        }
    }
}
Node *createNode(int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = val;
    node->next = NULL;
    return node;
}
Graph *addEdge(Graph *graph, int src, int trg)
{
    int index = search(graph, src);
    Node *newNode = createNode(trg);
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
            printf("%d ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}
int main()
{
    printf("Enter number of vertices for the graph: ");
    int v;
    scanf("%d", &v);
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->adjList = (Node **)malloc(v * sizeof(Node *));
    Graph *transGraph = (Graph *)malloc(sizeof(Graph));
    transGraph->adjList = (Node **)malloc(v * sizeof(Node *));
    printf("Enter number of edges: ");
    int e;
    scanf("%d", &e);
    stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    graph->visited = (int *)malloc(v * sizeof(int));
    printf("Enter vertices: ");
    for (int i = 0; i < v; i++)
    {
        int vertex;
        scanf("%d", &vertex);
        graph->adjList[i] = createNode(vertex);
        transGraph->adjList[i] = createNode(vertex);
    }
    printf("Enter edges: ");
    for (int i = 0; i < e; i++)
    {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        graph = addEdge(graph, v1, v2);
        transGraph = addEdge(transGraph, v2, v1);
    }
    printGraph(graph);
    SCC(graph, transGraph);
}