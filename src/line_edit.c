#include "line_input.h"

/*
**	\brief	Décalage de caractère vers la gauche
**
**	shift_char_left() décale de _n_ positions vers la gauche les caractères
**	de la chaîne _str_.
*/

static void	shift_char_left(char *str, int n)
{
	int	i;
	int	len;

	if (str)
	{
		i = 0;
		len = ft_strlen(str);
		while (i + n <= len)
		{
			str[i] = str[i + n];
			i++;
		}
	}
}

/**
**	\brief	Insertion d'un caractère dans une chaîne
**
**	\return	**0** si l'insertion s'est effectuée correctement ou **1** sinon.
**			L'ajout peut échouer si `line` est `NULL` ou que sa taille est trop
**			grande (262144 caractères),
**			ou que le caractère donné n'est pas affichable.
*/

int			insert_char(char **line, char c, t_line *line_info)
{
	if (line && *line && line_info && (c >= 32 && c <= 126) && line_info->len <= 262144)
	{
		if (line_info->len == line_info->size)
		{
			*line = (char*)ft_memrealloc(*line, line_info->size,\
											line_info->size + INPUT_BUF_SIZE);
			line_info->size += INPUT_BUF_SIZE;
		}
		if (line_info->cursor_i <= line_info->len)
			ft_memmove(&line[0][line_info->cursor_i + 1], &line[0][line_info->cursor_i], line_info->size - line_info->cursor_i);
		line[0][line_info->cursor_i++] = c;
		return (0);
	}
	return (1);
}

/**
**	\brief	Suppression d'un caractère dans une chaîne
**
**	\return	**0** si la suppression s'est effectuée correctement ou **1** sinon.
*/

int			delete_char(char **line, char t, t_line *line_info)
{
	if (line && *line && line_info && line_info->len > 0)
	{
		if ((t == 127 || t == 8) && line_info->cursor_i > 0)
			shift_char_left(&line[0][--line_info->cursor_i], 1);
		else if (t == 27 && line_info->cursor_i < line_info->len)
			shift_char_left(&line[0][line_info->cursor_i], 1);
		else
			return (1);
		return (0);
	}
	return (1);
}
