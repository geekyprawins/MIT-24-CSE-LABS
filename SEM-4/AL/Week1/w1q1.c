#include <stdio.h>
#include <stdlib.h>

struct node {
  int vertex;
  struct node* next;
};
struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
};

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  newNode->next = graph->adjLists[s];
  graph->adjLists[s] = newNode;

  // Add edge from d to s
  newNode = createNode(s);
  newNode->next = graph->adjLists[d];
  graph->adjLists[d] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    printf("\n %d: ", v);
    while (temp) {
      printf(" -> %d ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}


int main(){

int v;
printf("Enter the number of vertices: \n");
scanf("%d", &v);

int e;
printf("Enter the number of edges: \n");
scanf("%d", &e);


int vertices[v];

// adj matrix
int adj_mat[v][v];
// adj list
struct Graph* graph = createAGraph(v);


for(int i= 0; i<v; i++){
	for(int j = 0; j < v; j++){
		adj_mat[i][j] = 0;
	}
}

for(int i = 0; i<v; i++){
	printf("Enter vertex %d :", i);
	scanf("%d", &vertices[i]);
}

int isEdge;
for(int i= 0; i<v; i++){

	for(int j= i+1; j<v; j++){
		printf("Is there an edge between %d and %d ? (0 or 1)", vertices[i], vertices[j]);
		scanf("%d", &isEdge);

		if(isEdge){
			adj_mat[i][j] = 1;
			adj_mat[j][i] = 1;
			addEdge(graph,vertices[i],vertices[j]);
		}
		else{
			adj_mat[i][j] = 0;
			adj_mat[j][i] = 0;
		}
	}
}


// adj matrix display


printf("Adjacency matrix is : \n");
for(int i= 0; i<v; i++){
	for(int j = 0; j < v; j++){
		printf("%d ", adj_mat[i][j]);
	}
	printf("\n");
}

// adj list display

printGraph(graph);

}