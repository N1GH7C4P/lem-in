/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:38:26 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/01 23:35:39 by kpolojar         ###   ########.fr       */
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
	int id;
	char *name;
	int	visited;
	int	path_id;
	int	is_start;
	int	is_end;
	int x;
	int y;
} t_node;

// Data structure to store a graph edge, made of two node objects.
typedef struct s_edge
{
	t_node *start;
	t_node *end;
} t_edge;

// Data structure to store a path object, made of any number of edge objects;
typedef struct s_path
{
	t_node	**nodes;
	int		path_length;
} t_path;

// Data structure to store a graph object
typedef struct s_graph
{
	int 	ants;
	int		nb_of_nodes;
	int		nb_of_edges;
	int		nb_of_paths;

	t_node 	*start;
	t_node 	*end;
	t_node	**nodes;
	t_edge	**edges;
	t_path	**paths;
}	t_graph;

// Data structure to queue node objects
typedef struct s_queue
{
	t_node **inp_arr;
	int rear;
	int front;
} t_queue;


int		count_nodes_with_path_id(t_graph *g, int path_id);
t_node	*find_next_node_in_path(t_node *node, t_graph *graph, int path_id);
void	delete_path(t_path *p);
t_path	*new_path(int path_length);
t_path	*create_path(t_graph *g, int path_id);
void	traverse_paths(t_graph *g);
void	print_path(t_path *p);

t_queue	*new_queue();
t_node	*dequeue(t_queue *q);
void	enqueue(t_queue *q, t_node *node);
void	show(t_queue *q);
int		is_empty(t_queue *q);

t_graph	*create_graph(void);
t_node	*find_path(t_node *node, t_graph *graph, int path_id);
int		traverse_path(t_graph *g, int path_id);
void	traverse_paths(t_graph *g);
void	printGraph(t_graph* graph);
void	reset_visit_status(t_graph *g);

t_node	*find_neighbour(t_node *node, t_graph *graph);
t_node	*create_node(int x, int y, char *name, int ret);
t_node	*get_node_by_name(char *name, t_node **nodes);
void	print_nodes(t_node **nodes, int v);
void	print_node(t_node *node, int v);

t_edge	*create_edge(t_node *start, t_node *end);
void	print_edges(t_edge **edges);
void	print_edge(t_edge *edge);

void	createAdjMatrix(int Adj[][N + 1], int arr[][2], int M);
void 	printAdjMatrix(int Adj[][N + 1]);

void	set_ants(int ants, t_graph *graph);

// Parser

int	parser(t_graph *graph);

// Algorithms

int	bfs(t_graph *graph);

#endif