#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include "errmsg.h"
# include "struct.h"

# define WIDTH 800
# define HEIGHT 800

# define EPSILON 1.0 / 128.0

# define BACK_COLOR 0x00000000

# define AMB_K 1
# define DIFF_K 1
# define SUP_K 1

# define ESC 53

//描写に必要な全体の情報をもつ
//2: t_ambient amb -> 自然光情報
//3: t_camera cam -> カメラ情報
//4: t_light light -> 光源情報
//5: t_objects objs -> 描写する物体情報
typedef struct s_minirt
{
  t_mlx     mlx;
	t_ambient	*amb;
	t_camera	*cam;
	t_light		*light;
	t_objects	*objs;

}				t_minirt;

void			err_and_exit(char *msg);
int       input_error(char *msg);

double		ft_atod(char *str);
int				string_to_int(char **str);
bool			is_match(char *s1, char *s2);

bool			input_check(int argc, char **argv);
bool			check_vec_range(t_vec vec);
void			parse_line(char *line, t_minirt *world, t_read_flag *flag);
void			open_and_read(char *file, t_minirt *world);
void			set_vec(char *str, t_vec *vec);
bool			set_rgb_color(char *str, t_color *color);
void			set_ambient(char **token, t_minirt *world, t_read_flag *flag);
void			set_camera(char **token, t_minirt *world, t_read_flag *flag);
void			set_light(char **token, t_minirt *world, t_read_flag *flag);
void			set_sphere(char **token, t_minirt *world, t_read_flag *flag);
void			set_plane(char **token, t_minirt *world, t_read_flag *flag);
void			set_cylinder(char **token, t_minirt *world, t_read_flag *flag);
void			*my_malloc(size_t size);
double	get_number(char *str, int *i, int *j);

t_objects		*objnew(void *content);
int				get_obj_size(t_objects *list);
void			ob_lstadd_back(t_objects **lst, t_objects *new);

int				close_win(t_mlx *data);
int				key(int key_code, t_mlx *mlx);
void			my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void			set_mlx(t_mlx *mlx);

double			inner_product(t_vec a, t_vec b);
t_vec			cross_product(t_vec a, t_vec b);
t_vec			add_vec(t_vec a, t_vec b);
t_vec			sub_vec(t_vec a, t_vec b);
t_vec			mul_vec(t_vec a, double b);
double			norm_vec(t_vec a);
t_vec			vec_normalize(t_vec a);

t_color			sca_mul_color(t_color a, double b);
t_color			mul_color(t_color a, t_color b);
t_color			add_color(t_color a, t_color b);
int				argb_to_hex(t_color color);

bool			render(t_minirt *world);

double			get_test_condition(double a, double b, double c);
t_vec_info		pl_intersection(t_minirt *world, t_objects tmp_o_list,
					t_ray ray);
t_vec_info		sp_intersection(t_minirt *world, t_objects tmp_o_list,
					t_ray ray);
t_vec_info		cy_intersecton(t_minirt *world, t_objects tmp_o_list,
					t_ray ray);
t_vec_info		calc_intersection(t_minirt *world, t_objects node, t_ray ray);
t_vec_info		get_intersection(t_minirt *world, t_ray ray);

int	get_color(t_minirt *world, t_vec_info closest_obj, t_ray ray, double ra);
double			get_ambient(t_minirt *world);
double			get_diffuse(t_minirt *world, t_vec_info closest_obj);
double			get_supecular(t_minirt *world, t_vec_info closest_obj,
					t_vec dir_vec);
bool			check_shadow(t_minirt *world, t_vec_info obj);
#endif