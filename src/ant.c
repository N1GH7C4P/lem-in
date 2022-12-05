/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:04:39 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/04 20:09:56 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_ant	*new_ant(int id)
{
	t_ant	*a;

	a = (t_ant *)malloc(sizeof(t_ant));
	a->id = id;
	a->progress = 0;
	return (a);
}

void	free_ant(t_ant *a)
{
	free(a);
}

void	place_all_ants(t_graph *g)
{
	t_path	*p;
	t_ant	*a;

	while (g->ants_available > 0)
	{
		p = find_optimal_path(g);
		a = new_ant(g->ants_placed);
		advance_ants(g);
		place_ant_on_path(p, a, g);
	}
	while (g->ants_finished < g->ants_placed)
	{
		advance_ants(g);
		ft_putendl("");
	}
}

void	place_ant_on_path(t_path *p, t_ant *a, t_graph *g)
{
	p->ants++;
	a->path = p;
	g->ants[g->ants_placed] = a;
	ft_putchar('L');
	ft_putnbr(a->id);
	ft_putchar('-');
	ft_putendl(g->start->name);
	g->ants_placed++;
	g->ants_available--;
}

void	advance_ants(t_graph *g)
{
	int	i;

	i = 0;
	while (i < g->ants_placed)
	{
		if (g->ants[i]->progress < g->ants[i]->path->path_length - 1)
		{
			if (g->ants[i]->progress == g->ants[i]->path->path_length - 2)
				g->ants_finished++;
			g->ants[i]->progress++;
			ft_putchar('L');
			ft_putnbr(g->ants[i]->id);
			ft_putchar('-');
			ft_putstr(g->ants[i]->path->nodes[g->ants[i]->progress]->name);
			ft_putchar(' ');
		}
		i++;
	}
}
