#include "minirt.h"

// void global_init(t_minirt *global_info){

// }

int main(int argc, char **argv)
{
  bool flag;
  t_minirt global_info;
  t_mlx mlx;


  flag = inputCheck(argc, argv);
  if(flag == false)
    return (EXIT_FAILURE);

  // global_init(&global_info);
  // printf("%p\n", global_info.amb);
  // initStruct(&global_info);
  openAndRead(argv[1], &global_info);

  // ("%f\n", global_info.amb->light_ranprintfge);
  // printf("%f\n", global_info.cam->view_vec.z);
  // printf("%u\n", global_info.light->color.b);
  // t_sphere *tmp = global_info.objs->content;
  // printf("%f\n", tmp->center_vec.z);


  draw(&global_info, &mlx);

}