/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:46:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/26 17:31:56 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_patoi(char **s)
{
	int i;
	int res;
	int start;

	start = 0;
	res = 0;
	while (ft_isseparator((*s)[start]))
		start++;
	i = start;
	if ((*s)[i] == '+' || (*s)[i] == '-')
		i++;
	while (ft_isdigit((*s)[i]))
	{
		res = res * 10 + (*s)[i] - '0';
		i++;
	}
	if ((*s)[start] == '-')
		res *= -1;
	*s += i;
	return (res);
}
