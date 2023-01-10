/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:59:11 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/14 17:48:17 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

int	count_nodes_with_path_id(t_graph *g, int id)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < g->nb_of_nodes && g->nodes[i])
	{
		if (g->nodes[i]->path_id == id
			|| g->nodes[i]->is_start || g->nodes[i]->is_end)
			count++;
		i++;
	}
	return (count);
}

// -1: Ants, 0: Comment, 1: Edge, 2: Node
int	identify_line(char *line, int line_nb)
{
	if (line_nb == 0)
		return (-1);
	if (line[0] == '#')
		return (0);
	else if (ft_strchr(line, '-'))
		return (1);
	else
		return (2);
}

// -1: Ants, 0: Comment, 1: Edge, 2: Node
int	count_lines_with_id(char **lines, int id)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (lines[i])
	{
		if (identify_line(lines[i], i) == id)
			count++;
		i++;
	}
	return (count);
}

// Counts occurance of char c in char *l
int	count_c(char *l, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (l[i])
	{
		if (l[i] == c)
			count++;
		i++;
	}
	return (count);
}

// Checks if two nodes form the smallest possible path from start to end.
int	check_start_end(t_node *a, t_node *b, t_graph *g)
{
	if ((a->is_start || a->is_end) && (b->is_end || b->is_start))
	{
		if (g->smallest_path == 1)
			return (1);
		else
			g->smallest_path = 1;
	}
	return (0);
}
