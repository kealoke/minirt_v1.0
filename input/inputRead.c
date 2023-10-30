#include "../minirt.h"

// ファイルオープンして読み込む関数
// 1: char *file -> 読み込みたいファイル
// 2: t_minirt &scene -> 読み込んだ情報を格納する構造体
void openAndRead(char *file, t_minirt *scene)
{
  int fd;
  char *file_line;

  fd = open(file, O_RDONLY);
  if (fd == -1)
    printErrAndExit("Error: falied to open file\n");

  while (true)
  {
    file_line = get_next_line(fd);
    if (!file_line)
      break;
    parseLine(file_line, scene);
  }
}