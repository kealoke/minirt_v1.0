
#include "minirt.h"

int inputError(char *msg){
  printf("%s", msg);
  return (false);
}

void printErrAndExit(char *msg){
  printf("%s", msg);
  exit(EXIT_FAILURE);
}

bool inputCheck(int argc, char **argv){
  if(argc < 2 || 3 < argc)
    return (inputError("USAGE: ./minirt [1]*.rt [option] \n"));
  if(!ft_strrchr(argv[1], ".rt"))
    return (inputError("Error: input argument is not correct\n"));
}

void openAndRead(char *file, t_minirt &scene){
  int fd;
  char file_line;

  fd = open(file, O_RDONLY);
  if(fd == -1)
    printErrAndExit("Error: falied to open file\n");

  while(true){
    file_line = get_next_line(fd);
    if(!file_line)
      break;
    parseLine(file_line, scene);
  }

}