/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/02 18:38:36 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int main(void)
{
	static	t_graph	*graph;
	int		i;

	graph = create_graph();
	parser(graph);
	i = bfs(graph);
	while (i == 1)
		i = bfs(graph);
	traverse_paths(graph);
	i = 1;
	place_all_ants(graph);
	while (i <= graph->nb_of_paths)
	{
		print_path(graph->paths[i]);
		i++;
	}
	return (0);
}
