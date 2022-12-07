/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/07 19:53:01 by kpolojar         ###   ########.fr       */
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
	i = bfs(graph, NULL, NULL, NULL);
	while (i == 1)
		i = bfs(graph, NULL, NULL, NULL);
	traverse_paths(graph);
	if (graph->nb_of_paths < 1)
		exit_program(-1, "invalid map (5)");
	print_farm(graph);
	//print_paths(graph->paths);
	place_all_ants(graph);
	free_graph(graph);
	//ft_putstr("lines: ");
	//ft_putnbr(graph->lines);
	//ft_putendl("");
	exit_program(0, NULL);
}
