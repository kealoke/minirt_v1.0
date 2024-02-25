#ifndef STRUCT_H
# define STRUCT_H

# include "./libft/libft.h"

//rtファイルの設定がされているかのフラグ
typedef struct s_read_flags
{
	bool				amb_f;
	bool				cam_f;
	bool				light_f;
	bool				obj_f;
}						t_read_flag;

// minilibxに必要な情報
typedef struct s_mlx
{
	void				*mlx;
	void				*window;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_mlx;

// ベクトル構造体
typedef struct s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

// RGBカラー構造体 range[0, 255]
typedef struct s_color
{
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
}						t_color;


// 自然光構造体
// 1: double light_intensity -> 自然光の光の強さ range[0.0, 1.0]
// 2: t_color color -> 自然光の色
typedef struct s_ambient
{
	double				light_intensity;
	t_color				color;
}						t_ambient;

// カメラ構造体
// 1: t_vec pos_vec -> カメラの座標ベクトル
// 2: t_vec ori_vec -> カメラの向きベクトル range[-1, 1]
// 3: int fov -> カメラの視野角 range[0, 180]
typedef struct s_camera
{
	t_vec				pos_vec;
	t_vec				ori_vec;
	double				fov;
}						t_camera;

// 光源構造体
// 1: t_vec pos_vec -> 光源の座標ベクトル
// 2: double brightness -> 光源の明るさ range[0.0, 1.0]
// 3: t_color color -> 光源の色
typedef struct s_light
{
	t_vec				pos_vec;
	double				brightness;
	t_color				color;
}						t_light;

// 球体構造体
// 1: t_vec center_vec -> 球の中心の座標ベクトル
// 2: double diameter -> 球の直径
// 3: t_color color -> 球の色
typedef struct s_sphere
{
	t_vec				center_vec;
	double				diameter;
	t_color				color;
}						t_sphere;

// 平面構造体
// 1: t_vec pos_vec -> 平面の座標ベクトル
// 2: t_vec normal_vec -> 平面の法線ベクトル range[-1, 1]
// 3: t_color color -> 平面の色
typedef struct s_plane
{
	t_vec				pos_vec;
	t_vec				normal_vec;
	t_color				color;
}						t_plane;

// 円柱構造体
// 1: t_vec center_vec -> 円柱の中心の座標ベクトル
// 2: t_vec axis_vec -> 円柱の軸ベクトル
// 3: double diameter -> 円柱の直径
// 4: double height -> 円柱の高さ
// 5: t_color color -> 円柱の色
typedef struct s_cylinder
{
	t_vec				center_vec;
	t_vec				axis_vec;
	double				diameter;
	double				height;
	t_color				color;
	bool				inside;
}						t_cylinder;

// どのオブジェクトか判別する
typedef enum e_type_name
{
	t_sp,
	t_pl,
	t_cy

}						t_type_name;

// 物体構造体
// 1: void *content -> オブジェクト構造体のポインタ(t_sphere or t_plane or t_cylinder)
// 2: struct t_objects *next -> リストのポインタ
typedef struct s_objects
{
	void				*content;
	t_type_name			obj_type;
	struct s_objects	*next;

}						t_objects;

//描写するオブジェクトのベクトル情報
// 1: double t -> 距離
// 2: t_vec inter_pos -> 交点位置ベクトル
// 2: t_vec obj_normal -> 法線ベクトル
// 3: t_vec light_dir -> 入射ベクトル
// 4: t_color obj_color ->描写するオブジェクトのカラー
typedef struct s_vec_info
{
	double				t;
  	t_vec       		inter_pos;
	t_vec				normal;
	t_vec				light_dir;
	t_color				color;
}						t_vec_info;

//レイトレーシングの計算に使うrayのベクトル情報
//1: t_vec pos -> レイの位置ベクトル
//2: t_vec dir -> レイの方向ベクトル
typedef struct s_ray
{
  t_vec pos;
  t_vec dir;
}t_ray;

//スクリーンの基底ベクトル
// 1: t_vec dsc -> カメラからスクリーンの中心へのベクトル
// 2: t_vec esx ->
// 3: t_vec esy ->
typedef struct s_screen{
	t_vec dsc;
	t_vec esx;
	t_vec esy;
}t_screen;


#endif