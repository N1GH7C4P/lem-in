/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_augmentation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:48:26 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/01 11:39:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int		count_nodes_before_crossover(t_path *p, t_edge *e)
{
	int i;

	i = 0;
	while (p->nodes[i])
	{
		print_node(p->nodes[i]);
		if (e->start == p->nodes[i] || e->end == p->nodes[i])
			break;
		i++;
	}
	ft_putendl("counted befre");
	return (i + 1);
}

int		count_nodes_after_crossover(t_path *p, t_edge *e)
{
	int i;

	i = 0;
	while (p->nodes[i])
	{
		print_node(p->nodes[i]);
		if (e->start == p->nodes[i] || e->end == p->nodes[i])
			break;
		i++;
	}
	ft_putendl("counted fter");
	return (p->path_length - i - 1);
}

int		find_edge_index_in_path(t_path *p, t_edge *e)
{
	int i;

	i = 0;
	while (p->nodes[i] != e->end && p->nodes[i] != e->start)
	{
		i++;
	}
	return (i);
}

void	combine_paths(t_path *dest, t_path *src1, t_path *src2, t_edge *e)
{
	int i;

	i = 0;
	while (src1->nodes[i] != e->end && src1->nodes[i] != e->start)
	{
		dest->nodes[i] = src1->nodes[i];
		i++;
	}
	dest->nodes[i] = src1->nodes[i];
	i = find_edge_index_in_path(src2, e);
	while (src2->nodes[i])
	{
		dest->nodes[i] = src2->nodes[i];
		i++;
	}
	print_path(dest);
}

void	fix_paths(t_path *p1, t_path *p2, t_edge *e)
{
	int 	len;
	t_path	*new;

	len = count_nodes_after_crossover(p1, e) + count_nodes_before_crossover(p2, e);
	ft_putnbr(len);
	new = new_path(len);
	combine_paths(new, p1, p2, e);
}

void	the_great_switcharoo(t_graph *g)
{
	t_edge	*double_used;
	t_path	*p1;
	t_path	*p2;

	double_used = find_double_used_edge(g);
	p1 = g->paths[double_used->start->old_path_id];
	p2 = g->paths[double_used->end->path_id];
	ft_putnbr(p1->nodes[1]->path_id);
	ft_putnbr(p2->nodes[1]->path_id);
	fix_paths(p1, p2, double_used);
}


static t_node *check_aug_edge(t_edge *e, t_node *n, int tolerate_visit)
{
	if (n == e->end && e->start->visited == 0)
	{
		if (tolerate_visit == 1 && e->start->is_start == 0)
			return (e->start);
		else if (e->start->path_id == 0)
			return (e->start);
	}
	else if (n == e->start && e->end->visited == 0)
	{
		if (tolerate_visit == 1 && e->end->is_start == 0)
			return (e->end);
		else if (e->end->path_id == 0)
			return (e->end);
	}
	return (NULL);
}

// Finds neighbous of node (n) in graph (g)
static t_node	*find_augmenting_neighbour(t_node *n, t_graph *g)
{
	int 	i;
	t_node	*ret;

	i = 0;
	while (i < g->nb_of_edges - 1)
	{
		if (n->is_start == 1)
			ret = check_aug_edge(g->edges[i], n, 0);
		else
			ret = check_aug_edge(g->edges[i], n, 1);
		if (ret && ret->first_node_in_path != 1)
		{
			ft_putendl("free node found");
			print_node(ret);
			return (ret);
		}
		i++;
	}
	i = 0;
	ft_putendl("no more free nodes");
	return (NULL);
}

t_node *find_backpedal_node(t_node *n,  t_graph *g)
{
	int i;

	i = 0;
	while (i < g->nb_of_edges)
	{
		if (g->edges[i]->start == n)
		{
			if (g->edges[i]->end->path_id == n->path_id && g->edges[i]->used_backwards == 1)
			{
				if (g->edges[i]->end->is_start == 0 && g->edges[i]->end->first_node_in_path == 0)
				{
					ft_putendl("backpedal found");
					print_edge(g->edges[i]);
					ft_putendl("");
					print_node(g->edges[i]->end);
					return (g->edges[i]->end);
				}
				else
				{
					ft_putendl("no backpedaling to start node.");
				}
			}
		}
		if (g->edges[i]->end == n)
		{
			if (g->edges[i]->start->path_id == n->path_id && g->edges[i]->used_forwards == 1)
			{
				if (g->edges[i]->start->is_start == 0 && g->edges[i]->start->first_node_in_path != 1)
				{
					ft_putendl("backpedal found");
					print_edge(g->edges[i]);
					ft_putendl("");
					print_node(g->edges[i]->start);
					return (g->edges[i]->start);
				}
				else
				{
					ft_putendl("no backpedaling to start node.");
				}
			}
		}
		i++;
	}
	ft_putendl("impossible to backpedal");
	return (NULL);
}

int	check_backpedal_history(t_node *n)
{
	t_node	*prev;
	
	prev = n->previous;
	while (prev)
	{
		ft_putendl("prev: ");
		print_node(prev);
		if (prev->is_start)
			return (0);
		if (prev->backpedaled == 1)
			return (1);
		prev = prev->previous;
	}
	return (0);
}

void	backpedal_existing_path(t_node *n, t_queue *q, t_graph *g)
{
	t_node *backpedal;
	
	if (check_backpedal_history(n) == 1)
	{
		ft_putendl("Backpedal present in history");
		backpedal = find_augmenting_neighbour(n, g);
		if (backpedal)
		{
			visit_neighbour(n, backpedal, q, g);
			return;
		}
	}
	backpedal = find_backpedal_node(n, g);
	if (backpedal)
	{
		if (backpedal->first_node_in_path == 1)
		{
			ft_putendl("No backpedaling to first node in path");
			return;
		}
		n->backpedaled = 1;
		backpedal->visited = 1;
		g->history[backpedal->id] = n;
		n->next = backpedal;
		backpedal->previous = n;
		visit_neighbour(n, backpedal, q, g);
	}
}

int	augmenting_bfs(t_graph *g, t_node *start, t_node *end)
{
	t_node	*node;
	t_node	*neighbour;
	static	t_queue* q; 

	q = new_queue(g->nb_of_nodes + 1);
	g->history = (t_node **)malloc(sizeof(t_node *) * (g->nb_of_nodes + 1));
	set_start_node(q, g, start);
	while (!is_empty(q) && g->path_found != 1)
	{
		node = dequeue(q);
		ft_putendl("queue");
		print_node(node);
		if (node == end)
		{
			g->path_found = 1;
			break;
		}
		if (node->path_id > 0 && !node->is_start && !node->is_end && !g->backpedaled)
		{
			ft_putendl("backpedalling");
			backpedal_existing_path(node, q, g);
		}
		else
		{
			ft_putendl("finding aug path");
			neighbour = find_augmenting_neighbour(node, g);
			//print_node(node);
			while (neighbour)
			{
				visit_neighbour(node, neighbour, q, g);
				neighbour = find_augmenting_neighbour(node, g);
			}
		}
	}
	return (free_bfs(g, q));
}

int	find_augmenting_paths(t_graph *g)
{
	int ret;

	//print_nodes(g->nodes);
	//ft_putendl("nodes printed");
	ret = augmenting_bfs(g, g->start, g->end);
	//print_nodes(g->nodes);
	if (ret == 1)
	{
		backtrack(g, g->start, g->end);
		g->paths[g->nb_of_paths] = create_path(g, g->nb_of_paths);
	}
	the_great_switcharoo(g);
	return (0);
}