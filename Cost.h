#include <limits.h>
#define V 12 

int minDistance(int dist[], bool sptSet[]) 
{ 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < V; v++) 
		if (sptSet[v] == false && dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 

int dijkstra(int src,int des) 
{ 
	int graph[V][V] = {{0  , 4, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  }, 
			   {4, 0  , 11 , 6, 7, 0  , 0  , 0  , 0  , 0  , 0  , 0  }, 
	    		   {0  , 11 , 0  , 0  , 0  , 8, 0  , 6  , 0  , 0  , 0  , 0  }, 
			   {0  , 6, 0  , 0  , 0  , 0  , 9, 8, 0  , 0  , 0  , 0  }, 
	    		   {0  , 7, 0  , 0  , 0  , 0  , 0  , 3  , 0  , 0  , 0  , 0  }, 
			   {0  , 0  , 8, 0  , 0  , 0  , 0  , 13 , 11 , 0  , 0  , 0  }, 
	    		   {0  , 0  , 0  , 9, 0  , 0  , 0  , 11 , 0  , 0  , 9, 5}, 
			   {0  , 0  , 6  , 8, 3  , 13 , 11 , 0  , 7, 8, 11 , 0  }, 
	    		   {0  , 0  , 0  , 0  , 0  , 11 , 0  , 7, 0  , 5, 0  , 0  }, 
			   {0  , 0  , 0  , 0  , 0  , 0  , 0  , 8, 5, 0  , 9  , 0  }, 
			   {0  , 0  , 0  , 0  , 0  , 0  , 9, 11 , 0  , 9  , 0  , 8}, 
			   {0  , 0  , 0  , 0  , 0  , 0  , 6, 0  , 0  , 0  , 8, 0  }};

	int dist[V]; 
	bool sptSet[V];

	for (int i = 0; i < V; i++) 
		dist[i] = INT_MAX, sptSet[i] = false; 

	dist[src] = 0; 

	for (int count = 0; count < V - 1; count++) { 
		int u = minDistance(dist, sptSet); 

		sptSet[u] = true; 

		for (int v = 0; v < V; v++) 
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) 
				dist[v] = dist[u] + graph[u][v]; 
	} 

return(dist[des]); 
} 

int Cost(int i, int j) {

	int distance, cost;

	distance = dijkstra(i, j); 

	cost = distance * 10;

	return cost; 
} 

