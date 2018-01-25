/**
**	\file	sigleton.c
**	\author	Alexis Guérin
**	\date	23 janvier 2018
**
**	\brief	Fonctions contentant des variables `static`
*/

#include "line_input.h"

/**
**	\brief	Pointeur sur la structure `t_line`
**
**	Pour initialiser le sigleton, l'appel devra s'effectuer en donnant le
**	pointeur de la structure en paramètre de la fonction.
**	Pour simplement récupérer le pointeur sur la stucture, le paramètre `info`
**	devra être `NULL`
*/

t_line	*get_line_info(t_line *info)
{
	static t_line	*line_info = NULL;

	if (info)
		line_info = info;
	return (line_info);
}

/**
**	\brief	Pointeur sur la chaîne de caractères de la ligne
**
**	Pour initialiser le sigleton, l'appel devra s'effectuer en donnant le
**	pointeur de la chaîne de caractères en paramètre de la fonction.
**	Pour simplement récupérer le pointeur sur la chaîne, le paramètre `line`
**	devra être `NULL`
*/

char	**get_line(char **line)
{
	static char	**save_line = NULL;

	if (line)
		save_line = line;
	return (save_line);
}

/**
**	\brief	Chaîne de caractères pour le prompt
**
**	Pour initialiser le sigleton, l'appel devra s'effectuer en donnant la
**	chaîne de caractères en paramètre de la fonction.
**	Pour simplement récupérer la chaîne, le paramètre `prompt` devra être `NULL`
*/

char	*get_prompt(char *prompt)
{
	static char	*save_prompt = NULL;

	if (prompt)
		save_prompt = prompt;
	return (save_prompt);
}
