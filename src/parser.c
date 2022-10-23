/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:27:40 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/24 00:01:28 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int parser(int argc, char** argv, static int vertices[N + 1])
{
	int		i;
	int		j;
	int		nodes;
	char	*line;

	if (argc != 2)
		return ;
	char **lines = ft_split(argv, "\n");
	while(lines[i])
	{
		if (!ft_strcmp("##start"))
		{
			line = lines[++i];
			while (line)
		}
	}
}