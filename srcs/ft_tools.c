/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 22:34:20 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/26 17:48:55 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	ft_deg_to_rad(int deg)
{
	return (M_PI * deg / 180.0);
}

void	ft_free_lists(t_env *e)
{
	t_list	*ptr;
	t_list	*next;

	ptr = e->objects;
	while (ptr)
	{
		next = ptr->next;
		free(ptr->content);
		free(ptr);
		ptr = NULL;
		ptr = next;
	}
	ptr = e->spots;
	while (ptr)
	{
		next = ptr->next;
		free(ptr->content);
		free(ptr);
		ptr = NULL;
		ptr = next;
	}
}
