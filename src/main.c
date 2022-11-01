/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:00 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/01 23:46:11 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int main(void)
{
	static	t_graph	*graph;

	graph = create_graph();
	parser(graph);
	ft_putendl("Parsing complete!");
	bfs(graph);
	traverse_paths(graph);
	ft_putendl("printing path: ");
	print_path(graph->paths[1]);
}
