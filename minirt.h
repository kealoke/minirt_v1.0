#ifndef MINIRT_H
#define MINIRT_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <float.h>
#include <math.h>
#include <mlx.h>

#include "struct.h"
#include "./input/input.h"
#include "errmsg.h"
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"


#define WIDTH 800
#define HEIGHT 800

#define EPSILON 1.0/128.0

#define BACK_COLOR 0x00000000


//描写に必要な全体の情報をもつ
//2: t_ambient amb -> 自然光情報
//3: t_camera cam -> カメラ情報
//4: t_light light -> 光源情報
//5: t_objects objs -> 描写する物体情報
typedef struct s_minirt
{
  t_ambient *amb;
  t_camera *cam;
  t_light *light;
  t_objects *objs;

}t_minirt;

void printErrAndExit(char *msg);

double		ft_atod(char *str);
int stringToInt(char **str);
bool isMatch(char *s1, char *s2);

bool inputCheck(int argc, char **argv);
bool checkVecRange(t_vec vec);
void parseLine(char *line, t_minirt *world, t_read_flag *flag);
void openAndRead(char *file, t_minirt *world);
void setVec(char *str, t_vec *vec);
bool setRGBcolor(char *str, t_color *color);
bool setRGBcolor(char *str, t_color *color);
void setAmbient(char **token, t_minirt *world, t_read_flag *flag);
void setCamera(char **token, t_minirt *world, t_read_flag *flag);
void setLight(char **token, t_minirt *world, t_read_flag *flag);
void setSphere(char **token, t_minirt *world, t_read_flag *flag);
void setPlane(char **token, t_minirt *world, t_read_flag *flag);
void setCylinder(char **token, t_minirt *world, t_read_flag *flag);
void *my_malloc(size_t size);

t_objects *objnew(void *content);
int get_obj_size(t_objects *list);
void	ob_lstadd_back(t_objects **lst, t_objects *new);

int	close_win(t_mlx *data);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	ob_lstadd_back(t_objects **lst, t_objects *new);

bool	draw(t_minirt *world, t_mlx *mlx);


double	InnerProduct(t_vec a, t_vec b);
t_vec	crossProduct(t_vec a, t_vec b);
t_vec	add_vec(t_vec a, t_vec b);
t_vec	sub_vec(t_vec a, t_vec b);
t_vec	mul_vec(t_vec a, double b);
double	norm_vec(t_vec a);
t_vec	vec_normalize(t_vec a);

t_color sca_mul_color(t_color a, double b);
t_color mul_color(t_color a, t_color b);
t_color add_color(t_color a, t_color b);
int	argb_to_hex(t_color color);
t_color get_color_vec(unsigned int red, unsigned int green, unsigned int blue);

double	get_test_condition(double a, double b, double c);
t_vec_info	pl_intersection(t_minirt *world, t_objects tmp_o_list, t_ray ray);
t_vec_info	sp_intersection(t_minirt *world, t_objects tmp_o_list, t_ray ray);
t_vec_info cy_intersecton(t_minirt *world, t_objects tmp_o_list, t_ray ray);
#endif