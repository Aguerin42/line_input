#include "line_input.h"

int		is_in_heredoc(int i)
{
	static int	s = 0;

	if (i >= 0)
		s = i;
	return (s);
}

char	*redoc_delimiter(char *str)
{
	static char	*s = NULL;

	if (str)
		s = str;
	return (s);
}
