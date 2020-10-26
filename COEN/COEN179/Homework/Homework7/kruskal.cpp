/*
 * Tamir Enkhjargal
 * COEN 179 - Theory of Algorithms
 * Santa Clara University
 * 
 * Implementing Kruskal's Algorithm with disjoint sets
 *
 */


#include<iostream>
#include<string.h>

using namespace std;

class Graph {
	char vertices[12][12];
	int cost[12][12], v;
	public:
		Graph();
		void createGraph();
		void display();
		int Position(char[]);
		void kruskal();
};

// Initializes a graph with max size 12x12
// and makes cost of all nodes 100 (indicates infinity)
Graph::Graph() {
	v = 0;
	for(int i = 0; i < 12; i++)
		for(int j = 0; j < 12; j++)
			cost[i][j] = 100;
}

/* Taking inputs for creating graph */
void Graph::createGraph() {
	char ans, Start[12], End[12];
	int weight, i, j;
  cout<<"Enter the number of vertices: ";
  cin>>v;
  cout<<"\nEnter the vertices: ";
  for(i=0;i<v;i++)
          cin>>vertices[i];
  do
  {
    cout<<"\nEnter Start and End vertex of the edge: ";
    cin>>Start>>End;
    cout<<"Enter weight: ";
    cin>>weight;
    i=Position(Start);
    j=Position(End);
    cost[i][j]=cost[j][i]=weight;
    cout<<"\nDo you want to add more edges (Y=YES/N=NO)? : ";  /* Type 'Y' or 'y' for YES and 'N' or 'n' for NO */
    cin>>ans;
  }while(ans=='y' || ans=='Y');
}

/* Displaying Cost matrix */
void Graph::display() {
	int i, j;
	cout << "\n\nCost matrix: ";
	for(i = 0;i < v; i++) {
		cout << "\n";
	for(j = 0; j < v; j++)
		cout << "\t" << cost[i][j];
	}
}

/* Retrieving position of vertices in 'vertices' array */
int Graph::Position(char key[10]) {
	for(int i = 0; i < 10; i++)
		if( strcmp(vertices[i], key)==0 )
			return i;
	return -1;     
}

void Graph::kruskal() {
	int i, j, x, y, min, temp, d;
	int vec[12]={0};
	int Total_cost, flag = 0;
	int gr=1;
	
	while(flag == 0) {
		min = 100;
		for(i = 0; i < v; i++) {  
			for(j = 0; j < v; j++) {
				if(cost[i][j] < min) {
					min = cost[i][j];
					x = i;
					y = j;
				}
			}
		}

		if(vec[x] == 0 && vec[y] == 0) {
			vec[x] = vec[y] = gr;
			gr++;
		}
		else if(vec[x] != 0 && vec[y] == 0)
			vec[y] = vec[x];
		else if(vec[x] == 0 && vec[y] != 0)
			vec[x] = vec[y];
		else {
			if(vec[x] != vec[y]) {
				d = vec[x];
				for(i = 0; i < v; i++) {
					if(vec[i] == d)
						vec[i] = vec[y];
				}
			}
		}

		cost[x][y] = cost[y][x] = 100;
		Total_cost = Total_cost+min;      /* calculating cost of minimum spanning tree */
		cout << "\n\t" << vertices[x] << "\t\t" << vertices[y] << "\t\t" << min;

		temp = vec[0];
		flag = 1;
		for(i = 0; i < v; i++) {
			if(temp != vec[i]) {
				flag = 0;
				break;
			}
		}
	}	// End While Loop

	cout << "\nTotal cost of the tree= " << Total_cost;
}


int main() {
	Graph g;
	g.createGraph();
	g.display();
	cout << "\n\n\nMinimum Spanning tree using kruskal algo=>";
	cout << "\nSource vertex\tDestination vertex\tWeight\n";
	g.kruskal();
	return 0;
}
