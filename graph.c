#include<stdio.h>
#include<stdlib.h>
struct node{
    int vertex;
    struct node* next; 
};
struct Graph{
    int novertices;
    struct node**sides;
};
typedef struct node node;
typedef struct Graph Graph;
Graph* createGraph(int vert){
    Graph* graph=malloc(sizeof(Graph));
    graph->novertices=vert;
    graph->sides=malloc(vert*sizeof(node*));
    for(int i=0;i<vert;i++)
        graph->sides[i]=NULL;
    return graph;
}
node* createNode(int vertx){
    node*Node=malloc(sizeof(node));
    Node->vertex=vertx;
    Node->next=NULL;
    return Node;
}
void addEdge(Graph* graph, int s, int d) {
  node* newNode = createNode(d);
  newNode->next = graph->sides[s];
  graph->sides[s] = newNode;

  newNode = createNode(s);
  newNode->next = graph->sides[d];
  graph->sides[d] = newNode;
}
void printGraph(Graph* graph) {
  for (int v = 0; v < graph->novertices; v++) {
    struct node* temp = graph->sides[v];
    printf("\n %d: ", v);
    while (temp) {
      printf("->%d ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}
int main() {
  Graph* graph2 = createGraph(6);
  addEdge(graph2, 0, 1);
  addEdge(graph2, 0, 2);
  addEdge(graph2, 0, 4);
  addEdge(graph2, 0, 3);
  addEdge(graph2, 1, 2);
  addEdge(graph2,1,4);
  printGraph(graph2);

  return 0;
}