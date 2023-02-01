/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:06:39 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/01 11:39:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

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

void	print_paths(t_path **p, int length_mode)
{
	int	i;

	i = 0;
	while (p[i])
	{
		ft_putstr("path (");
		ft_putnbr(i);
		ft_putendl(")");
		if (length_mode)
		{
			ft_putstr("path len: ");
			ft_putnbr(p[i]->path_length);
		}
		else
			print_path(p[i]);
		ft_putendl("");
		i++;
	}
}

void	print_edges(t_edge **edges)
{
	int	i;

	i = 0;
	while (edges[i])
	{
		print_edge(edges[i]);
		ft_putendl("");
		i++;
	}
}

void	print_edge(t_edge *edge)
{
	ft_putstr(edge->start->name);
	ft_putstr("-");
	ft_putstr(edge->end->name);
}