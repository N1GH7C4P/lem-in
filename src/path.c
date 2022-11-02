/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:24:57 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/02 17:35:56 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

void	place_ant_on_path(t_path *p)
{
	p->ants++;
}

int		count_nodes_with_path_id(t_graph *g, int path_id)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < g->nb_of_nodes && g->nodes[i])
	{
		if (g->nodes[i]->path_id == path_id || g->nodes[i]->is_start || g->nodes[i]->is_end)
			count++;
		i++;
	}
	return (count);
}

t_node	*find_next_node_in_path(t_node *node, t_graph *graph, int path_id)
{
	int i;

	i = 0;
	while (graph->edges[i])
	{
		if (graph->edges[i]->start->id == node->id)
		{
			if ((graph->edges[i]->end->path_id == path_id && graph->edges[i]->end->visited != 1) || graph->edges[i]->end->is_end)
			{
				graph->edges[i]->end->visited = 1;
				return (graph->edges[i]->end);
			}
		}
		else if (graph->edges[i]->end->id == node->id)
		{
			if ((graph->edges[i]->start->path_id == path_id && graph->edges[i]->start->visited != 1) || graph->edges[i]->start->is_end)
			{
				graph->edges[i]->start->visited = 1;
				return (graph->edges[i]->start);
			}
		}
		i++;
	}
	return (NULL);
}


void	delete_path(t_path *p)
{
	free(p->nodes);
	free(p);
}

t_path	*new_path(int path_length)
{
	t_path	*p;

	p = (t_path *)malloc(sizeof(t_path));
	p->path_length = path_length;
	p->nodes = (t_node **)malloc(sizeof(t_node *) * (path_length + 1));
	p->nodes[path_length] = NULL;
	return (p);
}

//Basic DFS
t_path	*create_path(t_graph *g, int path_id)
{
	t_node	*node;
	t_path	*p;
	int 	i;

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
	delete_path(p);
	return (NULL);
}

void traverse_paths(t_graph *g)
{
	int i;

	g->paths = (t_path **)malloc(sizeof(t_path *) * (g->nb_of_paths + 1));
	i = 1;
	while (i <= g->nb_of_paths)
	{
		g->paths[i] = create_path(g, i);
		i++;
	}
}

void print_path(t_path *p)
{
	int i;

	ft_putstr("path length: ");
	ft_putnbr(p->path_length);
	ft_putendl("");
	ft_putendl("nodes: ");
	i = 0;
	while(p->nodes[i])
	{
		print_node(p->nodes[i], 1);
		ft_putendl("");
		i++;
	}
	ft_putstr("Ants: ");
	ft_putnbr(p->ants);
	ft_putendl("");
}
