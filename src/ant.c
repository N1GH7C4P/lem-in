/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:04:39 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/06 15:30:10 by kpolojar         ###   ########.fr       */
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
		//advance_ants(g);
		place_ant_on_path(p, a, g);
	}
	while (g->ants_finished < g->ants_placed)
	{
		/*
		ft_putstr("Ants finished: ");
		ft_putnbr(g->ants_finished);
		ft_putstr("/");
		ft_putnbr(g->ants_placed);
		ft_putendl("");
		*/
		advance_ants(g);
	}
}

void	place_ant_on_path(t_path *p, t_ant *a, t_graph *g)
{
	p->ants++;
	a->path = p;
	g->ants[g->ants_placed] = a;
	/*
		ft_putchar('L');
		ft_putnbr(a->id);
		ft_putchar('-');
		ft_putendl(g->start->name);
	*/
	g->ants_placed++;
	g->ants_available--;
}

void	advance_ants(t_graph *g)
{
	int	i;

	i = 0;
	while (i < g->ants_placed)
	{
		if (i == 0)
			g->end->ant_present = 0;
		if (!g->ants[i]->path->nodes[g->ants[i]->progress]->is_end)
		{
			if (g->ants[i]->path->nodes[(g->ants[i]->progress) + 1]->ant_present == 0)
			{
				g->ants[i]->path->nodes[g->ants[i]->progress]->ant_present = 0;
				g->ants[i]->progress++;
				g->ants[i]->path->nodes[g->ants[i]->progress]->ant_present = 1;
				if (g->ants[i]->path->nodes[g->ants[i]->progress]->is_end)
					g->ants_finished++;
				ft_putchar('L');
				ft_putnbr(g->ants[i]->id);
				ft_putchar('-');
				ft_putstr(g->ants[i]->path->nodes[g->ants[i]->progress]->name);
				ft_putchar(' ');
			}
			/*
			else
			{
				ft_putendl("node blocked: ");
				print_node(g->ants[i]->path->nodes[(g->ants[i]->progress) + 1], 0);
				ft_putendl("for ant: ");
				ft_putnbr(i);
				ft_putendl("");
			}
			*/
		}
		i++;
	}
	ft_putendl("");
}
