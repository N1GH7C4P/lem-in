/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:54:13 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/04 18:02:46 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_queue	*new_queue(size_t n)
{
	t_queue	*new_queue;

	new_queue = (t_queue *)malloc(sizeof(t_queue));
	new_queue->inp_arr = (t_node **)malloc(sizeof(t_node *) * (n + 1));
	new_queue->inp_arr[n] = NULL;
	new_queue->front = -1;
	new_queue->rear = -1;
	return (new_queue);
}

void	free_queue(t_queue *q)
{
	free(q->inp_arr);
	free(q);
}

int	is_empty(t_queue *q)
{	
	if (q->front == -1 || q->front > q->rear)
		return (1);
	return (0);
}

void	enqueue(t_queue *q, t_node *node)
{
	if (q->rear == QUEUE_MAX - 1)
		ft_putendl("Overflow \n");
	else
	{
		if (q->front == -1)
			q->front = 0;
		q->rear = q->rear + 1;
		q->inp_arr[q->rear] = node;
	}
}

t_node	*dequeue(t_queue *q)
{
	t_node	*ret;

	if (q->front == -1 || q->front > q->rear)
		ft_putendl("Underflow \n");
	else
	{
		ret = q->inp_arr[q->front];
		q->front = q->front + 1;
		return (ret);
	}
	return (NULL);
}
