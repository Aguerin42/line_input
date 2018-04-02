/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerin <aguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 10:43:04 by aguerin           #+#    #+#             */
/*   Updated: 2018/04/02 10:43:22 by aguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	\file	print.c
**	\author	Alexis Guérin
**	\date	14 décembre 2017
**
**	\brief	Fonctions d'affichage
*/

#include "line_input.h"

static void	swap_cur(t_line *line_info)
{
	int	tmp;

	if (line_info)
	{
		tmp = line_info->cursor_s;
		line_info->cursor_s = line_info->cursor_i;
		line_info->cursor_i = tmp;
	}
}

static void	print_selection(char *line, t_line line_info)
{
	if (line_info.cursor_s > (int)line_info.cursor_i)
		swap_cur(&line_info);
	ag_putnstr(line, line_info.cursor_s);
	ft_putstr(tgetstr("mr", NULL));
	ag_putnstr(&line[line_info.cursor_s],
	line_info.cursor_i - line_info.cursor_s + 1);
	ft_putstr(tgetstr("me", NULL));
	if (line_info.cursor_i + 1 < MAX_ALLOC)
		ft_putstr(&line[line_info.cursor_i + 1]);
}

/*
**	\brief	Affichage de la ligne de commande
**
**	La fonction supprime les lignes déjà affichées et affiche la nouvelle,
**	après le prompt.
**
**	\param	line		- ligne à afficher
**	\param	line_info	- information sur la ligne et la position du curseur
**	\param	prompt		- prompt du Shell
*/

void		print_line(char *line, t_line line_info, char *prompt)
{
	int				y;
	struct winsize	win;

	if (line)
	{
		ioctl(0, TIOCGWINSZ, &win);
		if (line_info.win_col != win.ws_col)
			y = nb_line(line_info.cursor_i + line_info.prompt, win.ws_col);
		else
			y = line_info.cursor_y;
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		while (--y > 0)
			ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("cd", NULL), 0, 0));
		ag_putstrs(prompt);
		if (line_info.cursor_s > -1)
			print_selection(line, line_info);
		else
			ft_putstr(line);
	}
}
