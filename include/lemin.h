/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:38:26 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/26 17:57:40 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define N 6
# define MAX_LINES 1000
# include <unistd.h>
# include <stdio.h>
# define QUEUE_MAX 1000

// Data structure to store a graph node.
typedef struct s_node
{
	char *name;
	int	visited;
	int	path_id;
	int	is_start;
	int	is_end;
	int x;
	int y;
} t_node;

// Data structure to store a graph edge
typedef struct s_edge {
	t_node *start;
	t_node *end;
} t_edge;

// Data structure to store a graph object
typedef struct s_graph
{
	int 	ants;
	int		nb_of_nodes;
	int		nb_of_edges;
	t_node 	*start;
	t_node 	*end;
	t_edge	**edges;
}	t_graph;

// Data structure to queue node objects
typedef struct s_queue
{
	t_node **inp_arr;
	int rear;
	int front;
} t_queue;

t_queue	*new_queue();
t_node	*dequeue(t_queue *q);
void	enqueue(t_queue *q, t_node *node);
void	show(t_queue *q);
int		is_empty(t_queue *q);

t_graph	*create_graph(void);
void	printGraph(t_graph* graph);

t_node	*find_univisited_node(t_node *node, t_graph *graph);
t_node	*create_node(int x, int y, char *name, int ret);
t_node	*get_node_by_name(char *name, t_node **nodes);
void	print_nodes(t_node **nodes, int v);
void	print_node(t_node *node, int v);

t_edge	*create_edge(t_node *start, t_node *end);
void	print_edges(t_edge **edges);
void	print_edge(t_edge *edge);

void createAdjMatrix(int Adj[][N + 1], int arr[][2], int M);
void printAdjMatrix(int Adj[][N + 1]);

void	set_ants(int ants, t_graph *graph);

// Parser

int	parser(t_graph *graph);

// Algorithms

int	bfs(t_graph *graph);

#endif