#ifndef FT_RTV1_H
# define FT_RTV1_H

# include <SDL.h>
# include "libft.h"
# include "libmat.h"
# include <fcntl.h>
typedef struct	s_keys
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			key_o;
	int			key_p;
	int			key_7;
	int			key_8;
	int			key_5;
	int			key_4;
	int			key_2;
	int			key_1;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_ctrl;
	int			key_space;
	int			key_shift;
}				t_keys;

typedef struct		 s_sdl
{
	SDL_Surface		*surface;
	SDL_Rect		screen;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}					t_sdl;

typedef struct		s_dim
{
	int				width;
	int				height;
}					t_dim;

typedef struct		s_env 
{
	t_sdl			sdl;
	t_dim			dim;
	t_keys			keys;
}					t_env;

int					ft_init_all(t_env *e);
void				ft_loop(t_env *e);
void				ft_loop(t_env *e);
void				ft_keys_down(t_env *e, SDL_Event event);
void				ft_keys_up(t_env *e, SDL_Event event);
void				ft_mouse_motion(t_env *e, SDL_Event event);
void				ft_loop(t_env *e);
#endif
