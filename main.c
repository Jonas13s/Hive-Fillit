#include <stdio.h>
#include "fillit.h"

int	main(int args, char **argv)
{
	int i = 0;
	char *name;
	name = ft_strjoin("error_file/error_", "0");
	char *c;
	printf("%s\n", name);
	while (i <= 25)
	{
		printf("%d %d\n",i, error_handling(name));
		ft_strdel(&name);
		c = ft_itoa(i);
		name = ft_strjoin("error_file/error_", (char *)c);
		ft_strdel(&c);
		i++;
	}
	ft_strdel(&name);
	ft_strdel(&c);
	return (0);
}