/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:13:55 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/23 23:35:46 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/lemin.h"
#include "../libft/libft.h"

// Function to create an adjacency list from specified edges

// Function to create Adjacency Matrix
void createAdjMatrix(int Adj[][N + 1],
                     int arr[][2], int M)
{
  
    // Initialise all value to this
    // Adjacency list to zero
    for (int i = 0; i < N + 1; i++) {
  
        for (int j = 0; j < N + 1; j++) {
            Adj[i][j] = 0;
        }
    }
  
    // Traverse the array of Edges
    for (int i = 0; i < M; i++) {
  
        // Find X and Y of Edges
        int x = arr[i][0];
        int y = arr[i][1];
  
        // Update value to 1
        Adj[x][y] = 1;
        Adj[y][x] = 1;
    }
}
  
// Function to print the created
// Adjacency Matrix
void printAdjMatrix(int Adj[][N + 1])
{
  
    // Traverse the Adj[][]
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
  
            // Print the value at Adj[i][j]
            ft_putnbr(Adj[i][j]);
        }
        ft_putendl("");
    }
}


t_graph* createGraph(t_edge edges[], int n, char **names)
{
    // allocate storage for the graph data structure
    t_graph* graph = (t_graph *)malloc(sizeof(t_graph));
 
    // initialize head pointer for all vertices
    for (int i = 0; i < N; i++) {
        graph->head[i] = NULL;
    }
 
    // add edges to the directed graph one by one
    for (int i = 0; i < n; i++)
    {
        // get the source and destination vertex

        // allocate a new node of adjacency list from src to dest
        t_node* newNode = (t_node*)malloc(sizeof(t_node));
        newNode->dest = edges[i].dest;
		newNode->name = ft_strdup(names[i + 1]);

        // point new node to the current head
        newNode->next = graph->head[edges[i].src];
 
        // point head pointer to the new node
        graph->head[edges[i].src] = newNode;
    }
 
    return graph;
}
 
// Function to print adjacency list representation of a graph
void printGraph(t_graph* graph)
{
    for (int i = 0; i < N; i++)
    {
        // print current vertex and all its neighbors
       t_node* ptr = graph->head[i];
        while (ptr != NULL)
        {
			ft_putendl(ptr->name);
            ft_putnbr(i);
			ft_putstr(" -> ");
			ft_putnbr(ptr->dest);
			ft_putendl("");
            ptr = ptr->next;
        }
    }
}
