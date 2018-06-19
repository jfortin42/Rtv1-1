#ifndef FT_RTV1_H
# define FT_RTV1_H

# include <SDL.h>
# include "libft.h"
# include "libmat.h"
# include "objects.h"
# include <fcntl.h>
# define EPSILON 0.01
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
	int				x;
	int				y;
}					t_ray;

typedef struct		 s_sdl
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Rect		screen;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}					t_sdl;

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
	t_object_union	object_union;
	t_vec3			scale;
	t_vec3			rotation;
	t_vec3			position;
	int				color;
	float			shininess;
	float			smoothness;
	t_mat4			transform_pos;
	t_mat4			transform_pos_inv;
	t_mat4			transform_dir;
	t_mat4			transform_dir_inv;
	float			(*intersect_func)(t_ray, t_object *);
	t_vec3			(*normal_func)(t_vec3, t_object *);
};

typedef struct		s_hit
{
	t_object		*object;
	float			t;
	t_vec3			point;
	t_vec3			normal;
	t_vec3			world_point;
	t_vec3			world_normal;
	int				color;
}					t_hit;

typedef struct		s_spot
{
	t_vec3			position;
}					t_spot;

typedef struct		s_env 
{
	t_sdl			sdl;
	t_keys			keys;
	t_camera		cam;
	int				scene;
	int				mode;
	float			ambiant_coefficient;
	float			speed;
	t_list			*objects;
	t_list			*spots;
	t_object		*selected_object;
}					t_env;

int							ft_init_all(t_env *e);
void						ft_init_scene(t_env *e);
void						ft_loop(t_env *e);
void						ft_process(t_env *e);
void						ft_render(t_env *e);
void						ft_compute_matrix(t_object *object);
void						ft_compute_matrices_list(t_list *objects);
int							ft_intersect_objects(t_list *objects, t_ray ray, t_object *except);
int							ft_color_add(int color, float to_add);
int							ft_get_color_reduction(int color, float reduc);



void						ft_keys_down(t_env *e, SDL_Event event);
void						ft_keys_up(t_env *e, SDL_Event event);
void						ft_mouse_motion(t_env *e, SDL_Event event);

t_object					*ft_new_sphere(float radius, t_vec3 pos,
								t_vec3 rot, int color);
t_object					*ft_new_plane(t_vec3 pos,
								t_vec3 rot, int color);
t_object					*ft_new_cylinder(float radius, t_vec3 pos,
								t_vec3 rot, int color);
t_object					*ft_new_cone(float angle, t_vec3 pos,
								t_vec3 rot, int color);
float						ft_intersect_sphere(t_ray ray, t_object *object);
float						ft_intersect_cone(t_ray ray, t_object *object);
float						ft_intersect_cylinder(t_ray ray, t_object *object);
float						ft_intersect_plane(t_ray ray, t_object *object);
float						ft_min_pos(float a, float b);
t_vec3						ft_normal_sphere(t_vec3 point, t_object *obj);
t_vec3						ft_normal_plane(t_vec3 point, t_object *obj);
t_vec3						ft_normal_cylinder(t_vec3 point, t_object *obj);
t_vec3						ft_normal_cone(t_vec3 point, t_object *obj);
#endif
