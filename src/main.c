/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/23 23:42:49 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

// Directed graph implementation in C
int main(void)
{

    int M;

    // input array containing edges of the graph (as per the above diagram)
    // (x, y) pair in the array represents an edge from x to y
    //t_edge edges[] =
    //{
    //    {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    //};
  
    // Given Edges
    int arr[][2] = {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    };
  
    // Number of Edges
    M = sizeof(arr) / sizeof(arr[0]);
  
    // For Adjacency Matrix
    int Adj[N + 1][N + 1];
  
    // Function call to create
    // Adjacency Matrix
    createAdjMatrix(Adj, arr, M);
  
    // Print Adjacency Matrix
    printAdjMatrix(Adj);
  
    // calculate the total number of edges
    //int n = sizeof(edges)/sizeof(edges[0]);
 
    // construct a graph from the given edges
    //t_graph *graph = createGraph(edges, n, argv);
 
    // Function to print adjacency list representation of a graph
    //printGraph(graph);
 
    return 0;
}
