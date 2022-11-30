#include <stdio.h>
#include <stdlib.h>
struct Edge
{
    int u;
    int v;
    int w;
};
struct Graph
{
    int V;
    int E;
    struct Edge *edge;
};
void bellmanford(struct Graph *g, int source);
void display(int arr[], int size);
int main(void)
{
    struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
    printf("Enter number of vertices for the graph: ");
    int v;
    scanf("%d", &g->V);
    printf("Enter number of edges: ");
    int e;
    scanf("%d", &g->E);
    g->edge = (struct Edge *)malloc(g->E * sizeof(struct Edge));
    printf("Enter vertex on the edges and the weight: ");
    int v1, v2, w;
    for (int i = 0; i < g->E; i++)
    {
        scanf("%d %d %d", &g->edge[i].u, &g->edge[i].v, &g->edge[i].w);
    }
    bellmanford(g, 0);
    return 0;
}
void bellmanford(struct Graph *g, int source)
{
    int i, j, u, v, w;
    int tV = g->V;
    int tE = g->E;
    int d[tV];
    int p[tV];
    for (i = 0; i < tV; i++)
    {
        d[i] = INT_MAX;
        p[i] = 0;
    }
    d[source] = 0;
    for (i = 1; i <= tV - 1; i++)
    {
        for (j = 0; j < tE; j++)
        {
            u = g->edge[j].u;
            v = g->edge[j].v;
            w = g->edge[j].w;
            if (d[u] != INT_MAX && d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                p[v] = u;
            }
        }
    }
    for (i = 0; i < tE; i++)
    {
        u = g->edge[i].u;
        v = g->edge[i].v;
        w = g->edge[i].w;
        if (d[u] != INT_MAX && d[v] > d[u] + w)
        {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }
    printf("Distance array: ");
    display(d, tV);
    printf("Parent array: ");
    display(p, tV);
}
void display(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}