/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:40:09 by aherriau          #+#    #+#             */
/*   Updated: 2018/04/16 22:27:21 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <SDL2/SDL.h>
# include "../libmath/libmath.h"

typedef struct		s_sdl
{
	SDL_Rect		screen;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
}					t_sdl;

typedef struct		s_env
{
	t_sdl			sdl;
}					t_env;

#endif
