#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5
int stack[MAX], top;
typedef struct node
{
    int dest;
    int weight;
    struct node *next;
} node;
typedef struct ad_list
{
    struct node *head;
} ad_list;
typedef struct graph
{
    int N;
    int *visited;
    struct ad_list *arr;
} graph;
graph *gr, *grcpy;
node *create_node(int d, int w)
{
    node *nnode = (node *)malloc(sizeof(node));
    nnode->dest = d;
    nnode->weight = w;
    nnode->next = NULL;
    return nnode;
}

graph *crt_grph(int N)
{
    graph *gr = (graph *)malloc(sizeof(graph));
    gr->N = N;
    gr->arr = (ad_list *)malloc(sizeof(ad_list));
    return gr;
}
void get_transpose(graph *grcpy, int src, int d, int w)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->next = grcpy->arr[d].head;
    grcpy->arr[d].head = newNode;
}

void add_edge(graph *gr, graph *grcpy, int src, int d, int w)
{
    node *nnode = create_node(d, w);
    nnode->next = gr->arr[src].head;
    gr->arr[src].head = nnode;
    get_transpose(grcpy, src, d, w);
}

void PrintGraph(graph *gr)
{
    for (int v = 0; v < gr->N; v++)
    {
        node *temp = gr->arr[v].head;
        printf("%d", v);
        while (temp)
        {
            printf("->%d(%d)\t", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}
void push(int x)
{
    if (top >= MAX - 1)
    {
        printf("\n\tSTACK is over flow");
    }
    else
    {
        top++;
        stack[top] = x;
    }
}

void pop()
{
    if (top <= -1)
    {
        printf("\n\t Stack is under flow");
    }
    else
    {
        top-- ;
    }
}
void set_fill_order(graph *graph, int v, bool visited[], int *stack)
{
    visited[v] = true;
    int i = 0;
    struct node *temp = graph->arr[v].head;
    while (temp)
    {
        if (!visited[temp->dest])
        {
            set_fill_order(graph, temp->dest, visited, stack);
        }
        temp = temp->next;
    }
    push(v);
}
void dfs_recursive(graph *gr, int v, bool visited[])
{
    visited[v] = true;
    printf("% d ", v);
    struct node *temp = gr->arr[v].head;
    while (temp)
    {
        if (!visited[temp->dest])
        {
            dfs_recursive(gr, temp->dest, visited);
        }
        temp = temp->next;
    }
}
void strongly_connected_components(graph *gr, graph *grcpy, int V)
{
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false)
        {
            set_fill_order(gr, i, visited, stack);
        }
    }
    int count = 1;
    for (int i = 0; i < V; i++)
        visited[i] = false;
    while (top != -1)
    {
        int v = stack[top];
        pop();
        if (visited[v] == false)
        {
            printf("Strongly connected component % d: \n", count++);
            dfs_recursive(grcpy, v, visited);
            printf("\n");
        }
    }
}

int main()
{
    top = -1;
    int v = 5;
    struct graph *gr = crt_grph(v);
    struct graph *grcpy = crt_grph(v);
    add_edge(gr, grcpy, 1, 0, 2);
    add_edge(gr, grcpy, 0, 2, 2);
    add_edge(gr, grcpy, 2, 1, 2);
    add_edge(gr, grcpy, 0, 3, 2);
    add_edge(gr, grcpy, 3, 4, 2);
    strongly_connected_components(gr, grcpy, v);
    return 0;
}