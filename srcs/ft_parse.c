/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 17:43:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/26 17:58:51 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_init_parsing(t_env *e, int *nb_lines)
{
	*nb_lines = 1;
	e->objects = NULL;
	e->spots = NULL;
	e->cam.rotation = ft_new_vec3(0, 0, 0);
	e->cam.position = ft_new_vec3(0, 0, -1);
	e->ambiant_coefficient = 0.3;
}

int		ft_process_parse_objects(char *str, t_env* e)
{
	if (!ft_strcmp("sphere", str))
	{
		e->parser.parsed_object = SPHERE;
		return (ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(),
			sizeof(t_object))));
	}
	else if (!ft_strcmp("cylinder", str))
	{
		e->parser.parsed_object = CYLINDER;
		return (ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(),
			sizeof(t_object))));
	}
	else if (!ft_strcmp("plane", str))
	{
		e->parser.parsed_object = PLANE;
		return (ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(),
			sizeof(t_object))));
	}
	else if (!ft_strcmp("cone", str))
	{
		e->parser.parsed_object = CONE;
		return (ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(),
			sizeof(t_object))));
	}
	else if (!ft_strcmp("light", str))
	{
		e->parser.parsed_object = LIGHT;
		return (ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(),
			sizeof(t_spot))));
	}
	else if (!ft_strcmp("ambiant", str))
	{
		e->parser.parsed_object = AMBIANT;
		return (0);
	}
	else
		return (1);
	return (0);
}

int		ft_process_parse_attributes(char *str, t_env *e)
{
	if (!ft_strncmp("pos ", str, 4))
		return (ft_parse_pos(&(str[4]), e));
	else if (!ft_strncmp("rot ", str, 4))
		return (ft_parse_rot(&(str[4]), e));
	else if (!ft_strncmp("col ", str, 4))
		return (ft_parse_col(&(str[4]), e));
	else if (!ft_strncmp("radius ", str, 6))
		return (ft_parse_radius(&(str[6]), e));
	else if (!ft_strncmp("angle ", str, 6))
		return (ft_parse_angle(&(str[6]), e));
	else if (!ft_strncmp("shine ", str, 6))
		return (ft_parse_shine(&(str[6]), e));
	else if (!ft_strncmp("smooth ", str, 7))
		return (ft_parse_smooth(&(str[7]), e));
	else if (!ft_strncmp("intensity ", str, 10))
		return (ft_parse_intensity(&(str[10]), e));
	else
		return (ft_process_parse_objects(str, e));
}

int		ft_process_parse(int nb_lines, char *str, t_env *e)
{
	if (nb_lines == 1)
	{
		if (ft_strcmp(str, "cam"))
			return (1);
	   else
	   {
		   e->parser.parsed_object = CAMERA;
		   return (0);
	   }
	}
	else
		return ft_process_parse_attributes(str, e);
}

int		get_fd(int *fd, char *filename)
{
	if ((*fd = open(filename, O_RDONLY)) == -1)
	{
		perror(filename);
		return (-1);
	}
	else
		return (0);
}
int		ft_parse(char *filename, t_env *e)
{
	int fd;
	char *buff;
	int ret;
	int		nb_lines;


	buff = NULL;
	ft_init_parsing(e, &nb_lines);
	if (get_fd(&fd, filename))
		return (1);
	while ((ret = get_next_line(fd, &buff)))
	{
		if (ret == -1 || ft_process_parse(nb_lines, buff, e))
		{
			printf("BUG : %s\n", buff);
			if (buff != NULL)
				ft_strdel(&buff);
				ft_free_lists(e);
			return 1;
		}
		nb_lines++;
		ft_strdel(&buff);
	}
	ft_strdel(&buff);
	return (0);
}
