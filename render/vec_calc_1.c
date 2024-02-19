#include "../minirt.h"

//内積を計算
double	InnerProduct(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//外積を計算
t_vec	crossProduct(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

//ベクトルのb倍
t_vec	mul_vec(t_vec a, double b)
{
	t_vec	res;

	res.x = a.x * b;
	res.y = a.y * b;
	res.z = a.z * b;
	return (res);
}

// ベクトルのノルムを取得する
double	norm_vec(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

// ベクトルの正規化
t_vec	vec_normalize(t_vec a)
{
	t_vec	res;
	double	mag;

	mag = sqrt(InnerProduct(a, a));
	res.x = a.x / mag;
	res.y = a.y / mag;
	res.z = a.z / mag;
	return (res);
}
