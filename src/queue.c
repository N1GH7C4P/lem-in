/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:54:13 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/27 16:49:50 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_queue	*new_queue(size_t n)
{
	t_queue	*new_queue;

	new_queue = (t_queue *)malloc(sizeof(t_queue));
	new_queue->inp_arr = (t_node **)malloc(sizeof(t_node *) * n + 1);
	new_queue->inp_arr[n] = NULL;
	new_queue->front = -1;
	new_queue->rear = -1;
	return (new_queue);
}

int	is_empty(t_queue *q)
{	
	if (q->front == - 1 || q->front > q->rear)
	if (q->front == q->rear)
		return (1);
	return (0);
}

void enqueue(t_queue *q, t_node *node)
{
    if (q->rear == QUEUE_MAX - 1)
       ft_putendl("Overflow \n");
    else
    {
		if (q->front == - 1)
      		q->front = 0;
        q->rear = q->rear + 1;
        q->inp_arr[q->rear] = node;
    }
} 
 
t_node *dequeue(t_queue *q)
{
	t_node	*ret;

    if (q->front == - 1 || q->front > q->rear)
		ft_putendl("Underflow \n");
    else
	{
		ret = q->inp_arr[q->front];
		q->front = q->front + 1;
		return (ret);
    }
	return NULL;
} 
 
void show(t_queue *q)
{
    int i;

    if (q->front == - 1)
        ft_putendl("Empty Queue \n");
    else
    {
        ft_putendl("Queue: \n");
		i = q->front;
        while (i <= q->rear)
		{
			print_node((t_node *)q->inp_arr[i], 1);
			i++;
		}
        ft_putendl("\n");
    }
} 