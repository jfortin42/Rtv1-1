/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:17:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/22 20:57:53 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_set_dimensions(t_env *e)
{
	e->sdl.screen.x = 0;
	e->sdl.screen.y = 0;
	if (e->mode == 1)
	{
		e->sdl.screen.w = 240;
		e->sdl.screen.h = 180;
	}
	else
	{
		e->sdl.screen.w = 1280;
		e->sdl.screen.h = 720;
	}
}

int		ft_init_sdl(t_env *e)
{
	ft_set_dimensions(e);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	if (!(e->sdl.window = SDL_CreateWindow("rtv1", e->sdl.screen.x,
					e->sdl.screen.y, e->sdl.screen.w, e->sdl.screen.h, 0)))
		return (0);
	e->sdl.renderer = SDL_CreateRenderer(e->sdl.window, -1, 0);
	if (!(e->sdl.surface = SDL_CreateRGBSurface(0, e->sdl.screen.w,
					e->sdl.screen.h, 32, 0, 0, 0, 0)))
		return (0);
	if (e->sdl.renderer == NULL)
		return (0);
	if (SDL_RenderSetLogicalSize(e->sdl.renderer, e->sdl.screen.w,
				e->sdl.screen.h) < 0)
		return (0);
	if (SDL_SetRenderDrawColor(e->sdl.renderer, 0, 0, 0, 255) < 0)
		return (0);
	if (e->mode == 1)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}

int		ft_init_all(t_env *e)
{
	if (!ft_init_sdl(e))
		return (0);
	ft_init_scene(e);
	return (1);
}
