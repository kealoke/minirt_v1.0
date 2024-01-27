#include "../minirt.h"

//bool構造体を初期化する関数
void init_flags(t_read_flag *flag){
  flag->amb_f= false;
  flag->cam_f = false;
  flag->light_f = false;
  flag->obj_f = false;
}

//ファイルから設定が全て取得できているか確認する関数
bool fileIdentiferCheck(t_read_flag flag){

if(flag.amb_f == false)
  return false;
if(flag.cam_f == false)
  return false;
if(flag.light_f == false)
  return false;
if(flag.obj_f == false)
  return false;
return true;
}

// ファイルオープンして読み込む関数
// 1: char *file -> 読み込みたいファイル
// 2: t_minirt &global_info -> 読み込んだ情報を格納する構造体
void openAndRead(char *file, t_minirt *global_info)
{
  int fd;
  char *file_line;
  bool ckeck_flag;
  t_read_flag flag;

  fd = open(file, O_RDONLY);
  if (fd == -1)
    printErrAndExit("failed to open file\n");

  while (true)
  {
    file_line = get_next_line(fd);
    if (!file_line)
      break;
    parseLine(file_line, global_info, &flag);
  }
  ckeck_flag = fileIdentiferCheck(flag);
  if(!ckeck_flag)
    printErrAndExit("your rt file is missing some identifer\n");
}
