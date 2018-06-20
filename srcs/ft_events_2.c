/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 21:45:42 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/20 21:46:03 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_keys_up_3(t_env *e, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_KP_2)
		e->keys.key_2 = 0;
	else if (event.key.keysym.sym == SDLK_KP_4)
		e->keys.key_4 = 0;
	else if (event.key.keysym.sym == SDLK_KP_5)
		e->keys.key_5 = 0;
	else if (event.key.keysym.sym == SDLK_KP_7)
		e->keys.key_7 = 0;
	else if (event.key.keysym.sym == SDLK_KP_8)
		e->keys.key_8 = 0;
	else if (event.key.keysym.sym == SDLK_o)
		e->keys.key_o = 0;
	else if (event.key.keysym.sym == SDLK_p)
		e->keys.key_p = 0;
	else if (event.key.keysym.sym == SDLK_LCTRL)
		e->keys.key_ctrl = 0;
	else if (event.key.keysym.sym == SDLK_SPACE)
		e->keys.key_space = 0;
	else if (event.key.keysym.sym == SDLK_LSHIFT)
		e->speed = 0.2;
}

void	ft_keys_up_2(t_env *e, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_KP_5)
		e->keys.key_5 = 0;
	else if (event.key.keysym.sym == SDLK_KP_4)
		e->keys.key_4 = 0;
	else if (event.key.keysym.sym == SDLK_KP_2)
		e->keys.key_2 = 0;
	else if (event.key.keysym.sym == SDLK_KP_1)
		e->keys.key_1 = 0;
	else if (event.key.keysym.sym == SDLK_w)
		e->keys.key_w = 0;
	else if (event.key.keysym.sym == SDLK_a)
		e->keys.key_a = 0;
	else if (event.key.keysym.sym == SDLK_s)
		e->keys.key_s = 0;
	else if (event.key.keysym.sym == SDLK_d)
		e->keys.key_d = 0;
	else if (event.key.keysym.sym == SDLK_q)
		e->keys.key_q = 0;
	else if (event.key.keysym.sym == SDLK_e)
		e->keys.key_e = 0;
	else if (event.key.keysym.sym == SDLK_KP_1)
		e->keys.key_1 = 0;
	else
		ft_keys_up_3(e, event);
}

void	ft_keys_up(t_env *e, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
		e->keys.up = 0;
	else if (event.key.keysym.sym == SDLK_DOWN)
		e->keys.down = 0;
	else if (event.key.keysym.sym == SDLK_RIGHT)
		e->keys.right = 0;
	else if (event.key.keysym.sym == SDLK_LEFT)
		e->keys.left = 0;
	else if (event.key.keysym.sym == SDLK_p)
	{
		e->keys.key_p = 0;
		e->can_change = 1;
	}
	else if (event.key.keysym.sym == SDLK_o)
	{
		e->keys.key_o = 0;
		e->can_change = 1;
	}
	else if (event.key.keysym.sym == SDLK_KP_8)
		e->keys.key_8 = 0;
	else if (event.key.keysym.sym == SDLK_KP_7)
		e->keys.key_7 = 0;
	else
		ft_keys_up_2(e, event);
}
