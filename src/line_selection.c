#include "line_input.h"

int	selection(char m, char *line, t_line *line_info)
{
	int	e;

	if (line && line_info && (m == 67 || m == 68))
	{	
		if (m == 68)
		{
			if (line_info->cursor_i > 0)
			{
				ft_putstr(tgetstr("mr", NULL));
				if (line_info->cursor_i == line_info->len)
				{
					if (!line_info->cursor_x)
					{
						ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
						ft_putstr(tgoto(tgetstr("ch", NULL), 0, line_info->win_col -1));
					}
					else
						ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
					line_info->cursor_i--;
					e = 1;
				}
				else
					e = 0;
				line_info->cursor_s = line_info->cursor_i;
				ft_putchar(line[line_info->cursor_i++]);
				if (!e)
				{
					ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
					line_info->cursor_i--;
				}
				if (!line_info->cursor_x && !e)
				{
					ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
					ft_putstr(tgoto(tgetstr("ch", NULL), 0, line_info->win_col -1));
				}
				else if (line_info->cursor_x != line_info->win_col - 1)
					ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
				line_info->cursor_i--;
			}
		}
		else if (m == 67)
		{
			if ((int)line_info->cursor_i < (int)line_info->len - 1)
			{
				ft_putstr(tgetstr("mr", NULL));
				ft_putchar(line[line_info->cursor_i]);
				line_info->cursor_s = line_info->cursor_i;
				if (++line_info->cursor_i + line_info->prompt == line_info->win_col)
				{
					ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
					ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
				}
			}
		}
		ft_putstr(tgetstr("me", NULL));
	}
	return (1);
}
