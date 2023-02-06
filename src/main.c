/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/06 13:58:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int compare_results(t_graph *graph)
{
	if (DEBUGGING > 0)
	{
		ft_putstr("old nb of rounds: ");
		ft_putnbr(graph->least_nb_of_rounds);
		ft_putstr(" new nb of rounds: ");
		ft_putnbr(graph->nb_of_rounds);
		ft_putendl("");
	}
	if (graph->nb_of_rounds < graph->least_nb_of_rounds)
	{
		if (DEBUGGING > 0)
			ft_putendl("saving new paths");
		save_paths_data(graph);
		if (DEBUGGING > 0)
			ft_putendl("resetting visit status");
		reset_visit_status(graph);
		if (DEBUGGING > 0)
			ft_putendl("resetting path found");
		graph->path_found = 0;
		if (DEBUGGING > 0)
		{
			ft_putendl("printing saved paths");
			print_paths(graph->best_paths, 1, graph->best_path_id_availability, graph->nb_of_best_paths);
		}
	}
	else
		if (DEBUGGING > 0)
			ft_putendl("keeping old paths");
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
		reset_ants(graph);
		place_all_ants(graph, 0, 0);
		if (DEBUGGING > 0)
			ft_putendl("resetting ants");
		reset_ants(graph);
		if (DEBUGGING > 0)
			ft_putendl("comparing results");
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
	if (DEBUGGING == 3)
	{
		ft_putendl("printing edges");
		print_edges(graph->edges);
	}
	validate_graph(graph);
	path_finding_core_loop(graph);
	if (DEBUGGING > 0)
		ft_putendl("printing farm");
	print_farm(graph);
	if (DEBUGGING > 0)
	{
		print_paths(graph->paths, 0, graph->path_id_availability, graph->nb_of_paths);
		ft_putstr("nb of paths: ");
		ft_putnbr(graph->nb_of_paths);
		ft_putendl("");
	}
	if (DEBUGGING > 0)
		ft_putendl("Placing all ants and printing them");
	place_all_ants(graph, 1, 1);
	free_graph(graph);
	exit_program(0, NULL);
}
