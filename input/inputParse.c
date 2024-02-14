#include "../minirt.h"

// lineをsplitして構造体に入力する関数
// 1: char *line -> ファイルから読み込んだライン
// 2: t_minirt *world -> 値を入力する構造体
void parseLine(char *line, t_minirt *world, t_read_flag *flag)
{
  char **token;

  token = ft_split(line, ' ');

  if (!token)
    return;
  if (isMatch(token[0], "A"))
    setAmbient(token, world, flag);
  else if (isMatch(token[0], "C")){
    setCamera(token, world, flag);
  }
  else if (isMatch(token[0], "L"))
    setLight(token, world, flag);
  else if (isMatch(token[0], "sp"))
    setSphere(token, world, flag);
  else if (isMatch(token[0], "pl"))
    setPlane(token, world, flag);
  else if (isMatch(token[0], "cy"))
    setCylinder(token, world, flag);
}
