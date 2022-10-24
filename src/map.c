/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:45:44 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/24 15:12:24 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_map	*new_map(void)
{	
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	return (map);
}

void	set_ants(int nb, t_map *map)
{
	map->ants = nb;
}

void	set_start(int nb, t_map *map)
{
	map->start = nb;
}

void	set_end(int nb, t_map *map)
{
	map->end = nb;
}