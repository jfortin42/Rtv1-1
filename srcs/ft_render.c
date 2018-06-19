/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:15:47 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/19 15:42:23 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void    ft_render(t_env *e)
{
	t_ray   ray;
	t_intersect intersect;
	t_intersect min;
	t_object	*object;
	double px;
	double py;
	double image_ratio = (float)e->sdl.screen.w / (float)e->sdl.screen.h;
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
			px = (2 * ((j + 0.5) / e->sdl.screen.w) - 1) * tan(e->cam.fov / 2) * image_ratio;
			py = (1 - 2 * (i + 0.5) / e->sdl.screen.h) * tan(e->cam.fov / 2);
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
	SDL_DestroyTexture(e->sdl.texture);
	SDL_RenderPresent(e->sdl.renderer);
	}
