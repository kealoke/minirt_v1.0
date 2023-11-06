#include "../minirt.h"

bool fileIdentiferCheck(t_minirt *scene){
  bool flag;

  flag = true;
  if(!scene->amb || !scene->cam || !scene->light)
    flag = false;
  if(!scene->objs->cy && !scene->objs->pl && !scene->objs->sp)
    flag = false;

  return (flag);
}

// ファイルオープンして読み込む関数
// 1: char *file -> 読み込みたいファイル
// 2: t_minirt &scene -> 読み込んだ情報を格納する構造体
void openAndRead(char *file, t_minirt *scene)
{
  int fd;
  char *file_line;
  bool flag;

  fd = open(file, O_RDONLY);
  if (fd == -1)
    printErrAndExit("failed to open file\n");

  while (true)
  {
    file_line = get_next_line(fd);
    if (!file_line)
      break;
    parseLine(file_line, scene);
  }
  flag = fileIdentiferCheck(scene);
  if(!flag)
    printErrAndExit("your rt file is missing some identifer\n");
}
