/**
**	\file	read.c
**	\author	Alexis Guérin
**	\date	14 décembre 2017
**
**	\brief	Lecture de l'entrée standard
*/

#include "line_input.h"

static void	input_simple(char buf[], char **line, t_line *line_info)
{
	if (!buf[1] && buf[0] > 31 && buf[0] < 127)
	{
		ft_putchar(buf[0]);
		insert_char(line, buf[0], line_info);
		update_info(line_info, *line);
	}
	else if (!buf[1] && buf[0] == 127)
	{
		if (line_info->cursor_i > 0)
		{
			ft_putchar(8);
			ft_putchar(' ');
			ft_putchar(8);
			delete_char(line, buf[0], line_info);
			update_info(line_info, *line);
		}
	}
}

/**
**	\brief	Lecture de l'entrée standard
**
**	La fonction appelle les différentes fonctions de lecture des touches tappées
**	et de gestion de celles-ci, de mise à jour de line_info, de modifications de
**	la ligne de commande et de replacement du curseur.
**
**	\param	line		- ligne de commande
**	\param	line_info	- pointeur sur la structure contenant les informations
**						nécessaires à *line_input*
**	\param	prompt		- chaîne représentant le prompt (peut être `NULL`)
**	\param	history		- historique de commandes (peut être `NULL`)
*/

void		input(char **line, t_line *line_info, char *prompt,
															t_lstag *history)
{
	char	buf[7];

	if (line)
	{
		buf[0] = 0;
		while (buf[0] != 10 && line_info->size)
		{
			update_info(line_info, *line);
			ft_bzero(buf, 7);
			read(0, buf, 6);
			if (line_info->size && line_info->term)
			{
				if (!check_key(line, buf, line_info, history))
				{
					line_info->cursor_s = -1;
					print_line(*line, *line_info, prompt);
					update_info(line_info, *line);
					replace_cursor(*line_info);
				}
			}
			else
				input_simple(buf, line, line_info);
		}
	}
}
