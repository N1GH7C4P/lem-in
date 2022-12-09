/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:18:31 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/09 18:25:01 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

void	print_nodes(t_node **nodes)
{
	int	i;

	i = 0;
	while (nodes[i])
		print_node(nodes[i++]);
}

void	print_node(t_node *node)
{
	if (node->is_start == 1)
		ft_putendl("##start");
	if (node->is_end == 1)
		ft_putendl("##end");
	ft_putstr(node->name);
	ft_putstr(" ");
	if (node->x != INT_MIN)
		ft_putnbr(node->x);
	if (node->y != INT_MIN)
	{
		ft_putstr(" ");
		ft_putnbr(node->y);
	}
	ft_putendl("");
}

void	free_node(t_node *n)
{
	free(n->name);
	free(n);
}

t_node	*create_node(char *name, int ret, int x, int y)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->name = ft_strdup(name);
	new_node->is_end = 0;
	new_node->is_start = 0;
	new_node->visited = 0;
	new_node->path_id = 0;
	new_node->x = x;
	new_node->y = y;
	new_node->ant_present = 0;
	if (ret == 1)
		new_node->is_start = 1;
	else if (ret == 2)
		new_node->is_end = 1;
	return (new_node);
}

t_node	*get_node_by_name(char *name, t_node **nodes)
{
	int	i;

	i = 0;
	while (nodes[i])
	{
		if (ft_strequ(name, nodes[i]->name))
			return (nodes[i]);
		i++;
	}
	return (0);
}
