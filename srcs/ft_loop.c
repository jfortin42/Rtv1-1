/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/19 14:17:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void    ft_process(t_env *e)
{
	if (e->keys.key_w)
	{
		e->cam.position.x -= sin(e->cam.rotation.x) * cos(e->cam.rotation.y) * e->speed;
		e->cam.position.y -= -sin(e->cam.rotation.y) * e->speed;
		e->cam.position.z += cos(e->cam.rotation.x) * cos(e->cam.rotation.y) * e->speed;
	}
	if (e->keys.key_s)
	{
		e->cam.position.x += sin(e->cam.rotation.x) * cos(e->cam.rotation.y) * e->speed;
		e->cam.position.y += -sin(e->cam.rotation.y) * e->speed;
		e->cam.position.z -= cos(e->cam.rotation.x) * cos(e->cam.rotation.y) * e->speed;
	}
	if (e->keys.key_a)
	{
		e->cam.position.x -= cos(e->cam.rotation.x) * e->speed;
		e->cam.position.z -= sin(e->cam.rotation.x) * e->speed;
	}
	if (e->keys.key_d)
	{
		e->cam.position.x += cos(e->cam.rotation.x) * e->speed;
		e->cam.position.z += sin(e->cam.rotation.x) * e->speed;
	}
	if (e->keys.key_ctrl)
		e->cam.position.y -= e->speed;
	if (e->keys.key_space)
		e->cam.position.y += e->speed;

	if (e->keys.up)
		e->selected_object->position.y += e->speed;
	if (e->keys.down)
		e->selected_object->position.y -= e->speed;

	if (e->keys.right)
		e->selected_object->position.x += e->speed;
	if (e->keys.left)
		e->selected_object->position.x -= e->speed;

	if (e->keys.key_1)
		e->selected_object->position.z += e->speed;
	if (e->keys.key_2)
		e->selected_object->position.z -= e->speed;
	if (e->keys.key_4)
		e->cam.rotation.x += M_PI / 16;
	if (e->keys.key_5)
		e->cam.rotation.x -= M_PI / 16;
	if (e->keys.key_e)
		e->selected_object->rotation.z += M_PI / 16;
	if (e->keys.key_q)
		e->selected_object->rotation.z -= M_PI / 16;
}

t_mat4  ft_mat4_inv_translate(t_mat4 trans)
{
	int i;

	i = 12;
	while (i < 15)
	{
		trans.as_mat[i] *= -1;
		i++;
	}
	return trans;
}

void	ft_compute_matrix(t_object *object)
{
	t_mat4 rotate = ft_mat4_mult(ft_mat4_rotate_x(object->rotation.y), ft_mat4_mult(ft_mat4_rotate_y(object->rotation.x), ft_mat4_rotate_z(object->rotation.z)));
	t_mat4 translate = ft_mat4_translate_vec(object->position);
	t_mat4 transform = ft_mat4_mult(translate, rotate);
	t_mat4 translate2 = ft_mat4_inv_translate(translate);	
	t_mat4 rotate2 = ft_mat4_mult(ft_mat4_rotate_z(-object->rotation.z), ft_mat4_mult(ft_mat4_rotate_y(-object->rotation.x), ft_mat4_rotate_x(-object->rotation.y)));
	t_mat4 invtransform = ft_mat4_mult(rotate2, translate2);
	t_mat4 transform_dir = rotate;
	t_mat4 transform_dir_inv = rotate2;
	
	object->transform_pos = transform;
	object->transform_dir = transform_dir;
	object->transform_pos_inv = invtransform;
	object->transform_dir_inv = transform_dir_inv;
}

void	ft_compute_matrices_list(t_list *objects)
{
	t_list *ptr;
	t_object *object;

	ptr = objects;
	while (ptr != NULL)
	{
		object = (t_object *)(ptr->content);
		ft_compute_matrix(object);
		ptr = ptr->next;
	}
}

float ft_min_pos(float a, float b)
{
	if (a < b && a >= 0)
		return a;
	if (b < a && b >= 0)
		return b;
	return (-1);
}
void	ft_init_keys(t_env *e)
{
	e->keys.up = 0;
	e->keys.down = 0;
	e->keys.left = 0;
	e->keys.right = 0;
	e->keys.key_o = 0;
	e->keys.key_p = 0;
	e->keys.key_7 = 0;
	e->keys.key_8 = 0;
	e->keys.key_5 = 0;
	e->keys.key_4 = 0;
	e->keys.key_2 = 0;
	e->keys.key_1 = 0;
	e->keys.key_w = 0;
	e->keys.key_a = 0;
	e->keys.key_s = 0;
	e->keys.key_d = 0;
	e->keys.key_e = 0;
	e->keys.key_q = 0;
	e->keys.key_ctrl = 0;
	e->keys.key_space = 0;
	e->keys.key_shift = 0;
}

t_spot *ft_new_spot(t_vec3 position)
{
	t_spot *res;
	res = (t_spot *)malloc(sizeof(t_spot));
	res->position = position;
	return (res);
}

int		ft_get_color_reduction(int color, float reduc)
{
	int r;
	int g;
	int b;

	r = (color >> 16) & (0xff);
	g = (color >> 8) & (0xff);
	b = color & (0xff);
	r = ft_clamp(0, r * reduc, 255);
	g = ft_clamp(0, g * reduc, 255);
	b = ft_clamp(0, b * reduc, 255);
	return ((r << 16) | (g << 8) | b);
}

int		ft_color_add(int color, float to_add)
{
	int r;
	int g;
	int b;

	r = (color >> 16) & (0xff);
	g = (color >> 8) & (0xff);
	b = color & (0xff);
	r = ft_clamp(0, r + (255 * to_add), 255);
	g = ft_clamp(0, g + (255 * to_add), 255);
	b = ft_clamp(0, b + (255 * to_add), 255);
	return ((r << 16) | (g << 8) | b);
}

void    ft_init_scene(t_env *e)
{
	e->objects = NULL;
	e->spots = NULL;
	e->cam.fov = (70 * M_PI) / 180.0;
	e->cam.position = ft_new_vec3(0, 0, -10);
	e->cam.rotation = ft_new_vec3(0 , 0, 0);
	e->speed = 0.2;
	e->ambiant_coefficient = 0.3;
	ft_init_keys(e);
	if (0)
	{
/*
	//RED
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(1.f, ft_new_vec3(0.f, 0.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0xff0000,), sizeof(t_object)));
	//YELLOW
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(1.f, ft_new_vec3(-10.f, 0.f, 20.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0xffff00), sizeof(t_object)));
	//GREEN
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(1.f, ft_new_vec3(0.f, 0.f, 20.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0x00ff00), sizeof(t_object)));

	//BLUE
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(-20.f, 0.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0xff00ff), sizeof(t_object)));

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(1.f, ft_new_vec3(-10.f, 0.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 2.f, 1.f), 0x0000ff), sizeof(t_object)));

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f, 0.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0x00ffff), sizeof(t_object)));

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI / 64, ft_new_vec3(0.f, 0.f, 20.f),
		ft_new_vec3(0.0f, 0.0f, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0xff00ff), sizeof(t_object)));
	*/
	}
	else if(1)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f, 0.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x444444), sizeof(t_object)));

		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 30.f, 55.f),
					ft_new_vec3(0.0f, M_PI / 2, 0.0f), 0x0000ff), sizeof(t_object)));

		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 10.f, 0.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x444444), sizeof(t_object)));


		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(-10.f, 0.f, 40.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));

		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, 10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, -10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));


		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(10.f, 0.f, 40.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
	
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, 10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, -10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));

//		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI / 16, ft_new_vec3(-10.f, 0.f, 20.f),						
//			ft_new_vec3(0.0f, 0.0f, M_PI / 2), ft_new_vec3(1.f, 1.f, 1.f), 0xff00ff), sizeof(t_object)));

		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(-10.f, 0.f,10.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
	
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, 10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, -10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));

		
//		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(10.f, 0.f, 10.f),
//					ft_new_vec3(0.0f, 0.0f, M_PI / 2), ft_new_vec3(1.f, 1.f, 1.f), 0x777777, 0, 0), sizeof(t_object)));	
		
//		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, 10.f, 10.f),
//					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0x777777, 0, 0), sizeof(t_object)));
		
//		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, -10.f, 10.f),
//					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f), 0x777777, 0, 0), sizeof(t_object)));

		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI * 0.1, ft_new_vec3(10.f, 0.f, 10.f),
					ft_new_vec3(0.0f, 0, M_PI / 2), 0x0000ff), sizeof(t_object)));
//		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.f, ft_new_vec3(0.f, -8.f, 13.f),
//					ft_new_vec3(0.0f, 0.0, 0.0f), ft_new_vec3(2.f, 1.f, 1.f), 0xff0000, 100, 2), sizeof(t_object)));
	
	}
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(10.5f, ft_new_vec3(-15.f, 8.f, 5.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0xff0000), sizeof(t_object)));

//	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(-30.f, 6.f, 5.f)), sizeof(t_spot)));
	
//	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(-21.f, 0.f, -8.f)), sizeof(t_spot)));
//	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(10.f, -4.f, 6.f)), sizeof(t_spot)));
	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(-10.f, -4.f, 6.f)), sizeof(t_spot)));

//	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(0.f, 0.f, -10.f)), sizeof(t_spot)));
	e->selected_object = (t_object *)(e->objects->content);
	ft_compute_matrices_list(e->objects);
}

int		ft_intersect_objects(t_list *objects, t_ray ray, t_object *except)
{
	t_list *ptr;
	t_intersect intersect;
	float value;
	t_object *object;
	t_ray save;
	
	save = ray;
	ray.direction = ft_vec3_mat4_mult(save.direction, except->transform_dir_inv);
	ray.position = ft_vec3_mat4_mult(save.position, except->transform_pos_inv);
	intersect = except->intersect_func(ray, except);
	value = intersect.t;

	ptr = objects;
	while (ptr != NULL)
	{
		object = (t_object *)(ptr->content);
		ray.direction = ft_vec3_mat4_mult(save.direction, object->transform_dir_inv);
		ray.position = ft_vec3_mat4_mult(save.position, object->transform_pos_inv);
		intersect = object->intersect_func(ray, object);
		if (intersect.t > 0 && intersect.t < value)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}


void    ft_render(t_env *e)
{
	t_ray   ray;
	t_intersect intersect;
	t_intersect min;
	t_object	*object;
	double px;
	double py;
	int *pix;
	t_mat4 cam_rot;
	t_list *ptr;

	ft_compute_matrices_list(e->objects);
	SDL_LockSurface(e->sdl.surface);
	pix = (int *)e->sdl.surface->pixels;

	cam_rot = ft_mat4_mult(ft_mat4_rotate_x(e->cam.rotation.y), ft_mat4_mult(ft_mat4_rotate_y(e->cam.rotation.x), ft_mat4_rotate_z(e->cam.rotation.z)));
	cam_rot = ft_mat4_transpose(cam_rot);
	int i;
	int j;
	t_vec3 c;
	t_vec3 n;
	t_object *intersected_object;
	t_spot	*spot;
	t_ray	light_ray;
	t_vec3	ray_rot;
	t_vec3	rm;
	t_vec3	v;
	float alpha;
	float diffuse_factor;
	float specular_factor;
	int step = 1;
	if (e->mode == 0)
		step = 1;
	alpha = 1;
	i = 0;
	while (i < e->sdl.screen.h)
	{
		j = 0;
		while (j < e->sdl.screen.w)
		{
			px = ((2 * ((j + 0.5) / e->sdl.screen.w)) - 1);
			py = (1 - (2 * (i + 0.5) / e->sdl.screen.h));
			t_vec3 lol = ft_new_vec3(px, py, 1);
			ft_vec3_normalize(&lol);
			ptr = e->objects;
			min.t = -1;
			ray_rot = ft_vec3_mat4_mult(lol, cam_rot);
			while (ptr != NULL)
			{
				object = (t_object *)(ptr->content);
				ray.position = ft_vec3_mat4_mult(e->cam.position, object->transform_pos_inv);
				ray.direction = ft_vec3_mat4_mult(ray_rot, object->transform_dir_inv);
				ft_vec3_normalize(&(ray.direction));
				if (i == e->sdl.screen.h / 2 && j == e->sdl.screen.w / 2)
				{
					if (object->intersect_func == ft_intersect_cone)
					{
						printf("cone dir \n");
						ft_print_vec3(ray.direction);
					}
				}
				intersect = object->intersect_func(ray, object);
				if (intersect.t > 0 && (intersect.t < min.t || min.t == -1))
				{
					min = intersect;
					intersected_object = object;
				}
				ptr = ptr->next;
			}
			if (min.t != -1)
			{
				c = ft_vec3_mat4_mult(min.intersection, intersected_object->transform_pos);
				n = ft_vec3_mat4_mult(min.normal, intersected_object->transform_dir);
				ptr = e->spots;
				diffuse_factor = 0;
				specular_factor = 0;
				while (ptr != NULL)
				{
					spot = (t_spot *)(ptr->content);
					light_ray.position = spot->position;
					light_ray.direction = ft_vec3_cmp(c, light_ray.position);
					ft_vec3_normalize(&(light_ray.direction));
					ft_vec3_normalize(&n);
					if (!ft_intersect_objects(e->objects, light_ray, intersected_object))
					{
						diffuse_factor += ft_fmax(0, ft_dot_product(ft_vec3_scalar(light_ray.direction, -1), n));
						
						rm = ft_vec3_cmp(ft_vec3_scalar(n, 2 *  (ft_dot_product(light_ray.direction, n))), light_ray.direction);
						v = ft_vec3_cmp(c, e->cam.position);
						ft_vec3_normalize(&v);
						ft_vec3_normalize(&rm);
						specular_factor += pow(ft_fmax(0, ft_dot_product(v, rm)), intersected_object->smoothness);
					}
					ptr = ptr->next;
				}
				if (i == e->sdl.screen.h / 2 && j == e->sdl.screen.w / 2)
				{
					printf("RAY ROT\n");
					ft_print_vec3(ray_rot);
					printf("RAY \n");
					ft_print_vec3(ray_rot);
					pix[e->sdl.screen.w * i + j] = 0x00ff00;
				}
				else
					pix[e->sdl.screen.w * i + j] = ft_color_add(ft_get_color_reduction(intersected_object->color, e->ambiant_coefficient + (1 - e->ambiant_coefficient) * ft_fclamp(0, diffuse_factor, 1)), intersected_object->shininess * specular_factor);
			}
			j += step;
		}
		i += step;
	}
	if (!(e->sdl.texture = SDL_CreateTextureFromSurface(e->sdl.renderer,
		e->sdl.surface)))
		exit(1);
	SDL_FillRect(e->sdl.surface, NULL, 0x000000);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &(e->sdl.screen));
	SDL_RenderPresent(e->sdl.renderer);
}

void	ft_loop(t_env *e)
{
	int end;
	SDL_Event event;
	ft_init_scene(e);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	end = 0;
	ft_render(e);
	while (!end)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN)
				ft_keys_down(e, event);
			if (event.type == SDL_KEYUP)
				ft_keys_up(e, event);
			if (event.type == SDL_MOUSEMOTION)
				ft_mouse_motion(e, event);
			if (event.window.event == SDL_WINDOWEVENT_CLOSE ||
					(event.key.keysym.sym == SDLK_ESCAPE
					 && event.type == SDL_KEYDOWN))
				end = 1;
		}
		if (e->mode == 0)
		{
			ft_process(e);
			ft_render(e);
		}
		SDL_Delay(12);
	}
}
