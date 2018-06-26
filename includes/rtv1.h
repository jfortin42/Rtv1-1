/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 22:02:04 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/26 18:08:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RTV1_H
# define FT_RTV1_H

# include <SDL.h>
# include "libft.h"
# include "libmat.h"
# include "objects.h"
# include <fcntl.h>

# define EPSILON 0.01

typedef struct s_object	t_object;

typedef struct		s_keys
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				key_o;
	int				key_p;
	int				key_7;
	int				key_8;
	int				key_5;
	int				key_4;
	int				key_2;
	int				key_1;
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_e;
	int				key_q;
	int				key_ctrl;
	int				key_space;
	int				key_shift;
}					t_keys;

typedef struct		s_ray
{
	t_vec3			position;
	t_vec3			direction;
	int				x;
	int				y;
}					t_ray;

typedef struct		s_phong
{
	float			diffuse_factor;
	float			specular_factor;
}					t_phong;

typedef struct		s_sdl
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

typedef enum		e_object_enum
{
	e_sphere,
	e_cone,
	e_plane,
	e_cylinder
}					t_object_enum;

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

typedef struct		s_auxcone
{
	float			cangle;
	float			sangle;
}					t_auxcone;

typedef enum		e_object_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE,
	CAMERA,
	AMBIANT,
	LIGHT
}					t_object_type;

typedef struct		s_parser
{
	int				nb_lines;
	int				parsed_object;
}					t_parser;

typedef struct		s_env
{
	t_sdl			sdl;
	t_keys			keys;
	t_camera		cam;
	int				scene;
	int				mode;
	float			ambiant_coefficient;
	float			speed;
	int				nb_objects;
	int				current_object;
	int				can_change;
	t_parser		parser;
	t_list			*objects;
	t_list			*spots;
	t_object		*selected_object;
}					t_env;

int					ft_init_all(t_env *e);
void				ft_init_scene(t_env *e);
void				ft_loop(t_env *e);
void				ft_process(t_env *e);
void				ft_render(t_env *e);
void				ft_compute_matrix(t_object *object);
void				ft_compute_matrices_list(t_list *objects);
int					ft_color_add(int color, float to_add);
int					ft_get_color_reduction(int color, float reduc);

void				ft_keys_down(t_env *e, SDL_Event event);
void				ft_keys_up(t_env *e, SDL_Event event);
void				ft_mouse_motion(t_env *e, SDL_Event event);

t_object			*ft_new_sphere(void);
t_object			*ft_new_cylinder(void);
t_object			*ft_new_plane(void);
t_object			*ft_new_cone(void);

float				ft_intersect_sphere(t_ray ray, t_object *object);
float				ft_intersect_cone(t_ray ray, t_object *object);
float				ft_intersect_cylinder(t_ray ray, t_object *object);
float				ft_intersect_plane(t_ray ray, t_object *object);
float				ft_min_pos(float a, float b);
t_vec3				ft_normal_sphere(t_vec3 point, t_object *obj);
t_vec3				ft_normal_plane(t_vec3 point, t_object *obj);
t_vec3				ft_normal_cylinder(t_vec3 point, t_object *obj);
t_vec3				ft_normal_cone(t_vec3 point, t_object *obj);

t_spot				*ft_new_spot(void);
void				ft_scene_3(t_env *e);
void				ft_scene_4(t_env *e);
void				ft_scene_5(t_env *e);
void				ft_scene_6(t_env *e);
t_hit				ft_trace(t_ray ray, t_env *e);
int					ft_parse(char *filename, t_env *e);
int					ft_parse_rot(char *str, t_env *e);
int					ft_parse_pos(char *str, t_env *e);
int					ft_parse_col(char *str, t_env *e);
int					ft_parse_angle(char *str, t_env *e);
int					ft_parse_radius(char *str, t_env *e);
int					ft_parse_shine(char *str, t_env *e);
int					ft_parse_smooth(char *str, t_env *e);
int					ft_parse_intensity(char *str, t_env *e);
float				ft_deg_to_rad(int deg);
#endif
