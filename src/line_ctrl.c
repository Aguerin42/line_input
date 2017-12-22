#include "line_input.h"

int	ctrl_key(char buf[], char **line, t_line *line_info)
{
	if (buf[0] == 1 || buf[0] == 5)
		return (move_cursor_on_line(buf[0], line_info));
	else if (buf[0] == 8)
		return (delete_char(line, buf[0], line_info));
	else if (buf[0] == 11)
		;
	else if (buf[0] == 12)
		;
	else if (buf[0] == 20)
		;
	else if (buf[0] == 21)
		;
	else if (buf[0] == 23)
		;
	else if (buf[0] == 4 && !line_info->len)
	{
		ft_strcpy(*line, "exit");
		buf[0] = 10;
	}
	else
		return (1);
	return (0);
}
