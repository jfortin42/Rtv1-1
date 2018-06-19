/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:15:47 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/19 21:59:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_hit	ft_trace(t_ray ray, t_env *e)
{
	t_list *ptr;
	t_object *object;
	float t;
	t_hit hit;
	t_ray save;

	save = ray;
	hit.t = -1;
	ptr = e->objects;
	while (ptr != NULL)
	{
		object = (t_object *)(ptr->content);
		ray.position = ft_vec3_mat4_mult(save.position, object->transform_pos_inv);
		ray.direction = ft_vec3_mat4_mult(save.direction, object->transform_dir_inv);
		ft_vec3_normalize(&(ray.direction));
		t = object->intersect_func(ray, object);
		if (t > 0 && (t < hit.t || hit.t == -1))
		{
				hit.t = t;
			hit.point = ft_vec3_add(ft_vec3_scalar(ray.direction, hit.t),
					ray.position);
			hit.normal = object->normal_func(hit.point,
						object);
			hit.world_point = ft_vec3_mat4_mult(hit.point,
					object->transform_pos);
			hit.world_normal = ft_vec3_mat4_mult(hit.normal,
					object->transform_dir);
		//	if (ft_dot_product(save.direction, hit.world_normal) > 0)
		//		hit.world_normal = ft_vec3_scalar(hit.world_normal, -1);
			hit.object = object;
		}
		ptr = ptr->next;
	}
	if (ray.x == e->sdl.screen.w / 2 && ray.y == e->sdl.screen.h / 2)
	{
		printf("%f\n", hit.t);
		ft_print_vec3(hit.world_normal);
	}
	return (hit);
}

void    ft_render(t_env *e)
{
	t_ray   ray;
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
	t_spot	*spot;
	t_ray	light_ray;
	t_vec3	rm;
	t_vec3	v;
	float alpha;
	float diffuse_factor;
	float specular_factor;
	int step = 1;
	t_hit hit;
	t_hit hit2;
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
			ray.direction = ft_new_vec3(px, py, 1);
			ray.direction = ft_vec3_mat4_mult(ray.direction, cam_rot);
			ray.position = e->cam.position;
			ray.x = j;
			ray.y = i;
			hit = ft_trace(ray, e);
			if (hit.t != -1)
			{
				ptr = e->spots;
				diffuse_factor = 0;
				specular_factor = 0;
				while (ptr != NULL)
				{
					spot = (t_spot *)(ptr->content);
					ft_vec3_normalize(&(hit.world_normal));
					light_ray.position = spot->position;
					light_ray.direction = ft_vec3_cmp(hit.world_point, light_ray.position);
					float light_inter_dist = ft_magnitude(light_ray.direction);
					ft_vec3_normalize(&(light_ray.direction));
					hit2 = ft_trace(light_ray, e);
					if (hit2.t >= light_inter_dist - 0.1)
					{
						light_ray.direction = ft_vec3_cmp(hit.world_point, spot->position);
						ft_vec3_normalize(&(light_ray.direction));
						diffuse_factor += ft_fmax(0, ft_dot_product(ft_vec3_scalar(light_ray.direction, -1), hit.world_normal));
						rm = ft_vec3_cmp(ft_vec3_scalar(hit.world_normal, 2 * (ft_dot_product(light_ray.direction, hit.world_normal))), light_ray.direction);
						v = ft_vec3_cmp(hit.world_point, e->cam.position);
						ft_vec3_normalize(&v);
						ft_vec3_normalize(&rm);
						specular_factor += pow(ft_fmax(0, ft_dot_product(light_ray.direction, rm)), hit.object->smoothness);
					}
					ptr = ptr->next;
				}
				if (i == e->sdl.screen.h / 2 && j == e->sdl.screen.w / 2)
					pix[e->sdl.screen.w * i + j] = 0x00ff00;
				else
					pix[e->sdl.screen.w * i + j] = ft_color_add(ft_get_color_reduction(hit.object->color, e->ambiant_coefficient + (1 - e->ambiant_coefficient) * ft_fclamp(0, diffuse_factor, 1)), hit.object->shininess * specular_factor);
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
