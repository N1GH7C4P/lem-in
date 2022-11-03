/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:27:40 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/03 21:53:43 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_edge	*handle_edge(char *line, t_node **nodes)
{
	char	**words;
	t_edge	*new_edge;
	t_node	*start;
	t_node	*end;

	words = ft_strsplit(line, '-');
	start = get_node_by_name(words[0], nodes);
	end = get_node_by_name(words[1], nodes);
	new_edge = create_edge(start, end);
	ft_free_array(words);
	return (new_edge);
}

t_node	*handle_node(char *line, int ret, t_graph *g)
{
	char	**words;
	t_node	*new_node;
	
	words = ft_strsplit(line, ' ');
	new_node = create_node(words[0], ret);
	if (ret == 1)
		g->start = new_node;
	else if (ret == 2)
		g->end = new_node;
	ft_free_array(words);
	g->nb_of_nodes = g->nb_of_nodes + 1;
	return (new_node);
}

int handle_comments(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (1);
	else if (!ft_strcmp(line, "##end"))
		return (2);
	return (0);
}

// -1: Ants, 0: Comment, 1: Edge, 2: Node
int	identify_line(char *line, int line_nb)
{
	if (line_nb == 0)
		return (-1);
	if (line[0] == '#')
		return (0);
	else if (ft_strchr(line, '-'))
		return (1);
	else
		return (2);
}

// -1: Ants, 0: Comment, 1: Edge, 2: Node
int count_lines_with_id(char **lines, int id)
{
	int count;
	int i;
	
	i = 0;
	count = 0;
	while (lines[i])
	{
		if (identify_line(lines[i], i) == id)
			count++;
		i++;
	}
	return (count);
}

void	handle_edges(char **lines, t_graph *g)
{
	int		i;
	int		edges_processed;

	g->edges = (t_edge **)malloc(sizeof(t_edge *) * (count_lines_with_id(lines, 1) + 1));
	edges_processed = 0;
	i = 1;
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 1)
			g->edges[edges_processed++] = handle_edge(lines[i], g->nodes);
		i++;
	}
	g->edges[edges_processed] = NULL;
	g->nb_of_edges = edges_processed;
}

void	handle_nodes(char **lines, t_graph *g)
{
	int		i;
	int		ret;
	int		nodes_processed;

	ret = 0;
	nodes_processed = 0;
	i = 0;
	g->nodes = (t_node **)malloc(sizeof(t_node *) * (count_lines_with_id(lines, 2) + 1));
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 0)
			ret = handle_comments(lines[i]);
		else if (identify_line(lines[i], i) == 2)
		{
			g->nodes[nodes_processed] = handle_node(lines[i], ret, g);
			g->nodes[nodes_processed]->id = nodes_processed;
			nodes_processed++;
			ret = 0;
		}
		i++;
	}
	g->nodes[nodes_processed] = NULL;
}

char	**read_from_stdout()
{
	int		ret;
	int		i;
	char 	*line;
	char 	**lines;

	i = 0;
	line = NULL;
	lines = (char **)malloc(sizeof(char *) * (MAX_LINES + 1));
	ret = ft_get_next_line(0, &line);
	while (ret)
	{
		lines[i] = ft_strdup(line);
		ret = ft_get_next_line(0, &line);
		i++;
	}
	free(line);
	return (lines);
}

int parser(t_graph *g)
{
	char **lines;
	
	lines = read_from_stdout();
	g->ants_available = ft_atoi(lines[0]);
	g->ants = (t_ant **)malloc(sizeof(t_ant *) * (g->ants_available + 1));
	g->ants[g->ants_available] = NULL;
	handle_nodes(lines, g);
	handle_edges(lines, g);
	ft_free_array(lines);
	return (0);
}

