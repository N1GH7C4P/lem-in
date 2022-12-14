/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:06:39 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/14 17:51:45 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void	print_farm(t_graph *g)
{
	ft_putnbr(g->ants_available);
	ft_putendl("");
	print_nodes(g->nodes);
	print_edges(g->edges);
	ft_putendl("");
}

void	print_ant_movement(int ant_id, char *node_name, int first)
{
	if (!first)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(ant_id);
	ft_putchar('-');
	ft_putstr(node_name);
}

void	print_path(t_path *p)
{
	print_nodes(p->nodes);
}

void	print_paths(t_path **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		ft_putstr("path (");
		ft_putnbr(i);
		ft_putendl(")");
		print_path(p[i]);
		ft_putendl("");
		i++;
	}
}

void	exit_program(int ret, char *msg)
{
	if (msg && DESCRIPTIVE_MSGS == 1)
		ft_putendl_fd(msg, 2);
	else if(ret == -1)
		ft_putendl_fd("Error", 2);
	exit(ret);
}
