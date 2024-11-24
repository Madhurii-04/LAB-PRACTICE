#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 9999  

int adj_mat[MAX][MAX] = {999};  
int heuristic[MAX];    
int gCost[MAX];         
int fCost[MAX];
int visited[MAX];
int num_vertices, num_edges;   
int open_list[MAX],closed_list[MAX];  


int findMinFCost() 
{
    int minIndex = -1, minValue = INF;
    for (int i = 0; i < num_vertices; i++) 
    {
        //if (!visited[i] && fCost[i] < minValue) 
        if(open_list[i] && fCost[i] < minValue)
        {
            minValue = fCost[i];
            minIndex = i;
        }
    }
    return minIndex; 
}


void A_star(int start, int goal) 
{

    for (int i = 0; i < num_vertices; i++) 
    {
        gCost[i] = INF;
        fCost[i] = INF;
        //visited[i] = 0;
        open_list[i] = 0;
        closed_list[i] = 0;
    }
    
    gCost[start] = 0;
    fCost[start] = heuristic[start];
    open_list[start] = 1;

    while (1) 
    {
        int current = findMinFCost();

        if (current == -1) 
        {
            printf("No path to the goal node found.\n");
            return;
        }

        if (current == goal) 
        {
            printf("Goal node %d reached with cost %d.\n", goal, gCost[goal]);
            return;
        }

        //visited[current] = 1;

        open_list[current] = 0;
        closed_list[current] = 1;

        printf("Visited node: %d\n", current);

        for (int i = 0; i < num_vertices; i++) 
        {
            //if (adj_mat[current][i] && !visited[i]) 
            if(adj_mat[current][i] && !closed_list[i])
            {  
                int tentativeGCost = gCost[current] + adj_mat[current][i];

                if (!open_list[i]) 
                {  
                    open_list[i] = 1;
                }

                if (tentativeGCost < gCost[i]) 
                {
                    gCost[i] = tentativeGCost;
                    fCost[i] = gCost[i] + heuristic[i];
                }
            }
        }
    }
}

int main() 
{
    int start, goal;
    int src,dest,weight;

    printf("Enter the number of nodes: ");
    scanf("%d", &num_vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &num_edges);

    for (int i = 0; i < num_edges; i++)
    {
        printf("\nEnter edge %d (formatt---->source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        adj_mat[src][dest] = weight;
        adj_mat[dest][src] = weight;
    }


    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < num_vertices; i++) 
    {
        scanf("%d", &heuristic[i]);
    }


    printf("Enter the start node: ");
    scanf("%d", &start);
    printf("Enter the goal node: ");
    scanf("%d", &goal);

    A_star(start, goal);

    return 0;
}
