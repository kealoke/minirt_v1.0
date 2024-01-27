#include "../minirt.h"

// lineをsplitして構造体に入力する関数
// 1: char *line -> ファイルから読み込んだライン
// 2: t_minirt *global_info -> 値を入力する構造体
void parseLine(char *line, t_minirt *global_info, t_read_flag *flag)
{
  char **token;

  token = ft_split(line, ' ');
  printf("token %s\n", token[0]);
  if (!token)
    return;
  if (isMatch(token[0], "A"))
    setAmbient(token, global_info, flag);
  else if (isMatch(token[0], "C")){
    setCamera(token, global_info, flag);
    printf("cam %f\n", global_info->cam->view_vec.z);
  }
  else if (isMatch(token[0], "L"))
    setLight(token, global_info, flag);
  else if (isMatch(token[0], "sp"))
    setSphere(token, global_info, flag);
  else if (isMatch(token[0], "pl"))
    setPlane(token, global_info, flag);
  else if (isMatch(token[0], "cy"))
    setCylinder(token, global_info, flag);
}
