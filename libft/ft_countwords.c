/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:01:14 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/09 19:02:27 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_countwords(char *line, char delimiter)
{
	int	i;
	int	count;
	int word_in_progress;

	i = 0;
	count = 0;
	word_in_progress = 0;
	while (line[i])
	{
		while ((line[i] != delimiter) && word_in_progress == 1)
			i++;
		word_in_progress = 0;
		while (line[i] == delimiter)
			i++;
		if (line[i] != delimiter)
		{
			count++;
			word_in_progress = 1;
		}
		i++;
	}
	return (count);
}
