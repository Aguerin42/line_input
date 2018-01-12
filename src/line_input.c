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

int				nb_line(size_t len, size_t col)
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

static t_line	init_line_info(size_t size, char *prompt)
{
	t_line	line_info;

	line_info.size = size;
	line_info.prompt = ft_strlen(prompt) + 1;
	line_info.len = 0;
	line_info.cursor_i = 0;
	line_info.cursor_x = line_info.prompt;
	line_info.cursor_y = 1;
	line_info.nb_line = 0;
	return (line_info);
}

static void		update_info(t_line *line_i, const char *line)
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
**	\brief	Vérification de la touche tappée
*/

static int		check_key(char **line, char buf[], t_line *line_info,
														t_list *history)
{
	if (line && line_info && line_info->size)
	{
		if ((buf[0] >= 32 && buf[0] <= 126) && !buf[1])
			return (insert_char(line, buf[0], line_info));
		else if (buf[0] == 127 || (buf[0] == 27 && buf[1] == 91\
					&& buf[2] == 51 && buf[3] == 126 && !buf[4]))
			return (delete_char(line, buf[0], line_info));
		else if ((buf[0] == 27 && buf[1] == 91 && !buf[3]) &&
				(buf[2] == 68 || buf[2] == 67 || buf[2] == 72 || buf[2] == 70))
			return (move_cursor_on_line(buf[2], line_info));
		else if ((buf[0] == 27 && buf[1] == 91 && !buf[3]) &&
				(buf[2] == 65 || buf[2] == 66))
			return (manage_history(line, buf[2], line_info, history));
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 &&
					buf[4] == 53)
			return (move_ctrl_arrow(buf[5], *line, line_info));
		else if (buf[0] == 10 && !buf[1])
			return (move_cursor_on_line(70, line_info));
		else if (buf[0] && !buf[1])
			return (ctrl_key(buf, line, line_info, history));
	}
	return (1);
}


char			*read_simple(char *line, t_line line_info, char buf[])
{
	if (line)
	{
		while (buf[0] != 10 && line_info.size)
		{
			ft_bzero(buf, 7);
			read(0, buf, 6);
			insert_char(&line, buf[0], &line_info);
		}
	}
	return (line);
}

static void		set_term(void)
{
	struct termios	new;

	tcgetattr(0, &new);
	new.c_lflag &= ~(ICANON);
	new.c_lflag &= ~(ECHO);
	new.c_cc[VTIME] = 0;
	new.c_cc[VMIN] = 1;
	tcsetattr(0, TCSADRAIN, &new);
}

static void		reset_term(struct termios save)
{
	tcsetattr(0, 0, &save);
}

t_line	*get_line_info(t_line *info)
{
	static t_line	*line_info = NULL;

	if (info)
		line_info = info;
	return (line_info);
}

char	**get_line(char **line)
{
	static char	**save_line = NULL;

	if (line)
		save_line = line;
	return (save_line);
}

char	*get_prompt(char *prompt)
{
	static char	*save_prompt = NULL;

	if (prompt)
		save_prompt = prompt;
	return (save_prompt);
}

void	ctrlc(int signal)
{
	char	*prompt;
	char	**line;
	t_line	*line_info;

	(void)signal;
	line_info = get_line_info(NULL);
	if ((line = get_line(NULL)))
		ft_strdel(line);
	while (line_info->cursor_y++ < line_info->nb_line)
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
	if ((*line = (char*)ft_memalloc(sizeof(char) * (INPUT_BUF_SIZE + 1))))
	{
		ft_putendl("");
		prompt = get_prompt(NULL);
		ft_putstrs(prompt);
		*line_info = init_line_info(INPUT_BUF_SIZE, prompt);
		update_info(line_info, *line);
	}
	else if (line_info && line_info->size)
	{
		line_info->size = 0;
		ft_putendl_fd("\nline_input: allocation error", 2);
	}
}

/*
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
**	\param	prompt -		prompt à afficher
**	\param	history -		liste pour historique, peut être `NULL` si celui-ci
**							n'existe pas
*/

char			*line_input(char *prompt, t_list *history)
{
	char			*line;
	char			buf[7];
	t_line			line_info;
	struct termios	save;

	signal(SIGINT, ctrlc);
	ft_putstrs(prompt);
	if ((line = (char*)ft_memalloc(sizeof(char) * (INPUT_BUF_SIZE + 1))))
	{
		buf[0] = 0;
		line_info = init_line_info(INPUT_BUF_SIZE, prompt);
		line_info.term = tgetent(NULL, getenv("TERM")) <= 0 ? 0 : 1;
		get_line_info(&line_info);
		get_line(&line);
		get_prompt(prompt);
		line_info.term ? (void)tcgetattr(0, &save) : NULL;
		line_info.term ? set_term() : NULL;
		while (buf[0] != 10 && line_info.size)
		{
			update_info(&line_info, line);
			ft_bzero(buf, 7);
			read(0, buf, 6);
			if (line_info.size && line_info.term &&
				!check_key(&line, buf, &line_info, history))
			{
				print_line(line, line_info, prompt);
				update_info(&line_info, line);
				replace_cursor(line_info);
			}
		}
		line_info.term ? reset_term(save) : NULL;
	}
	else if (!line)
		ft_putendl_fd("\nline_input: allocation error.", 2);
	signal(SIGINT, SIG_DFL);
	return (line);
}
