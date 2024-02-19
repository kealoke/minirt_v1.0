#include "minirt.h"

// void global_init(t_minirt *world){

// }

int main(int argc, char **argv)
{
  bool flag;
  t_minirt world;
  t_mlx mlx;


  flag = inputCheck(argc, argv);
  if(flag == false)
    return (EXIT_FAILURE);

  openAndRead(argv[1], &world);

  // ("%f\n", world.amb->light_ranprintfge);
  // printf("%f\n", world.cam->pos_vec.z);
  // printf("%u\n", world.light->color.b);
  // t_sphere *tmp = world.objs->content;
  // printf("%f\n", tmp->center_vec.z);


  draw(&world, &mlx);

}