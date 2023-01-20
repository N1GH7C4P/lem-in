/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:58:50 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/20 16:41:50 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void	check_smallest_path(t_graph *g, int direction, t_node *n)
{
	if (direction == 1)
	{
		if (n->is_end && g->history[n->id]->is_start)
			if (!g->smallest_path)
				g->smallest_path = 1;
	}
	else
	{
		if (n->is_start && g->history[n->id]->is_end)
			if (!g->smallest_path)
				g->smallest_path = 1;
	}
}

static void	visit_node(t_node *n, t_graph *g)
{
	if (n->visited == 1)
		n->visited = 2;
	else if (n->visited == 2)
	{
		n->old_path_id = n->path_id;
		n->visited = 3;
	}
	n->path_id = g->nb_of_paths;
	if (n->is_start != 1)
	{
		n->previous = g->history[n->id];
		g->history[n->id]->next = n;
	}
}

int	backtrack(t_graph *graph, int direction)
{
	t_node	*node;

	if (direction == 1)
		node = graph->end;
	else
		node = graph->start;
	graph->nb_of_paths = graph->nb_of_paths + 1;
	node->path_id = graph->nb_of_paths;
	while (node)
	{
		check_smallest_path(graph, direction, node);
		node = graph->history[node->id];
		visit_node(node, graph);
		if (node->is_start || node->is_end)
			break ;
	}
	reset_visit_status(graph);
	return (1);
}

static int	free_bfs(t_graph *g, t_queue *q)
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

static void		set_start_node(t_queue *q, t_graph *g, int direction)
{
	if (direction == 1)
	{
		enqueue(q, g->start);
		g->start->visited = 1;
	}
	else
	{
		enqueue(q, g->end);
		g->end->visited = 1;
	}
}

static t_node	*visit_neighbour(t_node *nd, t_node *ng, t_queue *q, t_graph *g)
{
	ng->visited = 1;
	g->history[ng->id] = nd;
	enqueue(q, ng);
	if (ng->is_end == 1 || ng->is_start == 1)
	{
		g->path_found = 1;
		return (NULL);
	}
	ng = find_neighbour(nd, g);
	return (ng);
}

int	bfs(t_graph *g, int direction)
{
	t_node	*node;
	t_node	*neighbour;
	static	t_queue* q; 

	q = new_queue(g->nb_of_nodes + 1);
	g->history = (t_node **)malloc(sizeof(t_node *) * (g->nb_of_nodes + 1));
	set_start_node(q, g, direction);
	while (!is_empty(q) && g->path_found != 1)
	{
		node = dequeue(q);
		neighbour = find_neighbour(node, g);
		while (neighbour)
			neighbour = visit_neighbour(node, neighbour, q, g);
	}
	if (g->path_found)
		backtrack(g, direction);
	return (free_bfs(g, q));
}
