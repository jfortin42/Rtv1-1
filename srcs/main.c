/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:59:44 by aherriau          #+#    #+#             */
/*   Updated: 2018/04/17 00:43:38 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define W	1024
#define H	1024

int		ft_init(t_env *e)
{
	e->sdl.screen.x = 100;
	e->sdl.screen.y = 200;
	e->sdl.screen.w = W;
	e->sdl.screen.h = H;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	e->sdl.window = SDL_CreateWindow("RTv1", e->sdl.screen.x, e->sdl.screen.y,
			e->sdl.screen.w, e->sdl.screen.h, 0);
	if (e->sdl.window == NULL)
		return (0);
	e->sdl.renderer = SDL_CreateRenderer(e->sdl.window, -1, 0);
	if (e->sdl.renderer == NULL)
		return (0);
	if (SDL_RenderSetLogicalSize(e->sdl.renderer, e->sdl.screen.w,
				e->sdl.screen.h) < 0)
		return (0);
	if (SDL_SetRenderDrawColor(e->sdl.renderer, 0, 0, 0, 255) < 0)
		return (0);
	e->sdl.surface = SDL_CreateRGBSurface(0, W, H, 32, 0, 0, 0, 0);
	if (e->sdl.surface == NULL)
		return (0);
	return (1);
}

void	ft_render(t_env *e)
{
	int		y;
	int		x;
	int		*surface;
	int		color;
	int		x_left;
	int		x_right;
	int		y_top;
	int		y_bottom;
	float	dx;
	float	dy;
	t_v3d	point;
	t_v3d	ray_ori;
	t_v3d	ray_dir;
	t_v3d	cam_pos;
	//float	a;
	float	b;
	float	c;
	float	delta;
	t_v3d	sphere_center;
	float	sphere_radius;

	cam_pos = ft_new_v3d(0.0f, 0.0f, -10.0f);
	x_left = -10;
	x_right = 10;
	y_top = 10;
	y_bottom = -10;
	dx = (x_right - x_left) / (float)W;
	dy = (y_top - y_bottom) / (float)H;

	sphere_center = ft_new_v3d(0.0f, 0.0f, 10.0f);
	sphere_radius = 10;

	surface = (int *)(e->sdl.surface->pixels);
	y = 0;
	while (y < e->sdl.screen.h)
	{
		x = 0;
		while (x < e->sdl.screen.w)
		{
			point.x = x_left + 0.5 * dx + x * dx;
			point.y = y_top - 0.5 * dy - y * dy;
			point.z = 0;

			ray_ori = cam_pos;
			ray_dir = ft_minus_new_v3d(point, ray_ori);
			ft_normalize_v3d(&ray_dir);
			//a = ft_square_length_v3d(ray_dir);
			b = 2 * (ray_dir.x * (ray_ori.x - sphere_center.x) +
					ray_dir.y * (ray_ori.y - sphere_center.y) +
					ray_dir.z * (ray_ori.z - sphere_center.z));
			c = (ray_ori.x - sphere_center.x) * (ray_ori.x - sphere_center.x) +
				(ray_ori.y - sphere_center.y) * (ray_ori.y - sphere_center.y) +
				(ray_ori.z - sphere_center.z) * (ray_ori.z - sphere_center.z) -
				sphere_radius * sphere_radius ;
			delta = b * b - 4 * c;
			if (x == 120 && y == 90)
				printf("(%f, %f, %f)  b:%f, c:%f, delta:%f\n", point.x, point.y, point.z, b, c, delta);
			if (delta > 0)
				color = 0xff0000;
			else
				color = 0x000000;
			surface[y * W + x] = color;
			x++;
		}
		y++;
	}
}

void	ft_process(t_env *e, int *running)
{
	SDL_Event	event;
	SDL_Rect	rect;

	while (SDL_PollEvent(&event))
	{
		if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN &&
					event.key.keysym.sym == SDLK_ESCAPE))
			*running = 0;
	}
	//SDL_LockSurface(e->sdl.surface);
	ft_render(e);
	//SDL_UnlockSurface(e->sdl.surface);
	e->sdl.texture = SDL_CreateTextureFromSurface(e->sdl.renderer, e->sdl.surface);
	// test if return NULL, exit
	SDL_FillRect(e->sdl.surface, NULL, 0x000000);
	rect.x = 0;
	rect.y = 0;
	rect.w = W;
	rect.h = H;
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &rect);
	SDL_DestroyTexture(e->sdl.texture);
}

int		main(void)
{
	t_env		e;
	int			running;

	if (!ft_init(&e))
		return (1);
	running = 1;
	while (running)
	{
		ft_process(&e, &running);
		SDL_RenderPresent(e.sdl.renderer);
		SDL_Delay(16);
		//SDL_Delay(10);
	}
	SDL_DestroyWindow(e.sdl.window);
	//ft_free_sdl(&e);
	SDL_Quit();
	return (0);
}
