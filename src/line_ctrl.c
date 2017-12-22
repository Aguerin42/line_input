#include "line_input.h"

int	ctrl_key(char buf[], char **line, t_line *line_info)
{
	if (buf[0] == 1 || buf[0] == 5)
		return (move_cursor_on_line(buf[0], line_info));
	else if (buf[0] == 8 || (buf[0] == 4 && line_info->len))
		return (delete_char(line, buf[0], line_info));
	else if (buf[0] == 11)
		;
	else if (buf[0] == 12)
	{
		ft_putstr(tgoto(tgetstr("cl", NULL), 0, 0));
	}
	else if (buf[0] == 20)
		return (swap_char(line, line_info));
	else if (buf[0] == 21)
		;
	else if (buf[0] == 23)
		;
	else if (buf[0] == 4)
	{
			ft_strcpy(*line, "exit");
			buf[0] = 10;
			return (1);
	}
	else
		return (1);
	return (0);
}
