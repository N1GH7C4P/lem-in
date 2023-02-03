/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:06:39 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/03 11:22:33 by marvin           ###   ########.fr       */
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

void	print_paths(t_path **p, int length_mode, t_graph *g)
{
	int	i;


	print_path_id_availability(g);
	i = 1;
	while (i < MAX_PATHS)
	{
		if (g->path_id_availability[i] == 1)
		{
			ft_putstr("path (");
			ft_putnbr(p[i -1]->id);
			ft_putendl(")");
			if (length_mode)
			{
				ft_putstr("path len: ");
				ft_putnbr(p[i - 1]->path_length);
				ft_putendl("");
			}
			print_path(p[i - 1]);
			ft_putendl("");
		}
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