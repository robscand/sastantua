/*-------------main.c---------------*/

#include "sastantua_h.h"

int	main(int argc, char **argv)
{
  int inp_s;
  if (argc == 2)
    {
      if (argv[1][0] > 48 && argv[1][0] <= 57)
	{
	  inp_s = argv[1][0] - '0';
	  sastantua(inp_s);
	}
    }
  return (0);
}
