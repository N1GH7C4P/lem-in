/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/03 11:50:44 by marvin           ###   ########.fr       */
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
	if (DEBUGGING > 0)
		ft_putendl("exited bfs");
	if (graph->nb_of_paths < 1)
		exit_program(-1, "invalid map (no paths)");
	if (DEBUGGING > 0)
		ft_putendl("placing ants");
	place_all_ants(graph, 0);
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
	//print_nodes(graph->nodes);
	if (DEBUGGING > 0)
		ft_putendl("Finding augmenting paths.");
	find_augmenting_paths(graph);
	//ft_putendl("freeing paths");
	//free_all_paths(graph->paths, graph->nb_of_paths);
	//ft_putendl("paths freed.");
	//traverse_paths(graph);
	the_great_switcharoo(graph);
	if (DEBUGGING > 0)
		ft_putendl("new bfs");
	reset_visit_status(graph);
	i = bfs(graph, 0, graph->start, graph->end);
	while (i == 1)
		i = bfs(graph, 0, graph->start, graph->end);
	//ft_putendl("nb of rounds: ");
	//ft_putnbr(graph->nb_of_rounds);
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
	//print_paths(graph->paths, 1);
	exit_program(0, NULL);
}
