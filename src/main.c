/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/03 22:21:41 by kpolojar         ###   ########.fr       */
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
	validate_graph(graph);
	i = bfs(graph);
	while (i == 1)
		i = bfs(graph);
	traverse_paths(graph);
	if (graph->nb_of_paths < 1)
		exit_program(-1, "invalid map");
	place_all_ants(graph);
	free_graph(graph);
	exit_program(0, NULL);
}
