#include "line_input.h"

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
	line_info.len = 0;
	line_info.cursor_i = 0;
	line_info.cursor_x = 0;
	line_info.cursor_y = 0;
	line_info.prompt = prompt_len;
	return (line_info);
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

char	*line_input(size_t prompt_len, t_list *history)
{
	t_line	line_info;
	char	*line;
	char	buf[7];

	if ((line = (char*)ft_memalloc(sizeof(char) * (INPUT_BUF_SIZE + 1))))
	{
		line_info = init_line_info(INPUT_BUF_SIZE, prompt_len);
		buf[0] = 0;
		while (buf[0] != 10)
		{
			ft_bzero(buf, 7);
			read(0, buf, 6);
			ft_putchar(buf[0]);
		}
	}
	else
		ft_putendl_fd("\nline_input : allocation error...", 2);
	(void)history;
	return (line);
}
