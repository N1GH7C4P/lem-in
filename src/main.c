/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/02 00:34:38 by kpolojar         ###   ########.fr       */
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
	print_path(graph->paths[1]);
}
