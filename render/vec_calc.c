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

//ベクトルの足し算
t_vec	add_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

//ベクトルの引き算　a-b
t_vec	sub_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

//ベクトルのb倍
t_vec	mul_vec(t_vec a, double b)
{
	t_vec res;

	res.x = a.x * b;
	res.y = a.y * b;
	res.z = a.z * b;
	return (res);
}

// ベクトルのノルム
double	norm_vec(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
