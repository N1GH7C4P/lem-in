/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:27:40 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/07 19:16:35 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

char	**read_from_stdout(void)
{
	int		ret;
	int		i;
	char	*line;
	char	**lines;

	i = 0;
	line = NULL;
	lines = (char **)malloc(sizeof(char *) * (MAX_LINES + 1));
	ret = ft_get_next_line(0, &line);
	while (ret)
	{
		lines[i] = ft_strdup(line);
		free(line);
		ret = ft_get_next_line(0, &line);
		i++;
		if (i > MAX_LINES)
			exit_program(-1, "invalid map (1)");
	}
	if (i == 0)
		exit_program(-1, "invalid map (2)");
	free(line);
	lines[i] = NULL;
	return (lines);
}

int	parser(t_graph *g)
{
	char	**lines;

	lines = read_from_stdout();
	g->ants_available = ft_atoi(lines[0]);
	g->ants = (t_ant **)malloc(sizeof(t_ant *) * (g->ants_available + 1));
	g->ants[g->ants_available] = NULL;
	handle_nodes(lines, g);
	handle_edges(lines, g);
	ft_free_array(lines);
	return (0);
}
