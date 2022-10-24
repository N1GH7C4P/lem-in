/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:38:26 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/24 15:17:06 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <unistd.h>
# include <stdio.h>

// Define the maximum number of vertices in the graph
 #define N 6
 
typedef struct s_map
{
	int 	ants;
	t_node 	start;
	t_node 	end;
	t_graph	adj_list;
	int 	adj_matrix[N + 1][N + 1];
}	t_map;

void	set_ants(int ants, t_map *map);

// Data structure to store a graph object

typedef struct s_node
{
	int dest;
	char *name;
	int x;
	int y;
	struct s_node* next;
} t_node;

typedef struct s_graph
{
    // An array of pointers to Node to represent an adjacency list
    t_node* head[N];
} t_graph;
 
// Data structure to store adjacency list nodes of the graph

// Data structure to store a graph edge
typedef struct s_edge {
    int src, dest;
} t_edge;
 
t_graph* createGraph(t_edge edges[], int n, char **names);
void printGraph(t_graph* graph);
void createAdjMatrix(int Adj[][N + 1], int arr[][2], int M);
void printAdjMatrix(int Adj[][N + 1]);

#endif