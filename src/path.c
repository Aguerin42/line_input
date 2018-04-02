/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:05:18 by aguerin           #+#    #+#             */
/*   Updated: 2018/04/02 14:06:04 by aguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_input.h"

char	*verif_path(char *path)
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
			{
				ft_putendl_fd("", 2);
				sh_error(1, "in function line input: verif_path");
			}
		}
	return (path);
}

int		first_word(const char *line, int pos)
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

char	**find_path(char *line, char **path, char **word, t_line *info)
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
	{
		ft_putendl_fd("", 2);
		sh_error(1, "line input: find_path");
	}
	return (dpath);
}
