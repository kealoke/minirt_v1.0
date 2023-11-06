
#include "../minirt.h"

int inputError(char *msg)
{
  printf("%s", msg);
  return (false);
}

void printErrAndExit(char *msg)
{
  printf("Error: %s", msg);
  exit(EXIT_FAILURE);
}

// 入力チェックする関数
// 1: int argc -> mainのargc
// 2: char **argv -> mainのargv
bool inputCheck(int argc, char **argv)
{
  if (argc < 2 || 3 < argc)
    return (inputError(USAGE));
  if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])))
    return (inputError("Error: input argument is not correct\n"));
  return (true);
}

// Vecの範囲を確認する関数
//  x,y,zが[-1, 1]の範囲ならtrue 一つでも外れてたらfalse
// 1: t_vec vec -> 確認したいベクトル
bool checkVecRange(t_vec vec)
{
  if (vec.x < -1.0 || 1.0 < vec.x)
    return (false);
  if (vec.y < -1.0 || 1.0 < vec.y)
    return (false);
  if (vec.z < -1.0 || 1.0 < vec.z)
    return (false);
  return (true);
}
