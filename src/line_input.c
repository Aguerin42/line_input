#include "line_input.h"

void		debug(t_line line);

/*
**	\brief	Calcul du nombre de lignes nécessaires à l'affichage
**
**	La fonction renvoie le nombre de ligne nécessaires à l'affichage de la ligne
**	`line` en fonction de la largeur de la fenêtre et de la taille du prompt.
**
**	\param	line -		Ligne de commande
**	\param	line_i -	Structure (s_line) contenant les informations sur line et
**						la taille du prompt
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

/*
**	\brief	Initialisation de la structure `init_line_info`
**
**	La fonction initalise les paramètres de la structure `init_line_info`.
**
**	\param	size -	taille de la première allocation (sans compter le '\0')
*/

static t_line	init_line_info(size_t size, size_t prompt_len)
{
	t_line	line_info;

	line_info.size = size;
	line_info.prompt = prompt_len;
	line_info.len = 0;
	line_info.cursor_i = 0;
	line_info.cursor_x = prompt_len;
	line_info.cursor_y = 1;
	line_info.nb_line = 0;
	return (line_info);
}

/*
**	\brief	Vérification de la touche tappée
*/

static int	check_key(char **line, char buf[], t_line *line_info, const t_list *history)
{
	if (line && line_info)
	{
		if ((buf[0] >= 32 && buf [0] <= 126) && !buf[1] && !buf[2])
			return (insert_char(line, buf[0], line_info));
		else if (buf[0] == 127 || buf[0] == 8 || (buf[0] == 27 && buf[1] == 91\
				&& buf[2] == 51 && buf[3] == 126 && !buf[4] && !buf[5]))
			return (delete_char(line, buf[0], line_info));
		else if ((buf[0] == 27 && buf[1] == 91 && !buf[4] && !buf[5]) &&
				(buf[2] == 68 || buf[2] == 67))
			move_cursor_on_line(buf[2], line_info);
		else if ((buf[0] == 27 && buf[1] == 91 && !buf[4] && !buf[5]) &&
				(buf[2] == 66 || buf[2] == 69))
				(void)history;

	}
	return (1);
}

void			print_line(char *line, t_line line_info)
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

/**
**	\brief	Gestion de la ligne de commande
**
**	La fonction s'occupe de la gestion de la ligne de commande. Elle permet de
**	se déplacer dans celle-ci avec les flèches, de l'éditer et d'accéder
**	aux autres lignes de l'historique s'il est disponible.
**	Lorsque l'utilisateur appuie sur _entrée_, la fonction renvoie la chaîne
**	contenant les commandes.
**
**	Avant l'appel à la fonction, le terminal devra être en mode non canonique et
**	non echo.
**
**	\param	prompt_len -	longueur du prompt
**	\param	history -		liste pour historique, peut être `NULL` si celui-ci
**							n'existe pas
*/

void			update_info(t_line *line_info, const char *line)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (line && line_info)
	{
		line_info->win_col = win.ws_col;
		line_info->len = ft_strlen(line);
		line_info->nb_line = nb_line(line_info->len + line_info->prompt, win.ws_col);
		line_info->cursor_x = line_info->win_col ? (line_info->cursor_i + line_info->prompt) % line_info->win_col : 0;
		line_info->cursor_y = nb_line(line_info->cursor_i + line_info->prompt + 1, line_info->win_col);
	}
}

void	replace_cursor(t_line line_info)
{
	int	x;
	int	y;
	
	x = line_info.win_col ? (line_info.len + line_info.prompt) % line_info.win_col : 0;
	y = nb_line(line_info.len + line_info.prompt + 1, line_info.win_col);
	ft_putendl_fd("", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(" ", 2);
	ft_putnbr_fd(y, 2);
	ft_putendl_fd("", 2);
	if (!((line_info.len + line_info.prompt) % line_info.win_col))
	{
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	}
	while (--y >= (int)line_info.cursor_y)
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
	if (x > (int)line_info.cursor_x)
		while (--x >= (int)line_info.cursor_x)
			ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
	else
		while (++x <= (int)line_info.cursor_x)
			ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	ft_putendl_fd("--", 2);
}

char			*line_input(size_t prompt_len, const t_list *history)
{
	char	*line;
	char	buf[7];
	t_line	line_info;

	if ((line = (char*)ft_memalloc(sizeof(char) * (INPUT_BUF_SIZE + 1))))
	{
		line_info = init_line_info(INPUT_BUF_SIZE, prompt_len);
		buf[0] = 0;
		while (buf[0] != 10)
		{
			update_info(&line_info, line);
			debug(line_info);
			ft_bzero(buf, 7);
			read(0, buf, 6);
			if (!check_key(&line, buf, &line_info, history))
			{
				print_line(line, line_info);
				update_info(&line_info, line);
				replace_cursor(line_info);
			}
			ft_putnbr_fd(line_info.nb_line, 2);
		/*	for(int	i = 0; i < 6; i++)
			{
				if (i != 5)
					ft_putnbrs(buf[i]);
				else
					ft_putnbrl(buf[i]);
			}*/
		}
	}
	else
		ft_putendl_fd("\nline_input : allocation error...", 2);
	return (line);
}
