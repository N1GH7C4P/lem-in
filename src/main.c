/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/01 11:39:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int	main(void)
{
	t_graph	*graph;
	int		i;

	graph = create_graph();
	parser(graph);
	validate_graph(graph);
	//ft_putendl("valid");
	i = bfs(graph, 0, graph->start, graph->end);
	while (i == 1)
		i = bfs(graph, 0, graph->start, graph->end);
	traverse_paths(graph);
	if (graph->nb_of_paths < 1)
		exit_program(-1, "invalid map");
	place_all_ants(graph, 0);
	save_paths_data(graph);
	reset_ants(graph);
	reset_visit_status(graph);
	graph->path_found = 0;
	//print_nodes(graph->nodes);
	find_augmenting_paths(graph);
	traverse_paths(graph);
	//ft_putendl("nb of rounds: ");
	//ft_putnbr(graph->nb_of_rounds);
	print_farm(graph);
	//print_paths(graph->paths, 0);
	//ft_putstr("nb of paths: ");
	//ft_putnbr(graph->nb_of_paths);
	//ft_putendl("");
	place_all_ants(graph, 1);
	free_graph(graph);
	//print_paths(graph->paths, 1);
	exit_program(0, NULL);
}
