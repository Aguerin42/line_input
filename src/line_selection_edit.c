#include "line_input.h"

int	delete_selection(char **line, t_line *line_info)
{
	int	tmp;

	if (line && *line && line_info && line_info->len)
	{
		if ((int)line_info->cursor_i > line_info->cursor_s)
		{
			tmp = (int)line_info->cursor_i;
			line_info->cursor_i = line_info->cursor_s;
			line_info->cursor_s = tmp;
		}
		while (line_info->cursor_s-- >= (int)line_info->cursor_i)
			delete_char(line, 4, line_info);
		return (0);
	}
	return (1);
}
