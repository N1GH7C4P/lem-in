/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:27:40 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/25 18:26:47 by kpolojar         ###   ########.fr       */
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

t_node	*handle_node(char *line, int ret, t_graph *graph)
{
	char	**words;
	t_node	*new_node;
	
	words = ft_strsplit(line, ' ');
	new_node = create_node(ft_atoi(words[1]), ft_atoi(words[2]), words[0], ret);
	if (ret == 1)
		graph->start = new_node;
	else if (ret == 2)
		graph->end = new_node;
	ft_free_array(words);
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

t_edge **handle_edges(char **lines, t_graph *graph, t_node **nodes)
{
	int		i;
	t_edge	**edges;
	int		edges_processed;

	edges = (t_edge **)malloc(sizeof(t_edge *) * (count_lines_with_id(lines, 1) + 1));
	edges_processed = 0;
	i = 1;
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 1)
			edges[edges_processed++] = handle_edge(lines[i], nodes);
		i++;
	}
	edges[edges_processed] = NULL;
	graph->nb_of_edges = edges_processed;
	print_edges(edges);
	return (edges);
}

t_node **handle_nodes(char **lines, t_graph *graph)
{
	int		i;
	int		ret;
	t_node	**nodes;
	int		nodes_processed;

	nodes_processed = 0;
	i = 0;
	nodes = (t_node **)malloc(sizeof(t_node *) * (count_lines_with_id(lines, 2) + 1));
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 0)
			ret = handle_comments(lines[i]);
		else if (identify_line(lines[i], i) == 2)
		{
			nodes[nodes_processed++] = handle_node(lines[i], ret, graph);
			ret = 0;
		}
		i++;
	}
	nodes[nodes_processed] = NULL;
	print_nodes(nodes, 1);
	return (nodes);
}

char	**read_from_stdout()
{
	int ret;
	char *line;
	char **lines;
	int i;

	i = 0;
	line = NULL;
	lines = (char **)malloc(sizeof(char *) * (MAX_LINES + 1));
	ret = ft_get_next_line(1, &line);
	while (ret)
	{
		lines[i] = ft_strdup(line);
		ret = ft_get_next_line(1, &line);
		if (!ft_strcmp(line, ""))
			break;
		i++;
	}
	free(line);
	return (lines);
}

int parser(t_graph *graph)
{
	static t_node	**nodes;
	static t_edge	**edges;

	char **lines = read_from_stdout();
	graph->ants = ft_atoi(lines[0]);
	nodes = handle_nodes(lines, graph);
	edges = handle_edges(lines, graph, nodes);	
	graph->edges = edges;	

	ft_free_array(lines);
	return (0);
}

