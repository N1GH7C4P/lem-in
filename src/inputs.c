/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:59:36 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/04 20:06:49 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_edge	*handle_edge(char *line, t_node **nodes)
{
	char	**words;
	t_edge	*new_edge;
	t_node	*start;
	t_node	*end;

	words = ft_strsplit(line, '-');
	start = get_node_by_name(words[0], nodes);
	end = get_node_by_name(words[1], nodes);
	new_edge = create_edge(start, end);
	ft_free_array(words);
	return (new_edge);
}

t_node	*handle_node(char *line, int ret, t_graph *g)
{
	char	**words;
	t_node	*new_node;

	words = ft_strsplit(line, ' ');
	new_node = create_node(words[0], ret);
	if (ret == 1)
		g->start = new_node;
	else if (ret == 2)
		g->end = new_node;
	ft_free_array(words);
	g->nb_of_nodes = g->nb_of_nodes + 1;
	return (new_node);
}

int	handle_comments(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (1);
	else if (!ft_strcmp(line, "##end"))
		return (2);
	return (0);
}

void	handle_edges(char **lines, t_graph *g)
{
	int		i;
	int		edges_processed;

	g->edges = (t_edge **)malloc
		(sizeof(t_edge *) * (count_lines_with_id(lines, 1) + 1));
	edges_processed = 0;
	i = 1;
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 1)
			g->edges[edges_processed++] = handle_edge(lines[i], g->nodes);
		i++;
	}
	g->edges[edges_processed] = NULL;
	g->nb_of_edges = edges_processed;
}

void	handle_nodes(char **lines, t_graph *g)
{
	int		i;
	int		ret;
	int		nodes_processed;
	int		nb_of_nodes;

	ret = 0;
	nodes_processed = 0;
	i = 0;
	nb_of_nodes = count_lines_with_id(lines, 2);
	g->nodes = (t_node **)malloc(sizeof(t_node *) * (nb_of_nodes + 1));
	g->nodes[nb_of_nodes] = NULL;
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 0)
			ret = handle_comments(lines[i]);
		else if (identify_line(lines[i], i) == 2)
		{
			g->nodes[nodes_processed] = handle_node(lines[i], ret, g);
			g->nodes[nodes_processed]->id = nodes_processed;
			nodes_processed++;
			ret = 0;
		}
		i++;
	}
	g->nodes[nodes_processed] = NULL;
}
