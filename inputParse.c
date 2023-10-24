#include "minirt.h"

void parseLine(char *line, t_minirt &scene){
  char **token;

  token = ft_split(line, ' ');
  if(!token)
    return ;
  if(ft_strncmp(token[0], "A" , ft_strlen(token[0]))== 0)
}