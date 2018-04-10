/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/10 00:46:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_render(t_env *e)
{
	SDL_SetRenderDrawColor(e->sdl.renderer, 255, 0, 0, 0);
	SDL_RenderClear(e->sdl.renderer);
	SDL_RenderPresent(e->sdl.renderer);
	(void)e;
}

void	ft_process(t_env *e)
{
	(void)e;
}


t_mat4	ft_mat4_inv_scale(t_mat4 scale)
{
	int i;

	i = 0;
	while(i < 15)
	{
		if (scale.as_mat[i])
			scale.as_mat[i] = 1.f / scale.as_mat[i];
		i += 5;
	}
	return scale;
}

t_mat4	ft_mat4_inv_translate(t_mat4 scale)
{
	int i;

	i = 12;
	while(i < 15)
	{
		scale.as_mat[i] *= -1;
		i++;
	}
	return scale;
}

t_sphere	ft_new_sphere(float radius, t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_sphere res;

	res.color = 0xff0000;
	res.radius = radius;
	res.position = pos;
	res.rotation = rot;
	res.scale = scale;
	return (res);
}

void	ft_init_test(t_env *e)
{
	e->test.sphere = ft_new_sphere(1.f, ft_new_vec3(0.f, 0.f, 10.f),
		ft_new_vec3(0.0f, M_PI, 0.0f), ft_new_vec3(1.f, 1.f, 1.f));

	t_mat4 rotate = ft_mat4_rotate_vec(e->test.sphere.rotation);
	ft_printf("rotate\n");
	ft_print_mat4(rotate);
	
	t_mat4 translate = ft_mat4_translate_vec(e->test.sphere.position);
	ft_printf("translate\n");
	ft_print_mat4(translate);
	
	t_mat4 scale = ft_mat4_scale_vec(e->test.sphere.scale);
	ft_printf("scale\n");
	ft_print_mat4(scale);

	t_mat4 transform = ft_mat4_model_view_matrix_mat(translate, scale, rotate);

	ft_printf("TRANSFORM\n");
	ft_print_mat4(transform);
	
	t_mat4 scale2 = ft_mat4_inv_scale(scale);
	t_mat4 translate2 = ft_mat4_inv_translate(translate);
	t_mat4 rotate2 = ft_mat4_mult(ft_mat4_rotate_z(-e->test.sphere.rotation.z), ft_mat4_mult(ft_mat4_rotate_y(-e->test.sphere.rotation.y), ft_mat4_rotate_x(-e->test.sphere.rotation.x)));

	ft_printf("rotate inv\n");
	ft_print_mat4(rotate2);
	
	ft_printf("translate inv\n");
	ft_print_mat4(translate2);
	
	ft_printf("scale inv\n");
	ft_print_mat4(scale2);

	ft_printf("IDENTITIES\n");
	ft_print_mat4(ft_mat4_mult(rotate, rotate2));
	ft_print_mat4(ft_mat4_mult(scale, scale2));
	ft_print_mat4(ft_mat4_mult(translate, translate2));

	t_mat4 invtransform = ft_mat4_model_view_matrix_mat(scale2, translate2, rotate2);
	
	ft_printf("TRANSFORM\n");
	ft_print_mat4(transform);
	
	ft_printf("INVERSE POS\n");
	ft_print_mat4(invtransform);

	ft_printf("TRANSFORM * INVERSE\n");
	ft_print_mat4(ft_mat4_mult(invtransform, transform));

	t_mat4 transform_dir = ft_mat4_mult(scale, rotate);
	t_mat4 transform_dir_inv = ft_mat4_mult(scale2, rotate2);

	ft_printf("INVERSE DIR \n");
	ft_print_mat4(transform_dir_inv);
	
	ft_printf("TRANSFORM * INVERSE\n");
	ft_print_mat4(ft_mat4_mult(transform_dir_inv, transform_dir));

	e->test.transform_pos = transform;
	e->test.transform_pos_inv = invtransform;

	e->test.transform_dir = transform_dir;
	e->test.transform_dir_inv = transform_dir_inv;
}

void	ft_render_test(t_env *e)
{
	t_ray	ray;
	e->cam.fov = (70 * M_PI) / 180.0;
	double a;
	double b;
	double c;
	double t;
	double px;
	double py;

	double image_ratio = (float)e->dim.width / (float)e->dim.height;

	int *pix;
	SDL_LockSurface(e->sdl.surface);
	pix = (int *)e->sdl.surface->pixels;
	e->cam.position = ft_new_vec3(5, 0, 0);
	int i;
	int j;
	ray.position = e->cam.position;
	i = 0;
	while (i < e->sdl.screen.h)
	{
		j = 0;
		while (j < e->sdl.screen.w)
		{
			px = (2 * ((j + 0.5) / e->dim.width) - 1) * tan(e->cam.fov / 2) * image_ratio;
			py = (1 - 2 * (i + 0.5) / e->dim.height) * tan(e->cam.fov / 2);

			ray.position = ft_vec3_mat4_mult(e->cam.position, e->test.transform_pos_inv);
			ray.direction = ft_vec3_mat4_mult(ft_new_vec3(px, py, 1), e->test.transform_dir_inv);
			ft_vec3_normalize(&(ray.direction));
			//ray.direction = ft_vec3_cmp(ray.direction, ray.position);

			a = (ray.direction.x * ray.direction.x) + (ray.direction.y * ray.direction.y) + (ray.direction.z * ray.direction.z);
			b = 2 * ((ray.position.x * ray.direction.x) + (ray.position.y * ray.direction.y) + (ray.position.z * ray.direction.z));
			c = (ray.position.x * ray.position.x) + (ray.position.y * ray.position.y) + (ray.position.z * ray.position.z) - (e->test.sphere.radius * e->test.sphere.radius);
			
			t = (-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a);
		
			if (t >= 0)
			{
				//pix[e->sdl.screen.w * i + j] = (int)(t * 10000) % 0xffffff;
				pix[e->sdl.screen.w * i + j] = e->test.sphere.color;
			}
			else
			{
				t = (-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a);
				if (t >= 0)
					pix[e->sdl.screen.w * i + j] = e->test.sphere.color;
			}
			j++;
		}
		i++;
	}
	if (!(e->sdl.texture = SDL_CreateTextureFromSurface(e->sdl.renderer,
			e->sdl.surface)))
		exit(1);
	SDL_UnlockSurface(e->sdl.surface);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &(e->sdl.screen));
	SDL_RenderPresent(e->sdl.renderer);
	SDL_DestroyTexture(e->sdl.texture);
}

void	ft_loop(t_env *e)
{
	int end;
	SDL_Event event;
	ft_init_test(e);
	ft_render_test(e);
	ft_printf("ON EST SORTI\n");	
	end = 0;
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
		/*
		ft_process(e);
		ft_render(e);
		*/
		SDL_Delay(12);
	}
	ft_printf("lool\n");
}
