/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:59:36 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/18 18:20:15 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static t_edge	*handle_edge(char *line, t_node **nodes, t_graph *g)
{
	char	**words;
	t_edge	*new_edge;
	t_node	*start;
	t_node	*end;

	words = ft_strsplit(line, '-');
	start = get_node_by_name(words[0], nodes);
	end = get_node_by_name(words[1], nodes);
	new_edge = create_edge(start, end, g);
	ft_free_array(words);
	return (new_edge);
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
			g->edges[edges_processed++] = handle_edge(lines[i], g->nodes, g);
		i++;
	}
	g->edges[edges_processed] = NULL;
	g->nb_of_edges = edges_processed;
}
