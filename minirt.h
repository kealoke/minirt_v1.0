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


#define WIDTH 600
#define HEIGHT 600


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
void parseLine(char *line, t_minirt *global_info, t_read_flag *flag);
void openAndRead(char *file, t_minirt *global_info);
void setVec(char *str, t_vec *vec);
bool setRGBcolor(char *str, t_color *color);
bool setRGBcolor(char *str, t_color *color);
void setAmbient(char **token, t_minirt *global_info, t_read_flag *flag);
void setCamera(char **token, t_minirt *global_info, t_read_flag *flag);
void setLight(char **token, t_minirt *global_info, t_read_flag *flag);
void setSphere(char **token, t_minirt *global_info, t_read_flag *flag);
void setPlane(char **token, t_minirt *global_info, t_read_flag *flag);
void setCylinder(char **token, t_minirt *global_info, t_read_flag *flag);
void *my_malloc(size_t size);

t_objects *objnew(void *content);
int get_obj_size(t_objects *list);
void	ob_lstadd_back(t_objects **lst, t_objects *new);

int	close_win(t_mlx *data);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	ob_lstadd_back(t_objects **lst, t_objects *new);

bool	draw(t_minirt *global_info, t_mlx *mlx);
bool	draw2(t_minirt *global_info, t_mlx *mlx);
#endif