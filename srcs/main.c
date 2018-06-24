/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:33:57 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/24 23:36:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_error(int type)
{
	if (type == 2)
		ft_putstr("Invalid mode. Available mode: 'fast'\n");
	ft_putstr("usage: ./rtv1 scene [ -mode ]\n");
	return (1);
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

void	ft_print_vec3(t_vec3 vec)
{
	printf("%f, %f, %f\n", vec.x, vec.y, vec.z);
}

void	ft_print_object(t_object *object)
{
	if (object->intersect_func == ft_intersect_sphere)
		printf("sphere\n");
	else if (object->intersect_func == ft_intersect_cylinder)
		printf("cylinder\n");
	else if (object->intersect_func == ft_intersect_plane)
		printf("plane\n");
	else if (object->intersect_func == ft_intersect_cone)
		printf("cone\n");
	printf("pos:\n");
	ft_print_vec3(object->position);
	printf("rot:\n");
	ft_print_vec3(object->rotation);
	printf("position\n");
	ft_printf("color: %#.6x\n", object->color);
}

void	ft_print_all(t_env e)
{
	t_list *ptr;
	t_object *object;

	printf("camera\n");
	printf("position\n");
	ft_print_vec3(e.cam.position);
	printf("rotation\n");
	ft_print_vec3(e.cam.rotation);

	ptr = e.objects;
	while(ptr)
	{
		object = (t_object *)(ptr->content);
		ft_print_object(object);

		ptr = ptr->next;
	}
}

int		main(int argc, char **argv)
{
	t_env	e;

	if (argc < 2 || argc > 3)
		return (ft_error(0));
	if (argc >= 2)
	{
		ft_parse(argv[1], &e);
		ft_print_all(e);
		ft_init_scene(&e);
	}
	e.mode = 0;
	if (argc == 3 && !ft_set_mode(&e, argv[2]))
		return (ft_error(2));
	if (!ft_init_all(&e))
		return (1);
	ft_loop(&e);
	return (0);
}
