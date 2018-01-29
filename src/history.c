/**
**	\file	history.c
**	\author	Alexis Guérin
**	\date	14 décembre 2017
**
**	\brief	Navigation dans l'historique
*/

#include "line_input.h"

/*
**	\brief	Remplacement de la ligne actuelle par celle de l'historique
*/

static int	alter_line(char **line, t_line *line_info, char *new)
{
	int		i;

	if (line && line_info && new)
	{
		i = -1;
		ft_bzero(line[0], line_info->len);
		line_info->len = 0;
		line_info->cursor_i = 0;
		while (new[++i])
			if (!(insert_char(line, new[i], line_info)))
				line_info->len++;
		line_info->cursor_i = line_info->len;
		return (0);
	}
	return (1);
}

/**
**	\brief	Navigation dans l'historique
**
**	L'utilisateur peut naviguer dans l'historique avec `ctrl`-`n`/`bas` ou
**	`ctrl`-`p`/`haut` et éditer la ligne qu'il désire. L'historique en lui-même
**	n'est pas modifié.
**
**	\param	line -		ligne de commande
**	\param	m -			direction dans l'historique
**	\param	line_info -	structure contenant les informations nécessaires à
**						*line_input*.
**	\param	history -	historique des commandes
*/

int			manage_history(char **line, char m, t_line *line_info,
															t_lstag *history)
{
	static t_lstag	*list = NULL;

	if (history && line && line_info)
	{
		if (!list && m == 65)
			list = history;
		else if (m == 65 && list && list->next)
			list = list->next;
		else if (m == 66 && list && list->prev)
			list = list->prev;
		else
			return (1);
		if (list)
			return (alter_line(line, line_info, list->content));
		return (0);
	}
	if (!history)
		list = NULL;
	return (1);
}
