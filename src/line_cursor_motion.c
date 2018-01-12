#include "line_input.h"

/*
**	\brief	Déplacement du curseur à l'écran
*/

static void	move_cursor_left(t_line *line_info)
{
	if (line_info)
	{
		if (line_info->cursor_x > 0)
			ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		else
		{
			ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, line_info->win_col - 1));
		}
		line_info->cursor_i -= 1;
	}
}

/*
**	\brief	Déplacement du curseur à l'écran
*/

static void	move_cursor_right(t_line *line_info)
{
	if (line_info)
	{
		if (line_info->cursor_x < line_info->win_col - 1)
			ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		else
		{
			ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		}
		line_info->cursor_i += 1;
	}
}

/*
**	\brief	Déplacement du curseur sur la chaîne
*/

int			move_cursor_on_line(char m, t_line *line_info)
{
	if (line_info)
	{
		if (m == 68 && line_info->cursor_i > 0)
			move_cursor_left(line_info);
		else if (m == 67 && line_info->cursor_i < line_info->len)
			move_cursor_right(line_info);
		else if (m == 72 || m == 1)
		{
			line_info->cursor_i = 0;
			return (0);
		}
		else if (m == 70 || m == 5)
		{
			line_info->cursor_i = line_info->len;
			return (0);
		}
	}
	return (1);
}

int			move_ctrl_arrow(char m, char *line, t_line *line_info)
{
	int	i;

	if (line_info && (m == 67 || m == 68 || m == 65 || m == 66))
	{
		i = line_info->cursor_i;
		if (m == 67)
		{
			while (line[i] && ft_isalnum(line[i]))
				++i;
			while (line[i] && !ft_isalnum(line[i]))
				++i;
		}
		else if (m == 68)
		{
			if (i > 0 && ft_isalnum(line[i]) && !ft_isalnum(line[i - 1]))
				--i;
			while (i > 0 && !ft_isalnum(line[i]))
				--i;
			while (i > 0 && ft_isalnum(line[i - 1]))
				--i;
		}
		else if (m == 65)
			i = (i >= (int)line_info->win_col) ? i - line_info->win_col : 0;
		else if (m == 66)
			i = (i + (int)line_info->win_col <= (int)line_info->len) ?\
								i + line_info->win_col : line_info->len;
		line_info->cursor_i = i;
		return (0);
	}
	return (1);
}

/*
**	\brief Replacement du curseur après affichage
*/

void		replace_cursor(t_line line_info)
{
	int	x;
	int	y;

	!line_info.win_col ? line_info.win_col = 1 : 0;
	x = (line_info.len + line_info.prompt) % line_info.win_col;
	y = nb_line(line_info.len + line_info.prompt + 1, line_info.win_col);
	if (!((line_info.len + line_info.prompt) % line_info.win_col))
	{
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	}
	while (--y >= (int)line_info.cursor_y)
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, line_info.cursor_x));
}
