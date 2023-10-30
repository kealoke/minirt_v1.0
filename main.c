#include "minirt.h"

void initStruct(t_minirt *scene){
  scene->amb = NULL;
  scene->cam = NULL;
  scene->libs = NULL;
  scene->light = NULL;
  scene->objs = NULL;
}

int main(int argc, char **argv)
{
  bool flag;
  t_minirt scene;

  initStruct(&scene);
  flag = inputCheck(argc, argv);
  if(flag == false)
    return (EXIT_FAILURE);
  openAndRead(argv[1], &scene);

}