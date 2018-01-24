#include "line_input.h"

/*
**	\brief	Affichage de la ligne de commande
**
**	La fonction supprime les lignes affichées et affiche la nouvelle, après le
**	prompt.
**
**	\param	line -		Ligne à afficher
**	\param	line_info - Information sur la ligne et la position du curseur
**	\param	prompt -	Prompt du Shell
*/

void		print_line(char *line, t_line line_info, char *prompt)
{
	int				y;
	struct winsize	win;

	if (line)
	{
		ioctl(0, TIOCGWINSZ, &win);
		if (line_info.win_col != win.ws_col)
			y = nb_line(line_info.cursor_i + line_info.prompt, win.ws_col);
		else
			y = line_info.cursor_y;
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		while (--y > 0)
			ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("cd", NULL), 0, 0));
		ft_putstrs(prompt);
		ft_putstr(line);
	}
}

static void	swap_cur(t_line *line_info)
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
	if (line)
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
		ft_putnstr(&line[line_info.cursor_s],
				line_info.cursor_i - line_info.cursor_s + 1);
		ft_putstr(tgetstr("me", NULL));
		if (line_info.cursor_i + 1 < MAX_ALLOC)
			ft_putstr(&line[line_info.cursor_i + 1]);
	}
}
