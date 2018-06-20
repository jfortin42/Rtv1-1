/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/20 19:59:10 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_get_events(t_env *e, int *end)
{
	SDL_Event	event;
	int			a;

	a = 0;
	while (SDL_PollEvent(&event))
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE
				|| (event.key.keysym.sym == SDLK_ESCAPE
					&& event.type == SDL_KEYDOWN))
			*end = 1;
		if (event.type == SDL_KEYDOWN)
			ft_keys_down(e, event);
		if (event.type == SDL_KEYUP)
			ft_keys_up(e, event);
		if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(e, event);
		a = 1;
	}
	return (a);
}

void	ft_loop(t_env *e)
{
	int			end;

	ft_render(e);
	end = 0;
	while (!end)
	{
		if (ft_get_events(e, &end) && e->mode == 1)
		{
			ft_process(e);
			ft_render(e);
		}
		SDL_Delay(12);
	}
}
