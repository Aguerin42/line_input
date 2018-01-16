#include "line_input.h"

static void	change_word(int i, char m, char *line, t_line *line_info)
{
	if (m == 67)
	{
		while (line[i + 1] && !ft_isalnum(line[i + 1]))
			++i;
		while (line[i + 1] && ft_isalnum(line[i + 1]))
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
								i + line_info->win_col : line_info->len - 1;
	line_info->cursor_i = i;
}

static void	change_position(int i, char m, t_line *line_info)
{
	if (m == 68 && i > 0)
		--i;
	else if (m == 67 && i < (int)line_info->len - 1)
		++i;
	else if (m == 72)
		i = 0;
	else if (m == 70)
		i = (line_info->len - 1);
	line_info->cursor_i = i;
}

static void		swap_cur(t_line *line_info)
{
	int	tmp;

	if (line_info)
	{
		tmp = line_info->cursor_s;
		line_info->cursor_s = line_info->cursor_i;
		line_info->cursor_i = tmp;
	}
}

void		print_selection(char *line, t_line line_info, char *prompt)
{
	if (line && line_info.cursor_s >= 0)
	{
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		while (--line_info.cursor_y > 0)
			ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("cd", NULL), 0, 0));
		if (line_info.cursor_s > (int)line_info.cursor_i)
			swap_cur(&line_info);
		ft_putstrs(prompt);
		ft_putnstr(line, line_info.cursor_s);
		ft_putstr(tgetstr("mr", NULL));
		ft_putnstr(&line[line_info.cursor_s], line_info.cursor_i - line_info.cursor_s + 1);
		ft_putstr(tgetstr("me", NULL));
		ft_putstr(&line[line_info.cursor_i + 1]);	
	}
}
int			selection(char n, char m, char *line, t_line *line_info)
{
	int	i;

	if (line && line_info &&
		(m == 65 || m == 66 || m == 67 || m == 68 || m == 70 || m == 72))
	{
		i = line_info->cursor_i;
		if (n == 50 || m == 72 || m == 70)
			change_position(i, m, line_info);
		else if (n == 54)
			change_word(i, m, line, line_info);
		if (i == (int)line_info->len && i > 0)
		{
			if (!((i-- + line_info->prompt) % line_info->win_col))
			{
				ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
				ft_putstr(tgoto(tgetstr("ch", NULL), 0, line_info->win_col - 1));
			}
			else
				ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		}
		if (line_info->cursor_s == -1 && i != (int)line_info->cursor_i)
			line_info->cursor_s = i;
		print_selection(line, *line_info, get_prompt(NULL));
		update_info(line_info, (const char*)line);
		replace_cursor(*line_info);
	}
	return (1);
}
