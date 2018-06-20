/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:15:47 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/20 21:55:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		ft_get_ray_at_pixel(int j, int i, t_env *e)
{
	t_ray	ray;
	double	px;
	double	py;
	t_mat4	cam_rot;
	double	image_ratio;

	image_ratio = (float)e->sdl.screen.w / (float)e->sdl.screen.h;
	cam_rot = ft_mat4_mult(ft_mat4_rotate_x(e->cam.rotation.y),
			ft_mat4_mult(ft_mat4_rotate_y(e->cam.rotation.x),
				ft_mat4_rotate_z(e->cam.rotation.z)));
	cam_rot = ft_mat4_transpose(cam_rot);
	px = (2 * ((j + 0.5) / e->sdl.screen.w) - 1) * tan(e->cam.fov / 2) *
		image_ratio;
	py = (1 - 2 * (i + 0.5) / e->sdl.screen.h) * tan(e->cam.fov / 2);
	ray.direction = ft_new_vec3(px, py, 1);
	ray.direction = ft_vec3_mat4_mult(ray.direction, cam_rot);
	ray.position = e->cam.position;
	return (ray);
}

void		ft_process_shading(t_spot *spot, t_hit hit, t_env *e, t_phong *p)
{
	t_ray	light_ray;
	float	light_inter_dist;
	t_vec3	rm;
	t_vec3	v;
	t_hit	hit2;

	light_ray.position = spot->position;
	light_ray.direction = ft_vec3_cmp(hit.world_point, light_ray.position);
	light_inter_dist = ft_magnitude(light_ray.direction);
	ft_vec3_normalize(&(light_ray.direction));
	hit2 = ft_trace(light_ray, e);
	if (hit2.t >= light_inter_dist - 0.1)
	{
		light_ray.direction = ft_vec3_cmp(hit.world_point, spot->position);
		ft_vec3_normalize(&(light_ray.direction));
		p->diffuse_factor += ft_fmax(0, ft_dot_product(ft_vec3_scalar(
			light_ray.direction, -1), hit.world_normal));
		rm = ft_vec3_cmp(ft_vec3_scalar(hit.world_normal, 2 * (ft_dot_product(
				light_ray.direction, hit.world_normal))), light_ray.direction);
		v = ft_vec3_cmp(hit.world_point, e->cam.position);
		ft_vec3_normalize(&v);
		ft_vec3_normalize(&rm);
		p->specular_factor += pow(ft_fmax(0, ft_dot_product(
			light_ray.direction, rm)), hit.object->smoothness);
	}
}

int			ft_compute_shading(t_hit hit, t_env *e)
{
	t_list	*ptr;
	t_spot	*spot;
	t_phong phong;

	ptr = e->spots;
	phong.diffuse_factor = 0;
	phong.specular_factor = 0;
	while (ptr != NULL)
	{
		spot = (t_spot *)(ptr->content);
		ft_process_shading(spot, hit, e,
				&phong);
		ptr = ptr->next;
	}
	return (ft_color_add(ft_get_color_reduction(
				hit.object->color, e->ambiant_coefficient +
				(1 - e->ambiant_coefficient) *
				ft_fclamp(0, phong.diffuse_factor, 1)),
			hit.object->shininess * phong.specular_factor));
}

void		ft_fill_canvas(t_env *e)
{
	if (!(e->sdl.texture = SDL_CreateTextureFromSurface(e->sdl.renderer,
					e->sdl.surface)))
		exit(1);
	SDL_FillRect(e->sdl.surface, NULL, 0x000000);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &(e->sdl.screen));
	SDL_DestroyTexture(e->sdl.texture);
	SDL_RenderPresent(e->sdl.renderer);
}

void		ft_render(t_env *e)
{
	t_ray	ray;
	int		*pix;
	int		i;
	int		j;
	t_hit	hit;

	i = 0;
	ft_compute_matrices_list(e->objects);
	SDL_LockSurface(e->sdl.surface);
	pix = (int *)e->sdl.surface->pixels;
	while (i < e->sdl.screen.h)
	{
		j = 0;
		while (j < e->sdl.screen.w)
		{
			ray = ft_get_ray_at_pixel(j, i, e);
			hit = ft_trace(ray, e);
			if (hit.t != -1)
				pix[e->sdl.screen.w * i + j] = ft_compute_shading(hit, e);
			j++;
		}
		i++;
	}
	ft_fill_canvas(e);
}
