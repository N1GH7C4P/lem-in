/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:18:31 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/02 00:27:57 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

void	print_nodes(t_node **nodes, int v)
{
	int i;
	
	i = 0;
	while (nodes[i])
	{
		print_node(nodes[i++], v);
		ft_putendl("");
	}
}

void	print_node(t_node *node, int v)
{
	ft_putstr(node->name);
	if (v == 1)
	{
		ft_putstr(" visited: ");
		ft_putnbr(node->visited);
		ft_putstr(" id: ");
		ft_putnbr(node->id);
		ft_putstr(" path_id: ");
		ft_putnbr(node->path_id);
		if (node->is_start == 1)
			ft_putstr(" START");
		if (node->is_end == 1)
			ft_putstr(" END");
	}
}

t_node *create_node(char *name, int ret)
{
	t_node *new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->name = ft_strdup(name);
	new_node->is_end = 0;
	new_node->is_start = 0;
	if (ret == 1)
		new_node->is_start = 1;
	else if (ret == 2)
		new_node->is_end = 1;
	return (new_node);
}

t_node	*get_node_by_name(char *name, t_node **nodes)
{
	int i;

	i = 0;
	while (nodes[i])
	{
		if (ft_strequ(name, nodes[i]->name))
			return (nodes[i]);
		i++;
	}
	return (0);
}