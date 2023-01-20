/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/20 17:43:42 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

int	main(void)
{
	t_graph	*graph;
	int		i;

	graph = create_graph();
	parser(graph);
	validate_graph(graph);
	//ft_putendl("valid");
	i = bfs(graph, 1);
	while (i == 1)
		i = bfs(graph, 1);
	traverse_paths(graph);
	if (graph->nb_of_paths < 1)
		exit_program(-1, "invalid map");
	print_farm(graph);
	//print_paths(graph->paths, 0);
	//ft_putstr("nb of paths: ");
	//ft_putnbr(graph->nb_of_paths);
	//ft_putendl("");
	place_all_ants(graph);
	free_graph(graph);
	//print_paths(graph->paths, 1);
	//print_adj_matrix(graph);
	exit_program(0, NULL);
}
