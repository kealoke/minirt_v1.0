#include "minirt.h"

int main(int argc, char **argv)
{
  bool flag;
  t_minirt world;
  t_mlx mlx;

  flag = inputCheck(argc, argv);
  if(flag == false)
    return (EXIT_FAILURE);

  openAndRead(argv[1], &world);

  set_mlx(&mlx);

  render(&world, &mlx);

  return (EXIT_SUCCESS);
}
