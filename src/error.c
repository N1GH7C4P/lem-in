/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:19:45 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/14 17:47:51 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

int	validate_graph(t_graph *g)
{
	if (g->nb_of_nodes < 2)
		exit_program(-1, "invalid map");
	if (g->nb_of_edges < 1)
		exit_program(-1, "invalid map");
	if (!g->start || !g->end)
		exit_program(-1, "invalid map");
	if (!g->ants)
		exit_program(-1, "invalid map");
	return (0);
}
