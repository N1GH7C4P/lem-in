/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:59:11 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/01 11:39:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

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

void	exit_program(int ret, char *msg)
{
	if (msg && DESCRIPTIVE_MSGS == 1)
		ft_putendl_fd(msg, 2);
	else if(ret == -1)
		ft_putendl_fd("Error", 2);
	exit(ret);
}
