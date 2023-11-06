#include "../minirt.h"

// 文字列の先頭か数字までをintの数値にして返す
//  char *str=255,0,0 -> return (int)255
// 1:char **str -> 変換したい数字を先頭に含む文字列
int stringToInt(char **str)
{
  int ans;

  ans = 0;
  if (!*str)
    return (ans);
  while (ft_isdigit(**str))
  {
    if(ans > (DBL_MAX / 10))
      printErrAndExit("float overflow\n");
    ans = ans * 10 + **str - '0';
    (*str)++;
  }
  return (ans);
}

// ft_atod用の関数 符号を返す
static int getSign(char **str)
{
  int sign;

  sign = 1;
  while ((**str) && !ft_isalnum(**str))
  {
    if (**str == '-')
      sign = -1;
    (*str)++;
  }
  return (sign);
}

// char文字列からdouble型に変換する関数
double ft_atod(char *str)
{
  double ans;
  double fraction;
  int sign;

  if (!str)
    return 0;
  sign = getSign(&str);
  ans = 0;

  // 小数点前までintに変換
  ans = stringToInt(&str);
  fraction = 0.0;
  // 小数点以下を計算
  if (*str == '.') {
    ++str;
    // 小数部分の処理
    while (ft_isdigit(*str)) {
        fraction *= 0.1;
        if (ans > DBL_MAX - (*str - '0') * fraction)
          printErrAndExit("float overflow\n");
        ans += (*str - '0') * fraction;
        ++str;
    }
  }
  return (sign * ans);
}

//二つの文字列が要素と長さが完全に一致しているか確かめる関数
bool isMatch(char *s1, char *s2)
{
  if (!s1 || !s2)
    return (false);
  if (ft_strlen(s1) != ft_strlen(s2))
    return (false);
  if (ft_strncmp(s1, s2, ft_strlen(s1)))
    return (false);
  return (true);
}

void *my_malloc(size_t size)
{
  void *res;

  res = malloc(size);
  if (!res)
    printErrAndExit("malloc err\n");
  return (res);
}
