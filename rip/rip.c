#include <stdio.h>

int	invalid(char *str)
{
	int	i = 0;
	int	open = 0;
	int	close = 0;
	
	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

void	result(char *str, int remove, int deleted, int *used)
{
	if (remove == deleted)
	{
		if (!invalid(str))
			puts(str);
		return ;
	}
	int	pos = 0;
	while (str[pos] && !used[pos])
	{      
		used[pos] = 1;
		if (str[pos] == '(' || str[pos] == ')')
		{
			char	c = str[pos];
			str[pos] = ' ';
			result (str, remove, deleted + 1, used);
			str[pos] = c;
		}
		used[pos] = 0;
		pos++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int	used[100] = {0};
	int	remove = invalid(argv[1]);
	result (argv[1], remove, 0, used);
	return (0);
}
