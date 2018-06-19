/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:33:57 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/19 12:23:03 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_error(int type)
{
	if (type == 1)
	{
		ft_putstr("Invalid scene. ");
		ft_putstr("Available scenes: 'scene1' 'scene2' 'scene3'\n");
	}
	else if (type == 2)
		ft_putstr("Invalid mode. Available mode: 'fast'\n");
	ft_putstr("usage: ./rtv1 scene [ -mode ]\n");
	return (1);
}

int		ft_set_scene(t_env *e, char *scene)
{
	if (ft_strcmp(scene, "scene1") == 0)
	{
		e->scene = 1;
		return (1);
	}
	if (ft_strcmp(scene, "scene2") == 0)
	{
		e->scene = 2;
		return (1);
	}
	if (ft_strcmp(scene, "scene3") == 0)
	{
		e->scene = 3;
		return (1);
	}
	return (0);
}

int		ft_set_mode(t_env *e, char *scene)
{
	if (ft_strcmp(scene, "-fast") == 0)
	{
		e->mode = 1;
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_env	e;

	if (argc < 2 || argc > 3)
		return (ft_error(0));
	if (!ft_set_scene(&e, argv[1]))
		return (ft_error(1));
	e.mode = 0;
	if (argc == 3 && !ft_set_mode(&e, argv[2]))
		return (ft_error(2));
	if (!ft_init_all(&e))
		return (1);
	ft_loop(&e);
	return (0);
}
