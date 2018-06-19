/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/19 13:18:50 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_get_events(t_env *e, int *end)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
			ft_keys_down(e, event);
		if (event.type == SDL_KEYUP)
			ft_keys_up(e, event);
		if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(e, event);
		if (event.window.event == SDL_WINDOWEVENT_CLOSE
				|| (event.key.keysym.sym == SDLK_ESCAPE
					&& event.type == SDL_KEYDOWN))
			*end = 1;
	}
}

void	ft_loop(t_env *e)
{
	int			end;

	ft_render(e);
	end = 0;
	while (!end)
	{
		ft_get_events(e, &end);
		if (e->mode == 1)
		{
			ft_process(e);
			ft_render(e);
		}
		SDL_Delay(12);
	}
}
