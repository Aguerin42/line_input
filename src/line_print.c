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

void	print_line(char *line, t_line line_info, char *prompt)
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
