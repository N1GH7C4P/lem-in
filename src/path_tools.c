/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:07:42 by marvin            #+#    #+#             */
/*   Updated: 2023/02/02 13:07:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int find_node_id_in_path(t_node *n, t_path *p)
{
	int i;

	i = 0;
	while (i < p->path_length)
	{
		if(p->nodes[i] == n)
			return (i);
		i++;
	}
	return -1;
}

int find_first_free_path_id(t_graph *g)
{
	int i;

	i = 1;
	while (g->path_id_availability[i] && i < MAX_PATHS)
	{
		i++;
	}
	return (i);
}

t_path	*create_path(t_graph *g, int path_id)
{
	t_node	*next;
	t_path	*p;
	int		i;

	p = new_path(count_nodes_with_path_id(g, path_id), path_id);
	reset_visit_status(g);
	g->start->visited = 1;
	p->nodes[0] = g->start;
	i = 1;
	g->nb_of_paths = g->nb_of_paths + 1;
	next = find_next_node_in_path(p->nodes[0], g, path_id);
	if (DEBUGGING == 2 || DEBUGGING == 1)
	{
		if (DEBUGGING > 0)
		{
			ft_putstr("creating path (");
			ft_putnbr(path_id);
			ft_putendl(")");
		}
	}
	while (next)
	{
		if (DEBUGGING > 0)
			print_node(next);
		p->nodes[i] = next;
		p->nodes[i - 1]->next = next;
		if (next->is_end == 1)
		{
			if (DEBUGGING > 0)
				ft_putendl("path finished");
			g->path_id_availability[path_id] = 1;
			p->nodes[1]->first_node_in_path = 1;
			return (p);
		}
		next = find_next_node_in_path(next, g, path_id);
		i++;
	}
	free_path(p, g);
	return (NULL);
}

void	save_paths_data(t_graph *g)
{
	int i;

	i = 0;
	free(g->best_paths);
	free(g->best_path_id_availability);
	
	g->best_paths = (t_path **)malloc(sizeof(t_path *) * MAX_PATHS + 1);
	g->best_path_id_availability = (char *)malloc(MAX_PATHS + 1);
	while (i < MAX_PATHS)
	{
		if (g->path_id_availability[i] == 1)
		{
			g->best_path_id_availability[i] = 1;
			g->best_paths[i - 1] = copy_path(g->paths[i - 1]);
		}
		i++;
	}
	g->least_nb_of_rounds = g->nb_of_rounds;
	g->nb_of_rounds = 0;
	g->best_paths[i] = NULL;
}

t_node	*find_next_node_in_path(t_node *node, t_graph *g, int id)
{
	int	i;

	i = -1;
	while (g->edges[++i])
	{
		if (g->edges[i]->start->id == node->id)
		{
			if ((g->edges[i]->end->path_id == id && g->edges[i]->end
					->visited != 1) || g->edges[i]->end->is_end)
			{
				g->edges[i]->end->visited = 1;
				g->edges[i]->used_forwards = 1;
				return (g->edges[i]->end);
			}
		}
		else if (g->edges[i]->end->id == node->id)
		{
			if ((g->edges[i]->start->path_id == id && g->edges[i]->start
					->visited != 1) || g->edges[i]->start->is_end)
			{
				g->edges[i]->start->visited = 1;
				g->edges[i]->used_backwards = 1;
				return (g->edges[i]->start);
			}
		}
	}
	return (NULL);
}
