/**
**	\file	completion.c
**	\author	Alexis Guérin
**	\date	12 février 2018
**
**	\brief	Fonctions pour l'utilisation de la complétion
*/

#include "line_input.h"

static int	word_begin(char *line, int i)
{
	while (i > 0 && !ag_isspace(line[i - 1]))
		i--;
	return (i);
}

static int	word_end(char *line, int i, int len)
{
	while (line[i] && i <= len && !ag_isspace(line[i]))
		i++;
	return (i);
}

static char	*word(char *line, t_line *info, int *c)
{
	int		b;
	int		e;
	char	*tmp;

	b = word_begin(line, info->cursor_i);
	e = word_end(line, info->cursor_i, (int)info->len);
	tmp = NULL;
	if (b != e)
		if (!(tmp = ft_strsub(line, b, e - b)))
			ft_putendl_fd("allocation error", 2);
	*c = b;
	return (tmp);
}

/**
**	\brief	Complétion de la ligne de commande
**
**	\param	line	- ligne de commande
**	\param	info	- structure contenant les information nécessaires à
**					*line_input*
**
**	\return	**0** en cas de succès et que la ligne doit être réaffichée,
**			ou **1** sinon
*/

int			complete_line(char **line, t_line *info)
{
	int		c;
	char	*tmp;
	char	**ret;
	char	**path;

	if (line && info)
	{
		path = NULL;
		tmp = word(*line, info, &c);
		if (c)
			path = ft_strsplit("./", ':');
		else
			path = ft_strsplit(ft_getenv("PATH", get_environ(NULL)), ':');
		ret = completion(c != (int)info->cursor_i ? tmp : "", (const char**)path);
		c = -1;
		while (ret[++c])
			ag_putstrs_fd(ret[c], 2);
		ft_putendl_fd("", 2);
		tmp ? ft_strdel(&tmp) : NULL;
		ret ? ag_strdeldouble(&path) : NULL;
		path ? ag_strdeldouble(&path) : NULL;
	}
	return (1);
}
