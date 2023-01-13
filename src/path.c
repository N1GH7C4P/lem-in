/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:24:57 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/13 14:05:45 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void	free_path(t_path *p)
{
	free(p->nodes);
	free(p);
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
				return (g->edges[i]->end);
			}
		}
		else if (g->edges[i]->end->id == node->id)
		{
			if ((g->edges[i]->start->path_id == id && g->edges[i]->start
					->visited != 1) || g->edges[i]->start->is_end)
			{
				g->edges[i]->start->visited = 1;
				return (g->edges[i]->start);
			}
		}
	}
	return (NULL);
}

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

t_path	*create_path(t_graph *g, int path_id)
{
	t_node	*node;
	t_path	*p;
	int		i;

	p = new_path(count_nodes_with_path_id(g, path_id));
	reset_visit_status(g);
	node = g->start;
	node->visited = 1;
	p->nodes[0] = node;
	i = 1;
	node = find_next_node_in_path(node, g, path_id);
	while (node)
	{
		p->nodes[i] = node;
		if (node->is_end)
			return (p);
		node = find_next_node_in_path(node, g, path_id);
		i++;
	}
	free_path(p);
	return (NULL);
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
		i++;
	}
}
