#include "../minirt.h"

// tokenからt_sphere構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
void setSphere(char **token, t_minirt *world, t_read_flag *flag)
{
  t_sphere *sp;
  t_objects *obj;

  if(!token[1] || !token[2] || !token[3])
    printErrAndExit("Sphere value is not enough\n");
  sp = my_malloc (sizeof(t_sphere));
  setVec(token[1], &(sp->center_vec));
  sp->diameter = ft_atod(token[2]);
  setRGBcolor(token[3], &(sp->color));
  obj = objnew(sp);
  obj->obj_type = t_sp;
  ob_lstadd_back(&(world->objs), obj);
  flag->obj_f = true;
}

// tokenからt_plane構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
void setPlane(char **token, t_minirt *world, t_read_flag *flag)
{
  bool rgb_flag;
  t_plane *pl;
  t_objects *obj;

  if(!token[1] || !token[2] || !token[3])
    printErrAndExit("Plane value is not enough\n");
  pl = my_malloc(sizeof(t_plane));
  setVec(token[1], &(pl->pos_vec));
  setVec(token[2], &(pl->normal_vec));
  if (checkVecRange(pl->normal_vec) == false)
    printErrAndExit(PLANE_VEC_ERR);
  rgb_flag = setRGBcolor(token[3], &(pl->color));
  if (flag == false)
    printErrAndExit(PLANE_COLOR_ERR);
  obj = objnew(pl);
  obj->obj_type = t_pl;
  ob_lstadd_back(&(world->objs), obj);
  flag->obj_f = true;
}

// tokenからt_cylinder構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
void setCylinder(char **token, t_minirt *world, t_read_flag *flag)
{
  bool rgb_flag;
  t_cylinder *cy;
  t_objects *obj;

  if(!token[1] || !token[2] || !token[3] || !token[4] || !token[5])
    printErrAndExit("Cylinder value is not enough\n");
  cy = my_malloc(sizeof(t_cylinder));
  setVec(token[1], &(cy->center_vec));
  setVec(token[2], &(cy->axis_vec));
  if (checkVecRange(cy->axis_vec) == false)
    printErrAndExit(CY_AXIS_VEC_ERR);
  cy->diameter = ft_atod(token[3]);
  cy->height = ft_atod(token[4]);
  rgb_flag = setRGBcolor(token[5], &(cy->color));
  if (rgb_flag == false)
    printErrAndExit(CY_COLOR_ERR);
  obj = objnew(cy);
  obj->obj_type = t_cy;
  ob_lstadd_back(&(world->objs), obj);
  flag->obj_f = true;
}
