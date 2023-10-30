#include "../minirt.h"

// tokenからt_sphere構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *scene -> 変換した値を入れるminirt構造体
void setSphere(char **token, t_minirt *scene)
{
  if (scene->objs == NULL)
    scene->objs = my_malloc(sizeof(t_objects));
  scene->objs->sp = my_malloc(sizeof(t_sphere));
  setVec(token[1], &(scene->objs->sp->center_vec));
  scene->objs->sp->diameter = ft_atod(token[2]);
  setRGBcolor(token[3], &(scene->objs->sp->color));
}

// tokenからt_plane構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *scene -> 変換した値を入れるminirt構造体
void setPlane(char **token, t_minirt *scene)
{
  bool flag;
  if (scene->objs == NULL)
    scene->objs = my_malloc(sizeof(t_objects));
  scene->objs->pl = my_malloc(sizeof(t_plane));
  setVec(token[1], &(scene->objs->pl->point_vec));
  setVec(token[2], &(scene->objs->pl->normal_vec));
  if (checkVecRange(scene->objs->pl->normal_vec) == false)
    printErrAndExit(PLANE_VEC_ERR);

  flag = setRGBcolor(token[3], &(scene->objs->pl->color));
  if (flag == false)
    printErrAndExit(PLANE_COLOR_ERR);
}

// tokenからt_cylinder構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *scene -> 変換した値を入れるminirt構造体
void setCylinder(char **token, t_minirt *scene)
{
  bool flag;
  if (scene->objs == NULL)
    scene->objs = my_malloc(sizeof(t_objects));
  scene->objs->cy = my_malloc(sizeof(t_cylinder));
  setVec(token[1], &(scene->objs->cy->center_vec));
  setVec(token[2], &(scene->objs->cy->axis_vec));
  if (checkVecRange(scene->objs->cy->axis_vec) == false)
    printErrAndExit(CY_AXIS_VEC_ERR);
  scene->objs->cy->diameter = ft_atod(token[3]);
  scene->objs->cy->height = ft_atod(token[4]);
  flag = setRGBcolor(token[5], &(scene->objs->cy->color));
  if (flag == false)
    printErrAndExit(CY_COLOR_ERR);
}