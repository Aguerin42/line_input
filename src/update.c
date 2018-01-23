#include "line_input.h"

/*
**	\brief	Calcul du nombre de lignes nécessaires à l'affichage
**
**	La fonction renvoie le nombre de ligne nécessaires à l'affichage de la ligne
**	`line` en fonction de la largeur de la fenêtre et de la taille du prompt.
**
**	\param	line -		Ligne de commande
**	\param	line_i -	Structure (s_line) contenant les informations sur line
**						et la taille du prompt
**
**	\return	Nombre de lignes nécaissaires
*/

int		nb_line(size_t len, size_t col)
{
	if (len <= col)
		return (1);
	else if (col)
		return (len / col + ((len % col) ? 1 : 0));
	return (0);
}

void	update_info(t_line *line_i, const char *line)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (line_i)
	{
		!win.ws_col ? win.ws_col = 1 : 0;
		line_i->win_col = win.ws_col;
		line_i->len = ft_strlen(line);
		line_i->nb_line = nb_line(line_i->len + line_i->prompt, win.ws_col);
		line_i->cursor_x =
			(line_i->cursor_i + line_i->prompt) % line_i->win_col;
		line_i->cursor_y =
			nb_line(line_i->cursor_i + line_i->prompt + 1, line_i->win_col);
	}
}

/*
**	\brief Replacement du curseur après affichage
*/

void	replace_cursor(t_line line_info)
{
	int	y;

	!line_info.win_col ? line_info.win_col = 1 : 0;
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
