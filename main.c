#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdlib.h>
#include "lem_in.h"
#include "ft_printf/includes/ft_printf.h"

static t_queue	*read_farm_file(char *fname)
{
	int		fd;
	t_queue	*input;

	fd = open(fname, O_RDONLY);
	input = read_farm(fd);
	close(fd);
	return (input);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		ft_printf("usage: ./test map\n");
	else
	{
		system(ft_sformat("../lem-in < %s > %s.out", argv[1], argv[1]));
		read_farm_file(ft_sformat("%s.out", argv[1]));
		ft_printf("{fg_bgreen}OK :D{eoc}\n");
	}
	return 0;
}