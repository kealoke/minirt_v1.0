#include "../minirt.h"

// lineをsplitして構造体に入力する関数
// 1: char *line -> ファイルから読み込んだライン
// 2: t_minirt *scene -> 値を入力する構造体
void parseLine(char *line, t_minirt *scene)
{
  char **token;

  token = ft_split(line, ' ');
  if (!token)
    return;
  if (isMatch(token[0], "A"))
    setAmbient(token, scene);
  else if (isMatch(token[0], "C"))
    setCamera(token, scene);
  else if (isMatch(token[0], "L"))
    setLight(token, scene);
  else if (isMatch(token[0], "sp"))
    setSphere(token, scene);
  else if (isMatch(token[0], "pl"))
    setPlane(token, scene);
  else if (isMatch(token[0], "cy"))
    setCylinder(token, scene);
  else
    printErrAndExit("rt file identifer is invalid");
}
