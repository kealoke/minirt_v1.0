#include "../minirt.h"

// 文字列をvec構造体に変換する関数
// 1: char *str -> 変換したい文字列[x,y,z]
// 2: t_vec *vec -> 変換後の値を入れる構造体
void setVec(char *str, t_vec *vec)
{
  char *tmp;
  int i;
  int j;

  i = 0;
  j = 0;
  tmp = NULL;
  if (!str)
    return;
  while (str[j] && str[j] != ',')
    j++;
  tmp = ft_substr(str, i, j);
  vec->x = ft_atod(tmp);
  free(tmp);
  i = j;
  while (str[j] && str[j] != ',')
    j++;
  tmp = ft_substr(str, i + 1, j - i);
  vec->y = ft_atod(tmp);
  free(tmp);
  i = j;
  while (str[j])
    j++;
  tmp = ft_substr(str, i + 1, j - i);
  vec->z = ft_atod(tmp);
  free(tmp);
}

// 文字列をRGB構造体に変換する関数
// return : 値が[0,255]の範囲ならtrue それ以外はfalseを返す
// 1: char *str -> 変換したい文字列 [0,255,255]など
// 2: t_color *color -> 変換後の値を格納するt_color構造体
bool setRGBcolor(char *str, t_color *color)
{
  color->r = stringToInt(&str);
  if (255 < color->r)
    return (false);
  // 区切りのカンマを指しているので一つ進める
  str++;
  color->g = stringToInt(&str);
  if (255 < color->g)
    return (false);
  str++;
  color->b = stringToInt(&str);
  if (255 < color->b)
    return (false);
  return (true);
}

// tokenからt_ambient構造体に値を変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *global_info -> 変換した値を入れるminirt構造体
void setAmbient(char **token, t_minirt *global_info)
{
  bool flag;

  if(!token[1] || !token[2])
    printErrAndExit("Amiebt value is not enough\n");
  global_info->amb = my_malloc(sizeof(t_ambient));
  global_info->amb->light_range = ft_atod(token[1]);
  if (global_info->amb->light_range < 0.0 || 1.0 < global_info->amb->light_range)
    printErrAndExit(AMB_LIGHT_ERR);
  flag = setRGBcolor(token[2], &(global_info->amb->color));
  if (flag == false)
    printErrAndExit(AMB_COLOR_ERR);
}

// tokenからカメラ構造体に変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *global_info -> 変換した値を入れるminirt構造体
void setCamera(char **token, t_minirt *global_info)
{
  if(!token[1] || !token[2] || !token[3])
    printErrAndExit("Camera value is not enough\n");
  global_info->cam = my_malloc(sizeof(t_camera));
  setVec(token[1], &(global_info->cam->view_vec));
  setVec(token[2], &(global_info->cam->ori_vec));
  if (checkVecRange(global_info->cam->ori_vec) == false)
    printErrAndExit(CAM_VEC_ERR);
  global_info->cam->fov = ft_atoi(token[3]);
  if (global_info->cam->fov < 0 || 180 < global_info->cam->fov)
    printErrAndExit(CAM_FOV_ERR);
}

// tokenからLight構造体に変換する関数
//  1: char **token -> 変換したいtoken列
//  2: t_minirt *global_info -> 変換した値を入れるminirt構造体
void setLight(char **token, t_minirt *global_info)
{
  int flag;

  if(!token[1] || !token[2] || !token[3])
    printErrAndExit("Light value is not enough\n");
  global_info->light = my_malloc(sizeof(t_light));
  setVec(token[1], &(global_info->light->point_vec));
  global_info->light->brightness = ft_atod(token[2]);
  if (global_info->light->brightness < 0.0 || 1.0 < global_info->light->brightness)
    printErrAndExit(LIGHT_BRIGHT_ERR);
  flag = setRGBcolor(token[3], &(global_info->light->color));
  if (flag == false)
    printErrAndExit(LIGHT_COLOR_ERR);
}