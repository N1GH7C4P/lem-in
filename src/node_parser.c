/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:04:39 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/01 11:39:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

static int	handle_comments(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (1);
	else if (!ft_strcmp(line, "##end"))
		return (2);
	return (0);
}

static int validate_line(char *line)
{
	char	**words;
	int		i;

	words = ft_strsplit(line, ' ');
	i = 0;
	while (words[i])
		i++;
	ft_free_array(words);
	if (i != 3)
		exit_program(-1, "Wrong number of words in room desriptor.");
	return (1);
}

static int parse_coordinate(char *coord)
{
	int i;

	i = 0;
	if (coord[0] == '+' || coord[0] == '-')
		i++;
	while (coord[i])
	{
		if (!ft_isdigit(coord[i]))
			exit_program(-1, "Coordinate descriptor contains a non digit character.");
		i++;
	}
	return (ft_atoi(coord));
}

t_node	*handle_node(char *line, int ret, t_graph *g)
{
	char	**words;
	t_node	*new_node;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (line[0] == 'L' || line[0] == '#')
		exit_program(-1, "Illegal hashtag or L in node name.");
	validate_line(line);
	words = ft_strsplit(line, ' ');
	x = parse_coordinate(words[1]);
	y = parse_coordinate(words[2]);
	new_node = create_node(words[0], ret, x, y);
	if (ret == 1)
		g->start = new_node;
	else if (ret == 2)
		g->end = new_node;
	ft_free_array(words);
	g->nb_of_nodes = g->nb_of_nodes + 1;
	return (new_node);
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
