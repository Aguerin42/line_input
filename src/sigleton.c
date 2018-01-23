#include "line_input.h"

t_line	*get_line_info(t_line *info)
{
	static t_line	*line_info = NULL;

	if (info)
		line_info = info;
	return (line_info);
}

char	**get_line(char **line)
{
	static char	**save_line = NULL;

	if (line)
		save_line = line;
	return (save_line);
}

char	*get_prompt(char *prompt)
{
	static char	*save_prompt = NULL;

	if (prompt)
		save_prompt = prompt;
	return (save_prompt);
}
