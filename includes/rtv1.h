#ifndef FT_RTV1_H
# define FT_RTV1_H

# include <SDL.h>
# include "libft.h"
# include "libmat.h"
# include "objects.h"
# include <fcntl.h>

typedef struct	s_object	t_object;

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
	int			key_e;
	int			key_q;
	int			key_ctrl;
	int			key_space;
	int			key_shift;
}				t_keys;

typedef struct		s_ray
{
	t_vec3			position;
	t_vec3			direction;
}					t_ray;

typedef struct		 s_sdl
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Rect		screen;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}					t_sdl;

typedef struct		s_dim
{
	int				width;
	int				height;
}					t_dim;

typedef struct 		s_test
{
	t_sphere		sphere;
	t_camera		camera;
	t_mat4			transform_pos;
	t_mat4			transform_pos_inv;
	t_mat4			transform_dir;
	t_mat4			transform_dir_inv;
	float			left;
	float			right;
	float			top;
	float			bottom;
}					t_test;

typedef struct		s_intersect
{
	int				color;
	t_vec3			intersection;
	t_vec3			normal;
	float			t;
}					t_intersect;

typedef enum	e_object_enum
{
	e_sphere,
	e_cone,
	e_plane,
	e_cylinder
}				t_object_enum;

typedef union		u_object_union
{
	t_sphere		sphere;
	t_cone			cone;
	t_plane			plane;
	t_cylinder		cylinder;
}					t_object_union;

struct				s_object
{
	t_object_enum	object_enum;
	t_object_union	object_union;
	t_vec3			scale;
	t_vec3			rotation;
	t_vec3			position;
	int				color;
	t_mat4			transform_pos;
	t_mat4			transform_pos_inv;
	t_mat4			transform_dir;
	t_mat4			transform_dir_inv;
	t_intersect		(*intersect_func)(t_ray, t_object *);
};

typedef struct		s_spot
{
	t_vec3			position;
}					t_spot;

typedef struct		s_env 
{
	t_sdl			sdl;
	t_dim			dim;
	t_keys			keys;
	t_test			test;
	t_camera		cam;
	float			ambiant_coefficient;
	float			speed;
	int				mode;
	t_list			*objects;
	t_list			*spots;
	t_object		*selected_object;
}					t_env;

int					ft_init_all(t_env *e);
void				ft_loop(t_env *e);
void				ft_loop(t_env *e);
void				ft_keys_down(t_env *e, SDL_Event event);
void				ft_keys_up(t_env *e, SDL_Event event);
void				ft_mouse_motion(t_env *e, SDL_Event event);
void				ft_loop(t_env *e);
#endif
