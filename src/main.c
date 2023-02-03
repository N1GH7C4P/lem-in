/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/03 14:08:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int compare_results(t_graph *graph)
{
	if (graph->nb_of_rounds < graph->least_nb_of_rounds)
	{
		if (DEBUGGING > 0)
			ft_putendl("saving paths");
		save_paths_data(graph);
		if (DEBUGGING > 0)
			ft_putendl("resetting ants");
		reset_ants(graph);
		if (DEBUGGING > 0)
			ft_putendl("resetting visit status");
		reset_visit_status(graph);
		if (DEBUGGING > 0)
			ft_putendl("resetting path found");
		graph->path_found = 0;
	}
	return (0);
}

int	path_finding_core_loop(t_graph *graph)
{
	int ret;

	ret = bfs(graph, graph->start, graph->end);
	while (ret == 1)
	{
		if (DEBUGGING > 0)
			ft_putendl("new bfs");
		while (ret == 1)
			ret = bfs(graph, graph->start, graph->end);
		if (DEBUGGING > 0)
			ft_putendl("exited bfs");
		if (graph->nb_of_paths < 1)
			exit_program(-1, "invalid map (no paths)");
		if (DEBUGGING > 0)
			ft_putendl("placing ants");
		place_all_ants(graph, 0);
		compare_results(graph);
		if (DEBUGGING > 0)
			ft_putendl("Finding augmenting paths.");
		ret = find_augmenting_paths(graph);
		if (ret == 1)
			the_great_switcharoo(graph);
		if (DEBUGGING > 0)
			ft_putendl("Resetting visit status.");
		reset_visit_status(graph);
	}
	return (0);
}

int	main(void)
{
	t_graph	*graph;

	graph = create_graph();
	parser(graph);
	validate_graph(graph);
	path_finding_core_loop(graph);
	if (DEBUGGING > 0)
		ft_putendl("printing farm");
	print_farm(graph);
	if (DEBUGGING > 0)
	{
		print_paths(graph->paths, 0, graph);
		ft_putstr("nb of paths: ");
		ft_putnbr(graph->nb_of_paths);
		ft_putendl("");
	}
	place_all_ants(graph, 1);
	free_graph(graph);
	exit_program(0, NULL);
}
