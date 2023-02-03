/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:58:50 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/03 12:04:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

static void	check_smallest_path(t_graph *g, t_node *n)
{
	if (n->is_end && g->history[n->id]->is_start)
		if (!g->smallest_path)
			g->smallest_path = 1;
}

static void	visit_node(t_node *n, t_graph *g, int path_id)
{
	n->visited = 2;
	if (n->path_id)
	{
		n->old_path_id = n->path_id;
		n->visited = 3;
	}
	n->path_id = path_id;
	if (n->is_start != 1)
	{
		n->previous = g->history[n->id];
		g->history[n->id]->next = n;
	}
}

int	backtrack(t_graph *graph, t_node *start, t_node *end, int path_id)
{
	t_node	*node;

	node = end;
	if (node->path_id)
		node->old_path_id = node->path_id;
	node->path_id = path_id;
	while (node)
	{
		if (DEBUGGING > 0)
			print_node(node);
		check_smallest_path(graph, node);
		node = graph->history[node->id];
		visit_node(node, graph, path_id);
		if (node == start)
			break ;
	}
	reset_visit_status(graph);
	return (1);
}

int	free_bfs(t_graph *g, t_queue *q)
{
	
	free_queue(q);
	free(g->history);
	if (g->path_found)
	{
		g->path_found = 0;
		return (1);
	}
	return (0);
}

void	set_start_node(t_queue *q, t_graph *g, t_node *start)
{
		if (DEBUGGING > 0)
			print_node(start);
		enqueue(q, g->start);
		start->visited = 1;
}

void	visit_neighbour(t_node *nd, t_node *ng, t_queue *q, t_graph *g)
{
	enqueue(q, ng);
	ng->visited = 1;
	nd->next = ng;
	ng->previous = nd;
	g->history[ng->id] = nd;
	if (ng->is_end == 1)
	{
		if (DEBUGGING > 0)
			ft_putendl("end node visited");
		g->path_found = 1;
	}
}

int	bfs(t_graph *g, int tolerate_visit, t_node *start, t_node *end)
{
	t_node	*node;
	t_node	*neighbour;
	static	t_queue* q;
	int			path_id;

	if (DEBUGGING > 0)
		ft_putendl("running bfs");
	q = new_queue(g->nb_of_nodes + 1);
	g->history = (t_node **)malloc(sizeof(t_node *) * (g->nb_of_nodes + 1));
	set_start_node(q, g, start);
	while (!is_empty(q) && g->path_found != 1)
	{
		node = dequeue(q);
		if (DEBUGGING > 0)
			print_node(node);
		neighbour = find_neighbour(node, g, tolerate_visit);
		while (neighbour)
		{
			visit_neighbour(node, neighbour, q, g);
			neighbour = find_neighbour(node, g, tolerate_visit);
		}
	}
	if (g->path_found == 1)
	{
		if (DEBUGGING > 0)
			ft_putendl("backtracking");
		path_id = find_first_free_path_id(g);
		backtrack(g, start, end, path_id);
		if (DEBUGGING > 0)
			ft_putendl("creating path");
		g->paths[path_id - 1] = create_path(g, path_id);
		if (DEBUGGING > 0)
		{
			ft_putendl("printing path");
			print_path(g->paths[path_id - 1]);
		}
	}
	if (DEBUGGING > 0)
		ft_putendl("exiting bfs");
	return (free_bfs(g, q));
}
