/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:38:26 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/22 19:57:24 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define DESCRIPTIVE_MSGS 1
# define MAX_LINES 30000
# define QUEUE_MAX 30000
# define DEBUGGING 0
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

// Data structure to store a graph node.
typedef struct s_node
{
	int				x;
	int				y;
	int				id;
	char			*name;
	int				visited;
	int				path_id;
	int				old_path_id;
	int				is_start;
	int				is_end;
	int				ant_present;
	struct s_node	*previous;
	struct s_node	*next;
}	t_node;

// Data structure to store a path object, made of any number of edge objects;
typedef struct s_path
{
	t_node	**nodes;
	int		path_length;
	int		ants;
}	t_path;

// Data structure to store an ant and its location on path
typedef struct s_ant
{
	int		id;
	int		progress;
	t_path	*path;
}	t_ant;

// Data structure to store a graph edge, made of two node objects.
typedef struct s_edge
{
	t_node	*start;
	t_node	*end;
	int		used_forwards;
	int		used_backwards;
}	t_edge;

// Data structure to store a graph object
typedef struct s_graph
{
	int		nb_of_nodes;
	int		nb_of_edges;
	int		nb_of_paths;
	int		nb_of_best_paths;
	int		ants_available;
	int		ants_placed;
	int		ants_finished;
	int		smallest_path;
	int		lines;
	int		path_found;
	int		least_nb_of_rounds;
	int		nb_of_rounds;
	int		backpedaled;

	t_node	*start;
	t_node	*end;
	t_node	**nodes;
	t_edge	**edges;
	t_path	**paths;
	t_path	**best_paths;
	t_ant	**ants;
	t_node	**history;
}	t_graph;

// Data structure to queue node objects
typedef struct s_queue
{
	t_node	**inp_arr;
	int		rear;
	int		front;
}	t_queue;

// Ants
void	advance_ants(t_graph *g, int i, int first_ant, int print);
void	place_ant_on_path(t_path *p, t_ant *a, t_graph *g);
void	place_all_ants(t_graph *g, int print);
t_ant	*new_ant(int id);
void	free_ant(t_ant *a);
void	reset_ants(t_graph *g);

// Queue
t_queue	*new_queue(size_t n);
t_node	*dequeue(t_queue *q);
void	enqueue(t_queue *q, t_node *node);
void	show(t_queue *q);
int		is_empty(t_queue *q);
void	debug_queue(t_queue *q);
void	free_queue(t_queue *q);

// Graph
t_graph	*create_graph(void);
int		validate_graph(t_graph *g);
void	reset_visit_status(t_graph *g);
void	free_graph(t_graph *g);

// Path
t_node	*find_path(t_node *node, t_graph *graph, int path_id);
int		traverse_path(t_graph *g, int path_id);
void	traverse_paths(t_graph *g);
void	save_paths_data(t_graph *g);
void	free_path(t_path *p);
t_path	*new_path(int path_length);
t_path	*create_path(t_graph *g, int path_id);
void	print_path(t_path *p);
int		count_nodes_with_path_id(t_graph *g, int path_id);
t_node	*find_next_node_in_path(t_node *node, t_graph *graph, int path_id);
t_path	*find_optimal_path(t_graph *g);

// Node
t_node	*create_node(char *name, int ret, int x, int y);
t_node	*get_node_by_name(char *name, t_node **nodes);
void	free_node(t_node *n);

// Edge
t_edge	*create_edge(t_node *start, t_node *end, t_graph *g);
void	print_edges(t_edge **edges);
void	print_edge(t_edge *edge);
void	free_edge(t_edge *e);
t_edge *find_double_used_edge(t_graph *g);

// Parser
int		parser(t_graph *graph);
void	handle_edges(char **lines, t_graph *g);
void	handle_nodes(char **lines, t_graph *g);
int		identify_line(char *line, int line_nb);

// Algorithms
int		bfs(t_graph *g, int tolerate_visit, t_node *start, t_node *end);
int		free_bfs(t_graph *g, t_queue *q);
int		backtrack(t_graph *graph, t_node *start, t_node *end)
t_node	*find_neighbour(t_node *node, t_graph *graph, int tolerate_visit);
void	visit_neighbour(t_node *nd, t_node *ng, t_queue *q, t_graph *g);
void	set_start_node(t_queue *q, t_graph *g, t_node *start);

// Path Augmentation
int		find_augmenting_paths(t_graph *g);

// Utility
int		count_c(char *l, char c);
int		count_lines_with_id(char **lines, int id);
void	exit_program(int ret, char *msg);

// Output
void	print_paths(t_path **p, int length_mode);
void	print_ant_movement(int ant_id, char *node_name, int first);
void	print_farm(t_graph *g);
void	print_nodes(t_node **nodes);
void	print_node(t_node *node);
void	print_graph(t_graph *graph);

#endif