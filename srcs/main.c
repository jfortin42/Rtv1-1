/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:33:57 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/17 17:03:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_env e;

	if (!ft_init_all(&e))
		return (1);
	if (argc != 1)
		e.mode = 1;
	else
		e.mode = 0;
	ft_loop(&e);
	return (0);
}
