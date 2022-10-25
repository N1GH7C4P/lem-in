/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:58:27 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/25 16:09:39 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_graph	*create_graph(void)
{
	t_graph	*new_graph;

	new_graph = (t_graph *)malloc(sizeof(t_graph));

	return (new_graph);
}