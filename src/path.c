/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:24:57 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/01 11:39:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_path	*new_path(int len)
{
	t_path	*p;

	p = (t_path *)malloc(sizeof(t_path));
	p->path_length = len;
	p->nodes = (t_node **)malloc(sizeof(t_node *) * (len + 1));
	p->nodes[len] = NULL;
	p->ants = 0;
	return (p);
}

t_path *copy_path(t_path *p)
{
	t_path *new_p;
	int		i;

	new_p = new_path(p->path_length);
	i = 0;
	while(i < p->path_length)
	{
		new_p->nodes[i] = p->nodes[i];
		i++;
	}
	new_p->nodes[i] = NULL;
	return (new_p);
}

void	free_path(t_path *p)
{
	free(p->nodes);
	free(p);
}

void	free_all_paths(t_path **paths, int nb_of_paths)
{
	int i;

	i = 0;
	while (i < nb_of_paths)
	{
		free_path(paths[i]);
		i++;
	}
	free(paths);
}

void	save_paths_data(t_graph *g)
{
	int i;

	g->best_paths = (t_path **)malloc(sizeof(t_path *) * g->nb_of_paths + 1);
	i = 0;
	while (i < g->nb_of_paths)
	{
		g->best_paths[i] = copy_path(g->paths[i]);
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

t_path	*create_path(t_graph *g, int path_id)
{
	t_node	*next;
	t_path	*p;
	int		i;

	//ft_putstr("path_id: ");
	//ft_putnbr(path_id);
	//ft_putendl("");
	p = new_path(count_nodes_with_path_id(g, path_id));
	reset_visit_status(g);
	g->start->visited = 1;
	p->nodes[0] = g->start;
	i = 1;
	next = find_next_node_in_path(p->nodes[0], g, path_id);
	ft_putendl("creating path");
	while (next)
	{
		print_node(next);
		p->nodes[i] = next;
		p->nodes[i - 1]->next = next;
		if (next->is_end)
			return (p);
		next = find_next_node_in_path(next, g, path_id);
		i++;
	}
	free_path(p);
	return (NULL);
}

static t_path *create_smallest_path(t_graph *g)
{
	t_path *smallest;
	
	smallest = new_path(2);
	smallest->nodes[0] = g->start;
	smallest->nodes[1] = g->end;
	return (smallest);
}

void	traverse_paths(t_graph *g)
{
	int	i;

	g->paths = (t_path **)malloc(sizeof(t_path *) * (g->nb_of_paths + 1));
	g->paths[g->nb_of_paths] = NULL;
	i = 0;
	while (i < g->nb_of_paths)
	{
		g->paths[i] = create_path(g, i + 1);
		g->paths[i]->nodes[1]->first_node_in_path = 1;
		i++;
	}
	if (g->smallest_path == 1)
	{
		g->paths[g->nb_of_paths] = create_smallest_path(g);
		g->nb_of_paths++;
	}
}
