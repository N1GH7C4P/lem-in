/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:19:45 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/01 11:38:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int	validate_graph(t_graph *g)
{
	if (g->nb_of_nodes < 2)
		exit_program(-1, "invalid map (1)");
	if (g->nb_of_edges < 1)
		exit_program(-1, "invalid map (2)");
	if (!g->start || !g->end)
		exit_program(-1, "invalid map (3)");
	if (!g->ants)
		exit_program(-1, "invalid map (4)");
	return (0);
}
