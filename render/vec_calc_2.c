#include "../minirt.h"

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
	t_vec res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}