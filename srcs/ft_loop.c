/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/09 05:54:14 by ldedier          ###   ########.fr       */
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
	e->test.sphere = ft_new_sphere(5.f, ft_new_vec3(0.0f, 0.f, 0.f),
		ft_new_vec3(0.0, 0.0, 0.0f), ft_new_vec3(1.f, 1.f, 1.f));
	
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
	
	ft_printf("INVERSE\n");
	ft_print_mat4(invtransform);
	
	ft_printf("TRANSFORM * INVERSE\n");
	ft_print_mat4(ft_mat4_mult(invtransform, transform));


	t_mat4 transform_dir = ft_mat4_mult(scale, rotate);
	t_mat4 transform_dir_inv = ft_mat4_mult(scale2, rotate2);




	ft_printf("TRANSFORM * INVERSE\n");
	ft_print_mat4(ft_mat4_mult(transform_dir_inv, transform_dir));

	printf("%d\n", e->dim.width);
	printf("%d\n", e->dim.height);
	
	e->test.transform_pos = transform;
	e->test.transform_pos_inv = invtransform;

	e->test.transform_dir = transform_dir;
	e->test.transform_dir_inv = transform_dir_inv;

	e->test.top = -9;
	e->test.bottom = 9;
	e->test.left = -16;
	e->test.right = 16;
}

void	ft_render_test(t_env *e)
{
	t_ray	ray;
	float dx;
	float dy;

	float a;
	float b;
	float c;
	float t;

	dx = (e->test.right * 2) / e->dim.width;
	dy = (e->test.bottom * 2) / e->dim.height;

	t_vec3 screen_plane;
	
	int *pix;
	pix = (int *)e->sdl.surface->pixels;
	e->cam.position = ft_new_vec3(5, 0, -10);
	int i;
	int j;

	ray.position = e->cam.position;
	ft_print_vec3(ray.position);
	c = (ray.position.x * ray.position.x) + (ray.position.y * ray.position.y) + (ray.position.z * ray.position.z) - (e->test.sphere.radius * e->test.sphere.radius);
	i = 0;
	while (i < e->sdl.screen.h)
	{
		j = 0;
		while (j < e->sdl.screen.w)
		{
			screen_plane.x = e->test.left + (dx / 2.0) + j * dx;
			screen_plane.y = e->test.top + (dy / 2.0 ) + i * dy;
			screen_plane.z = 16; //DETERMINED BY LEFT/TOP ??
	
		//	ray.direction = ft_vec3_add(screen_plane, ray.position);
			ray.direction = screen_plane;
			ft_vec3_normalize(&(ray.direction));
			/*
			if (i + j == 0)	
			{
				ft_print_mat4(e->test.transform_pos_inv);
				printf("position avant tranformation\n");
				ft_print_vec3(ray.position);
				printf("direction avant tranformation\n");
				ft_print_vec3(ray.direction);
			}
			ray.direction = ft_vec3_mat4_mult(ray.direction, e->test.transform_dir_inv);
			//ft_vec3_normalize(&(ray.direction));
			ray.position = ft_vec3_mat4_mult(ray.position, e->test.transform_pos_inv);
			if (i + j == 0)	
			{
				printf("position apres tranformation\n");
				ft_print_vec3(ray.position);
				printf("direction apres tranformation\n");
				ft_print_vec3(ray.direction);
			}
			*/
			if(i + j == 0)
			{
				printf("screen plane\n");
				ft_print_vec3(screen_plane);

				printf("ray position\n");
				ft_print_vec3(ray.position);

				printf("ray direction\n");
				ft_print_vec3(ray.direction);
			}

			a = (ray.direction.x * ray.direction.x) + (ray.direction.y * ray.direction.y) + (ray.direction.z * ray.direction.z);
			b = 2 * ((ray.position.x * ray.direction.x) + (ray.position.y * ray.direction.y) + (ray.position.z * ray.direction.z));
			t = (-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a);
			if (t >= 0)
				pix[e->sdl.screen.w * i + j] = e->test.sphere.color;
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
