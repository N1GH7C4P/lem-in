/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:04:39 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/22 15:08:55 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

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

void	reset_ants(t_graph *g)
{
	int i;
	
	i = 0;
	while (i < g->ants_finished)
	{
		free_ant(g->ants[i]);
		i++;
	}
	g->ants_available += g->ants_finished;
	g->ants_finished = 0;
	g->ants_placed = 0;
}

void	place_all_ants(t_graph *g, int print)
{
	t_path	*p;
	t_ant	*a;

	g->nb_of_rounds = 0;
	while (g->ants_available > 0)
	{
		p = find_optimal_path(g);
		a = new_ant(g->ants_placed);
		place_ant_on_path(p, a, g);
	}
	while (g->ants_finished < g->ants_placed)
	{
		advance_ants(g, -1, 1, print);
		g->nb_of_rounds++;
		if (print)
			ft_putendl("");
	}
}

void	place_ant_on_path(t_path *p, t_ant *a, t_graph *g)
{
	p->ants++;
	a->path = p;
	g->ants[g->ants_placed] = a;
	g->ants_placed++;
	g->ants_available--;
}

void	advance_ants(t_graph *g, int i, int first_ant, int print)
{
	g->end->ant_present = 0;
	while (++i < g->ants_placed)
	{
		if (!g->ants[i]->path->nodes[g->ants[i]->progress]->is_end)
		{
			if (g->ants[i]->path->nodes[(g->ants[i]->progress) + 1]
				->ant_present == 0 || ((g->ants[i]->path->nodes[(g->ants[i]
								->progress) + 1]->is_end &&!(g->ants[i]
							->path->nodes[(g->ants[i]->progress)]->is_start))))
			{
				g->ants[i]->path->nodes[g->ants[i]->progress]->ant_present = 0;
				g->ants[i]->progress++;
				g->ants[i]->path->nodes[g->ants[i]->progress]->ant_present = 1;
				if (g->ants[i]->path->nodes[g->ants[i]->progress]->is_end)
					g->ants_finished++;
				if (print == 1)
					print_ant_movement(g->ants[i]->id,
						g->ants[i]->path->nodes[g->ants[i]
						->progress]->name, first_ant);
				first_ant = 0;
			}
		}
	}
}
