#include "minirt.h"

int main(int argc, char **argv)
{
  bool flag;
  t_minirt world;
  t_mlx mlx;

  flag = input_check(argc, argv);
  if(flag == false)
    return (EXIT_FAILURE);

  open_and_read(argv[1], &world);

  set_mlx(&(world.mlx));

  render(&world);

  return (EXIT_SUCCESS);
}
