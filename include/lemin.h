/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:38:26 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/23 23:37:04 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <unistd.h>
# include <stdio.h>

// Define the maximum number of vertices in the graph
 #define N 6
 
 
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