/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/03 22:36:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_render(t_env *e)
{
	SDL_SetRenderDrawColor(e->sdl.renderer, 150,200,0,0);
	SDL_RenderClear(e->sdl.renderer);
	SDL_RenderPresent(e->sdl.renderer);
	(void)e;
}

void	ft_process(t_env *e)
{
	(void)e;
}

void	ft_loop(t_env *e)
{
	int end;
	SDL_Event event;

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
		ft_process(e);
		ft_render(e);
		SDL_Delay(12);
	}
}
