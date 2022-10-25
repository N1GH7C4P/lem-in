/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countlines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:21:09 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/25 16:22:44 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_countlines(char	**lines)
{
	int	count;

	if (!lines)
		return (0);
	count = 0;
	while (lines[count])
		count++;
	return (count);
}
