#include "../minirt.h"

//ファイル内ベクトルの文字情報を数値に変換して返す関数
double get_number(char *str, int *i, int *j){
  char *tmp;
  double res;

  tmp = ft_substr(str, *i, *j - *i);
  *i = *j+1;
  *j = *i;
  res = ft_atod(tmp);
  free(tmp);
  return (res);
}


//lightカラーを255から変換する
t_light_color convert_color(t_color rgb){
  t_light_color light_c;

  light_c.r = ((double)rgb.r)/255.0;
  light_c.g = ((double)rgb.g)/255.0;
  light_c.b = ((double)rgb.b)/255.0;

  printf("rgb %f %f %f\n", light_c.r,light_c.g, light_c.b);
  return (light_c);
}

// 文字列をvec構造体に変換する関数
// 1: char *str -> 変換したい文字列[x,y,z]
// 2: t_vec *vec -> 変換後の値を入れる構造体
void setVec(char *str, t_vec *vec)
{
  int i;
  int j;

  i = 0;
  j = 0;
  if (!str)
    return;
  while (str[j] && str[j] != ',')
    j++;
  vec->x = get_number(str, &i, &j);
  while (str[j] && str[j] != ',')
    j++;
  vec->y = get_number(str, &i, &j);
  while (str[j])
    j++;
  vec->z = get_number(str, &i, &j);
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
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
void setAmbient(char **token, t_minirt *world, t_read_flag *flag)
{
  bool rgb_flag;
  t_color rgb_color;

  if(!token[1] || !token[2])
    printErrAndExit("Amiebt value is not enough\n");
  world->amb = my_malloc(sizeof(t_ambient));
  world->amb->light_intensity = ft_atod(token[1]);
  if (world->amb->light_intensity < 0.0 || 1.0 < world->amb->light_intensity)
    printErrAndExit(AMB_LIGHT_ERR);
  rgb_flag = setRGBcolor(token[2], &(rgb_color));
  if (flag == false)
    printErrAndExit(AMB_COLOR_ERR);
  world->amb->color = convert_color(rgb_color);
  flag->amb_f = true;
}

// tokenからカメラ構造体に変換する関数
// 1: char **token -> 変換したいtoken列
// 2: t_minirt *world -> 変換した値を入れるminirt構造体
void setCamera(char **token, t_minirt *world, t_read_flag *flag)
{
  if(!token[1] || !token[2] || !token[3])
    printErrAndExit("Camera value is not enough\n");
    world->cam = my_malloc(sizeof(t_camera));
  setVec(token[1], &(world->cam->pos_vec));
  setVec(token[2], &(world->cam->ori_vec));
  if (checkVecRange(world->cam->ori_vec) == false)
    printErrAndExit(CAM_VEC_ERR);
  world->cam->fov = ft_atoi(token[3]);
  if (world->cam->fov < 0 || 180 < world->cam->fov)
    printErrAndExit(CAM_FOV_ERR);
  flag->cam_f = true;
}

// tokenからLight構造体に変換する関数
//  1: char **token -> 変換したいtoken列
//  2: t_minirt *world -> 変換した値を入れるminirt構造体
void setLight(char **token, t_minirt *world, t_read_flag *flag)
{
  int rgb_flag;
  t_color rgb_color;

  if(!token[1] || !token[2] || !token[3])
    printErrAndExit("Light value is not enough\n");
    world->light = my_malloc(sizeof(t_light));
  setVec(token[1], &(world->light->pos_vec));
  world->light->brightness = ft_atod(token[2]);
  if (world->light->brightness < 0.0 || 1.0 < world->light->brightness)
    printErrAndExit(LIGHT_BRIGHT_ERR);
  rgb_flag = setRGBcolor(token[3], &(rgb_color));
  if (flag == false)
    printErrAndExit(LIGHT_COLOR_ERR);
  world->light->color = convert_color(rgb_color);
  flag->light_f = true;
}