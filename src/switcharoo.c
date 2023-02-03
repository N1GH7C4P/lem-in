/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switcharoo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:38:06 by marvin            #+#    #+#             */
/*   Updated: 2023/02/03 12:07:19 by marvin           ###   ########.fr       */
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
		if (DEBUGGING > 0)
			print_node(p->nodes[i]);
		if (e->start == p->nodes[i] || e->end == p->nodes[i])
			break;
		i++;
	}
	if (DEBUGGING > 0)
		ft_putendl("counted befre");
	return (i + 1);
}

int		count_nodes_after_crossover(t_path *p, t_edge *e)
{
	int i;

	i = 0;
	while (p->nodes[i])
	{
		if (DEBUGGING > 0)
			print_node(p->nodes[i]);
		if (e->start == p->nodes[i] || e->end == p->nodes[i])
			break;
		i++;
	}
	if (DEBUGGING > 0)
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

static void	reset_combined_path_ids(t_path *p, t_path *new)
{
		int i;

		i = 0;
		while (p->nodes[i])
		{
			if (p->nodes[i]->path_id != new->id)
				p->nodes[i]->path_id = 0;
			i++;
		}
}
// returns path id
t_path *combine_paths(t_path *src1, t_path *src2, t_edge *e, t_graph *g)
{
	int i;
	int j;
	int new_path_id;
	t_path	*dest;

	new_path_id = find_first_free_path_id(g);
	dest =  new_path(count_nodes_after_crossover(src1, e) + count_nodes_before_crossover(src2, e), new_path_id);
	dest->id = new_path_id;
	i = 0;
	while (src1->nodes[i] != e->end && src1->nodes[i] != e->start)
	{
		dest->nodes[i] = src1->nodes[i];
		dest->nodes[i]->path_id = new_path_id;
		dest->nodes[i]->old_path_id = 0;
		if ((dest->nodes[i] == e->end || dest->nodes[i] == e->start) && (dest->nodes[i]->next == e->end || dest->nodes[i]->next == e->start))
				break;
		i++;
	}
	j = find_node_id_in_path(src1->nodes[i], src2);
	while (src2->nodes[j])
	{
		dest->nodes[i] = src2->nodes[j];
		dest->nodes[i]->path_id = new_path_id;
		dest->nodes[i]->old_path_id = 0;
		i++;
		j++;
	}
	if (DEBUGGING > 0)
	{
		ft_putendl("Combined path: ");
		print_path(dest);
		ft_putendl("Path printed");
	}
	return (dest);
}

void	fix_paths(t_path *p1, t_path *p2, t_edge *e, t_graph *g)
{
	t_path	*new;

	new = combine_paths(p1, p2, e, g);
	reset_combined_path_ids(p1, new);
	free_path(p1, g);
	reset_combined_path_ids(p2, new);
	free_path(p2, g);
	if (DEBUGGING > 0)
	{
		ft_putstr("saving path: ");
		ft_putnbr(new->id);
		ft_putendl("");
	}
	g->paths[new->id - 1] = new;
	g->path_id_availability[new->id] = 1;
	g->nb_of_paths--;
}

void	the_great_switcharoo(t_graph *g)
{
	t_edge	*double_used;
	t_path	*p1;
	t_path	*p2;

	double_used = find_double_used_edge(g);
	if (DEBUGGING > 0)
	{
		ft_putendl("printing double use edge nodes: ");
		print_node(double_used->start);
		print_node(double_used->end);
	}
	p1 = g->paths[double_used->start->old_path_id - 1];
	p2 = g->paths[double_used->end->path_id - 1];
	fix_paths(p1, p2, double_used, g);
}