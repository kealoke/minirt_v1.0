#ifndef MINIRT_H
#define MINIRT_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>

#include "./libft/libft.h"
#include "./gnl/get_next_line.h"

//描写に必要な全体の情報をもつ
//1: t_libx libs -> minilibxの情報
//2: t_ambient amb -> 自然光情報
//3: t_camera cam -> カメラ情報
//4: t_light lig -> 光源情報
//5: t_objects objs -> 描写する物体情報
typedef struct s_minirt
{
  t_libx libs;
  t_ambient amb;
  t_camera cam;
  t_light lig;
  t_objects objs;

}t_minirt;

//minilibxに必要な情報
typedef struct s_libx
{
  void *mlx;
  void *window;
} t_libx;

// ベクトル構造体
typedef struct s_vec
{
  double x;
  double y;
  double z;
} t_vec;

// RGBカラー構造体 range[0, 255]
typedef struct s_color
{
  double r;
  double g;
  double b;
} t_color;

// 自然光構造体
// 1: double light_range -> 自然光の光の強さ range[0.0, 1.0]
// 2: t_color color -> 自然光の色
typedef struct s_ambient
{
  double light_range;
  t_color color;
} t_ambient;

// カメラ構造体
// 1: t_vec view_vec -> カメラの座標ベクトル
// 2: t_vec ori_vec -> カメラの向きベクトル range[-1, 1]
// 3: int fov -> カメラの視野角 range[0, 180]
typedef struct s_camera
{
  t_vec view_vec;
  t_vec ori_vec;
  int fov;
} t_camera;

// 光源構造体
// 1: t_vec point_vec -> 光源の座標ベクトル
// 2: double brightness -> 光源の明るさ range[0.0, 1.0]
// 3: t_color color -> 光源の色
typedef struct s_light
{
  t_vec point_vec;
  double brightness;
  t_color color;

} t_light;

// 球体構造体
// 1: t_vec center_vec -> 球の中心の座標ベクトル
// 2: double diameter -> 球の直径
// 3: t_color color -> 球の色
typedef struct s_sphere
{
  t_vec center_vec;
  double diameter;
  t_color color;
} t_sphere;

// 平面構造体
// 1: t_vec point_vec -> 平面の座標ベクトル
// 2: t_vec normal_vec -> 平面の法線ベクトル range[-1, 1]
// 3: t_color color -> 平面の色
typedef struct s_plane
{
  t_vec point_vec;
  t_vec normal_vec;
  t_color color;
} t_plane;

// 円柱構造体
// 1: t_vec center_vec -> 円柱の中心の座標ベクトル
// 2: t_vec axis_vec -> 円柱の軸ベクトル
// 3: double diameter -> 円柱の直径
// 4: double height -> 円柱の高さ
// 5: t_color color -> 円柱の色
typedef struct s_cylinder
{
  t_vec center_vec;
  t_vec axis_vec;
  double diameter;
  double height;
  t_color color;
} t_cylinder;

//物体構造体
//1: t_sphere *sp ->球体構造体へのポインタ
//2: t_plane *pl ->平面構造体へのポインタ
//3: t_cylinder *cy -> 円柱構造体へのポインタ
typedef struct s_objects{
  t_sphere *sp;
  t_plane *pl;
  t_cylinder *cy;
}t_objects;

#endif