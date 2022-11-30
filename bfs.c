#include <stdio.h>
#include <stdlib.h>
#define SIZE 40
typedef struct queue
{
    int items[SIZE];
    int front;
    int rear;
} queue;
queue *createQueue();
void enqueue(queue *q, int);
int dequeue(queue *q);
void display(queue *q);
int isEmpty(queue *q);
void printQueue(struct queue *q);
typedef struct node
{
    int vertex;
    struct node *next;
} node;
node *createNode(int);
typedef struct Graph
{
    int numVertices;
    node **adjLists;
    int *visited;
} Graph;
void bfs(Graph *graph, int startVertex)
{
    queue *q = createQueue();
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    while (!isEmpty(q))
    {
        printQueue(q);
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
        node *temp = graph->adjLists[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            if (graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}
node *createNode(int v)
{
    node *newNode = malloc(sizeof(node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
Graph *createGraph(int vertices)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(node *));
    graph->visited = malloc(vertices * sizeof(int));
    int i;
    for (i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
void addEdge(Graph *graph, int src, int dest)
{
    node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
queue *createQueue()
{
    queue *q = malloc(sizeof(queue));
    q->front = -1;
    q->rear = -1;
    return q;
}
int isEmpty(queue *q)
{
    if (q->rear == -1)
        return 1;
    else
        return 0;
}
void enqueue(queue *q, int value)
{
    if (q->rear == SIZE - 1)
        printf("\nQueue is Full!!");
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}
int dequeue(queue *q)
{
    int item;
    if (isEmpty(q))
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            printf("Resetting queue ");
            q->front = q->rear = -1;
        }
    }
    return item;
}
void printQueue(queue *q)
{
    int i = q->front;
    if (isEmpty(q))
    {
        printf("Queue is empty");
    }
    else
    {
        printf("\nQueue contains \n");
        for (i = q->front; i < q->rear + 1; i++)
        {
            printf("%d ", q->items[i]);
        }
    }
}
int main()
{
    int vertices, key, edges, u, v;
    printf("Enter number of vertices for the graph: ");
    scanf("%d", &vertices);
    Graph *graph = createGraph(vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    printf("Enter the vertices on the edges: ");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }
    bfs(graph, 0);
    return 0;
}
