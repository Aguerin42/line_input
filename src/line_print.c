#include "line_input.h"

/*
**	\brief	Affichage de la ligne de commande
**
**	La fonction supprime les lignes affichées et affiche la nouvelle, après le
**	prompt.
**
**	\param	line -		Ligne à afficher
**	\param	line_info - Information sur la ligne et la position du curseur
*/

void	print_line(char *line, t_line line_info)
{
	if (line)
	{
		while (--line_info.cursor_y > 0)
		{
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
			ft_putstr(tgoto(tgetstr("cd", NULL), 0, 0));
			ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		}
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, line_info.prompt));
		ft_putstr(tgetstr("cd", NULL));
		ft_putstr(line);
	}
}
