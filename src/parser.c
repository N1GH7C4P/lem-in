/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:27:40 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/24 15:15:49 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int handle_link(char *line, t_map *map)
{

}

int handle_vertex(char *line, t_map *map, int ret)
{
	t_node	new_node;
	int		x;
	int		y;
	char	*name;

	new_node = create_node(x, y, name);
}

int handle_input(char *line, t_map *map, int ret)
{
	int nb;
	int digits;

	nb = ft_atoi(line);
	digits = ft_countdigits(nb, 10);
	if (ft_strchr(line, '-'))
		handle_link(line, map);
	else
		handle_vertex(line, map, ret);
}

int handle_comments(char *line, t_map *map)
{
	if (!ft_strcmp(line, "##start"))
		return (1);
	else if (!ft_strcmp(line, "##end"))
		return (2);
	return (0);
}

int parser(int argc, char** argv, t_map *map, int adj[N + 1][N + 1])
{
	int		i;
	int		ret;
	char	*line;

	if (argc != 2)
		return ;
	char **lines = ft_split(argv, "\n");
	i = 0;
	set_ants(ft_atoi(lines[i++]), map);
	while (lines[i])
	{
		if (lines[i][0] == '#')
			ret = handle_comments(lines[i], map);
		else if (is_digit(lines[i][0]))
			handle_input(lines[i], map, ret);
		i++;
	}
	ft_free_array(lines);
}