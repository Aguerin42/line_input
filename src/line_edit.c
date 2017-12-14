#include "line_input.h"

/*
**	\brief	Décalage de caractères vers la droite
**
**	shift_char_right() décale de _n_ positions vers la droite les caractères
**	de la chaîne _str_.
**
**	La chaîne _str_ doit être assez grande pour contenir le déplacement et le
**	caractère de fin de chaîne.
*/

static void	shift_char_right(char *str, int n)
{
	int	i;

	if (str)
	{
		i = ft_strlen(str) - 1 + n;
		while (i - n >= 0)
		{
			str[i] = str[i - n];
			i--;
		}
	}
}

/*
**	\brief	Décalage de caractère vers la gauche
**
**	shift_char_left() décale de _n_ positions vers la gauche les caractères
**	de la chaîne _str_.
*/

void	shift_char_left(char *str, int n)
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
**	\return	**0** si l'insertion s'est effectuée correctement, **-1** en cas
**			d'échec.
**			L'ajout peur échouer si `line` est `NULL` ou que sa taille est trop
**			grande (262144 caractères),
**			ou que le caractère donné n'est pas affichable.
*/

int			insert_char(char **line, char c, t_line *line_info)
{
	if (line && (c >= 32 && c <= 126) && line_info->len <= 262144)
	{
		if (line_info->len == line_info->size)
			*line = (char*)ft_memrealloc(*line, line_info->size,\
											line_info->size += INPUT_BUF_SIZE);
		if (line_info->cursor_i <= line_info->len)
			shift_char_right(&line[0][line_info->cursor_i], 1);
		line[0][line_info->cursor_i++] = c;
		line_info->len += 1;
		return (0);
	}
	return (1);
}
