/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:46:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/24 17:10:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_pow(int a, int b)
{
	int i;
	int res;

	res = 1;
	i = 0;
	while (i < b)
	{
		res *= a;
		i++;
	}
	return (res);
}

static void		ft_add_float(char **s, int *i, float *res)
{
	int point;

	point = *i;
	*i += 1;
	while (ft_isdigit((*s)[*i]))
	{
		*res += ((*s)[*i] - '0') / (float)(ft_pow(10, *i - point));
		*i += 1;
	}
}

float	ft_patof(char **s)
{
	int		i;
	float	res;
	int		start;

	res = 0;
	start = 0;
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
	if ((*s)[i] == '.')
		ft_add_float(s, &i, &res);
	if ((*s)[start] == '-')
		res *= -1;
	*s += i;
	return (res);
}
