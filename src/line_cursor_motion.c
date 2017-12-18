#include "line_input.h"

/**
**	\brief	Déplacement du curseur à l'écran
*/

void	move_cursor_left(t_line *line_info)
{
	if (line_info)
	{
		if (line_info->cursor_i > 0)
			ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
	}
}

/**
**	\brief	Déplacement du curseur à l'écran
*/

void	move_cursor_right(t_line *line_info)
{
	if (line_info)
	{
		if (line_info->cursor_i < line_info->len)
			ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	}
}

/**
**	\brief	Déplacement du curseur sur la chaîne
*/

int	move_cursor_on_line(char m, t_line *line_info)
{
	if (line_info)
	{
		if (m == 68 && line_info->cursor_i > 0)
		{
			move_cursor_left(line_info);
			line_info->cursor_i -= 1;
		}
		else if (m == 67 && line_info->cursor_i < line_info->len)
		{
			move_cursor_right(line_info);
			line_info->cursor_i += 1;
		}
		else
			return (1);
	}
	return (0);
}
