#include "line_input.h"

static char	*clipboard(char *content, int del)
{
	static char	*clipboard = NULL;

	if ((del || content) && clipboard)
		ft_strdel(&clipboard);
	if (content)
		clipboard = ft_strdup(content);
	return (clipboard);
}
int	copy_selection(char **line, t_line	*line_info)
{
	int		i;
	int		s;
	char	*copy;

	if (line && *line && line_info && line_info->cursor_s >= 0)
	{
		i = (int)line_info->cursor_i;
		s = line_info->cursor_s;
		if (i > s)
			ft_swap(&i, &s);
		if (s == (int)line_info->len)
			s--;
		ft_putnbr_fd(s - i + 1, 2);
		clipboard((copy = ft_strsub(*line, i, s - i + 1)), 0);
		ft_putendl_fd(clipboard(NULL, 0), 2);
		if (copy)
			ft_strdel(&copy);
	}
	return (1);
}

/*
**	\brief	Insertion d'un caractère à la place du ou des caratères sélectionnés
*/

int	insert_char_selection(char **line, char c, t_line *line_info)
{
	if (line && *line && line_info)
	{
		delete_selection(line, line_info);
		insert_char(line, c, line_info);
		return (0);
	}
	return (1);
}

/*
**	\brief	Suppression du ou des caractères sélectionnés
*/

int	delete_selection(char **line, t_line *line_info)
{
	int	tmp;

	if (line && *line && line_info && line_info->len)
	{
		if ((int)line_info->cursor_i > line_info->cursor_s)
		{
			tmp = (int)line_info->cursor_i;
			line_info->cursor_i = line_info->cursor_s;
			line_info->cursor_s = tmp;
		}
		while (line_info->cursor_s-- >= (int)line_info->cursor_i)
			delete_char(line, 4, line_info);
		return (0);
	}
	return (1);
}
