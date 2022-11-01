/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:27:40 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/01 23:04:51 by kpolojar         ###   ########.fr       */
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
	ft_putendl("edge start: ");
	print_node(start, 1);
	ft_putendl("");
	end = get_node_by_name(words[1], nodes);
	ft_putendl("edge end: ");
	print_node(end, 1);
	ft_putendl("");
	new_edge = create_edge(start, end);
	print_edge(new_edge);
	ft_putendl("");
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
	graph->nb_of_nodes = graph->nb_of_nodes + 1;
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

void	handle_edges(char **lines, t_graph *graph)
{
	int		i;
	int		edges_processed;

	ft_putstr("lines: ");
	ft_putnbr(count_lines_with_id(lines, 1));
	ft_putendl("");
	graph->edges = (t_edge **)malloc(sizeof(t_edge *) * (count_lines_with_id(lines, 1) + 1));
	edges_processed = 0;
	i = 1;
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 1)
			graph->edges[edges_processed++] = handle_edge(lines[i], graph->nodes);
		i++;
	}
	ft_putstr("Edges total: ");
	ft_putnbr(edges_processed);
	ft_putendl("");
	graph->edges[edges_processed] = NULL;
	graph->nb_of_edges = edges_processed;
	print_edges(graph->edges);
}

void	handle_nodes(char **lines, t_graph *graph)
{
	int		i;
	int		ret;
	int		nodes_processed;

	nodes_processed = 0;
	i = 0;
	graph->nodes = (t_node **)malloc(sizeof(t_node *) * (count_lines_with_id(lines, 2) + 1));
	while (lines[i])
	{
		if (identify_line(lines[i], i) == 0)
			ret = handle_comments(lines[i]);
		else if (identify_line(lines[i], i) == 2)
		{
			graph->nodes[nodes_processed] = handle_node(lines[i], ret, graph);
			graph->nodes[nodes_processed]->id = nodes_processed;
			nodes_processed++;
			ret = 0;
		}
		i++;
	}
	graph->nodes[nodes_processed] = NULL;
	print_nodes(graph->nodes, 1);
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
	char **lines;
	
	lines = read_from_stdout();
	graph->ants = ft_atoi(lines[0]);
	handle_nodes(lines, graph);
	ft_putendl("Nodes parsed");
	handle_edges(lines, graph);	
	ft_free_array(lines);
	return (0);
}

