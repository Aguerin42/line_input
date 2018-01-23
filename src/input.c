#include "line_input.h"

/*
**	\brief	Initialisation de la structure `init_line_info`
**
**	La fonction initalise les paramètres de la structure `init_line_info`.
**
**	\param	size -	taille de la première allocation (sans compter le '\0')
*/

t_line		init_line_info(size_t size, char *prompt)
{
	t_line	line_info;

	line_info.size = size;
	line_info.prompt = ft_strlen(prompt) + 1;
	line_info.len = 0;
	line_info.cursor_i = 0;
	line_info.cursor_x = line_info.prompt;
	line_info.cursor_y = 1;
	line_info.cursor_s = -1;
	line_info.nb_line = 0;
	return (line_info);
}

static void	set_term(void)
{
	struct termios	new;

	tcgetattr(0, &new);
	new.c_lflag &= ~(ICANON);
	new.c_lflag &= ~(ECHO);
	new.c_cc[VTIME] = 0;
	new.c_cc[VMIN] = 1;
	tcsetattr(0, TCSADRAIN, &new);
}

static void	reset_term(struct termios save)
{
	tcsetattr(0, 0, &save);
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
**	La fonction intercepte le signal SIGINT et le rétablit à son comportement
**	par défaut avant de retourner la commande. Si la fonction appelante a
**	également besoin d'intercepter ce signal, elle devra le rétablir après
**	l'appel à _line_input_.
**
**	\param	prompt -		prompt à afficher
**	\param	history -		liste pour historique, peut être `NULL` si celui-ci
**							n'existe pas
*/

char		*line_input(char *prompt, t_list *history)
{
	char			*line;
	t_line			line_info;
	struct termios	save;

	launch_signal();
	ft_putstrs(prompt);
	if ((line = (char*)ft_memalloc(sizeof(char) * (INPUT_BUF_SIZE + 1))))
	{
		line_info = init_line_info(INPUT_BUF_SIZE, prompt);
		line_info.term = tgetent(NULL, getenv("TERM")) <= 0 ? 0 : 1;
		get_line_info(&line_info);
		get_line(&line);
		get_prompt(prompt);
		tcgetattr(0, &save);
		set_term();
		input(&line, &line_info, prompt, history);
		reset_term(save);
	}
	else if (!line)
		ft_putendl_fd("\nline_input: allocation error.", 2);
	signal(SIGINT, SIG_DFL);
	return (line);
}
