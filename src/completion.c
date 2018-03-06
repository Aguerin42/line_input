/**
**	\file	completion.c
**	\author	Alexis Guérin
**	\date	12 février 2018
**
**	\brief	Fonctions pour l'utilisation de la complétion
*/

#include "line_input.h"

static char	*verif_path(char *path)
{
	char	*new;
	char	*home;

	if (ft_strnequ(path, "~/", 2))
		if ((home = ft_getenv("HOME", (const char**)get_environ(NULL))))
		{
			if ((new = ft_strnew(ft_strlen(home) + ft_strlen(&path[1]))))
			{
				new = ft_strcpy(new, home);
				new = ft_strcat(new, &path[1]);
				ft_strdel(&path);
				path = new;
			}
			else
				ft_putendl_fd("\nline input: allocation error.", 2);
		}
	return (path);
}

static int	first_word(const char *line, int pos)
{
	int	i;
	int	ret;

	ret = -1;
	if (line)
	{
		ret = 1;
		i = find_begin(line, pos);
		while (--i >= 0 && ag_isspace(line[i]))
			NULL;
		if (i <= 0)
			ret = 1;
		else if (is_shellop(line[i]))
		{
			ret = 1;
			if (line[i] == '>' || line[i] == '<'
				|| (line[i] == '|' && line[i - 1] == '>'))
				ret = 0;
		}
		else
			ret = 0;
	}
	return (ret);
}


static char	**find_path(char *line, char **path, char **word, t_line *info)
{
	char	*env;
	char	**dpath;

	dpath = NULL;
	path ? delete_backslash(*path) : NULL;
	delete_backslash(*word);
	if (!path)
	{
		if (first_word((const char*)line, info->cursor_i))
			env = ft_getenv("PATH", (const char**)get_environ(NULL));
		else
			env = "./";
		dpath = ft_strsplit(env, ':');
	}
	else
	{
		*path = verif_path(*path);
		dpath = ft_strsplit(*path, ':');
	}
	if (!dpath)
		ft_putendl_fd("\nline input: allocation error.", 2);
	return (dpath);
}

static void	insert_part(char **line, char *word, char *insert, t_line *info)
{
	int	i;
	int	e;

	info->cursor_i = find_end((const char*)line[0], info->cursor_i);
	e = info->cursor_i;
	i = 0;
	while (--e >= 0 && line[0][e] != '/' && (line[0][e] != ' ' ||
			(e > 0 && line[0][e] == ' ' && line[0][e - 1] == '\\')))
		i++;
	info->cursor_i = e + i + 1;
	if (word[0] == '$')
		i--;
	while (i >= 0 && insert[i])
		insert_char(line, insert[i++], info);
	if (insert[0] && insert[i - 1] != '/')
		insert_char(line, ' ', info);
}

static void	choice(char **line, t_line *info, char **ret)
{
	int i;

	i = -1;
	while (ret[++i])
		ret[i] = insert_backslash(ret[i]);
	i = nb_line(info->len, info->win_col);
	while ((size_t)i-- > info->cursor_y)
		ft_putstr(tgetstr("do", NULL));
	ft_putendl("");
	ag_putchoice((const char**)ret);
	ag_putstrs(get_prompt(NULL));
	ft_putstr(*line);
	replace_cursor(*info);
}

/**
**	\brief	Complétion de la ligne de commande
**
**	\param	line	- ligne de commande
**	\param	info	- structure contenant les informations nécessaires à
**					*line_input*
**
**	\return	**0** en cas de succès et que la ligne doit être réaffichée,
**			ou **1** sinon
*/

int			complete_line(char **line, t_line *info)
{
	char	*part;
	char	*path;
	char	*word;
	char	**ret;
	char	**dpath;

	int		val = 1;
	if (line && info
		&& (part = cut_command((const char*)*line, info->cursor_i)))
	{
		word = NULL;
		path = NULL;
		if (!cut_path_word(part, &path, &word) && word)
		{	
			if ((dpath = find_path(*line, path ? &path : NULL, &word, info)))
			{
				if ((ret = completion(word[0] == '$' ? &word[1] : word,
					word[0] == '$' ? NULL : (const char **)dpath,
					word[0] == '$' ? (const char**)get_environ(NULL) : NULL,
					NULL)))
				{
					if (ret[0] && !ret[1])
					{
						ret[0] = insert_backslash(ret[0]);
						word = insert_backslash(word);
						insert_part(line, word, ret[0], info);
						val = 0;
					}
					else
						choice(line, info, ret);
					ag_strdeldouble(&ret);
				}
				ag_strdeldouble(&dpath);
			}
			ft_strdel(&word);
		}
		path ? ft_strdel(&path) : NULL;
		ft_strdel(&part);
		return (val);
	}
	return (1);
}
