#include "minirt.h"

void initStruct(t_minirt *global_info){
  global_info->amb = NULL;
  global_info->cam = NULL;
  global_info->libs = NULL;
  global_info->light = NULL;
  global_info->objs = NULL;
}

int main(int argc, char **argv)
{
  bool flag;
  t_minirt global_info;

  flag = inputCheck(argc, argv);
  if(flag == false)
    return (EXIT_FAILURE);
  initStruct(&global_info);
  openAndRead(argv[1], &global_info);

}