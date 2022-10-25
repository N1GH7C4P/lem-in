/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:38:26 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/25 18:24:59 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define MAX_LINES 1000
# include <unistd.h>
# include <stdio.h>

// Define the maximum number of vertices in the graph
 #define N 6

// Data structure to store a graph object

typedef struct s_node
{
	char *name;
	int	is_start;
	int	is_end;
	int x;
	int y;
} t_node;

t_node	*create_node(int x, int y, char *name, int ret);
t_node	*get_node_by_name(char *name, t_node **nodes);
void	print_nodes(t_node **nodes, int v);
void	print_node(t_node *node, int v);

// Data structure to store adjacency list nodes of the graph

// Data structure to store a graph edge
typedef struct s_edge {
	t_node *start;
	t_node *end;
} t_edge;

t_edge	*create_edge(t_node *start, t_node *end);
void	print_edges(t_edge **edges);
void	print_edge(t_edge *edge);

void createAdjMatrix(int Adj[][N + 1], int arr[][2], int M);
void printAdjMatrix(int Adj[][N + 1]);

typedef struct s_graph
{
	int 	ants;
	int		nb_of_nodes;
	int		nb_of_edges;
	t_node 	*start;
	t_node 	*end;
	t_edge	**edges;
}	t_graph;

t_graph	*create_graph(void);
void	printGraph(t_graph* graph);

void	set_ants(int ants, t_graph *graph);

// Parser

int	parser(t_graph *graph);

#endif