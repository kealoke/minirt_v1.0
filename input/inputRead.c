#include "../minirt.h"

bool fileIdentiferCheck(t_minirt *global_info){
  bool flag;

  flag = true;
  if(!global_info->amb || !global_info->cam || !global_info->light)
    flag = false;
  if(!global_info->objs->cy && !global_info->objs->pl && !global_info->objs->sp)
    flag = false;

  return (flag);
}

// ファイルオープンして読み込む関数
// 1: char *file -> 読み込みたいファイル
// 2: t_minirt &global_info -> 読み込んだ情報を格納する構造体
void openAndRead(char *file, t_minirt *global_info)
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
    parseLine(file_line, global_info);
  }
  flag = fileIdentiferCheck(global_info);
  if(!flag)
    printErrAndExit("your rt file is missing some identifer\n");
}
