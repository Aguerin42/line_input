/**
**	\file	signal.c
**	\author	Alexis Guérin
**	\date	23 janvier 2018
*/

#include "line_input.h"

/*
**	\brief	Gestion de `Ctrl`-`C`
*/

static void	ctrlc(int signal)
{
	int		term;
	char	*prompt;
	char	**line;
	t_line	*line_info;

	(void)signal;
	line_info = get_line_info(NULL);
	(line = get_line(NULL)) ? ft_strdel(line) : NULL;
	while (line_info->cursor_y++ < line_info->nb_line)
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
	if ((*line = (char*)ft_memalloc(sizeof(char) * (INPUT_BUF_SIZE + 1))))
	{
		term = line_info->term;
		ft_putendl("");
		prompt = get_prompt(NULL);
		ft_putstrs(prompt);
		*line_info = init_line_info(INPUT_BUF_SIZE, prompt);
		line_info->term = term;
		update_info(line_info, *line);
	}
	else if (line_info && line_info->size)
	{
		line_info->size = 0;
		ft_putendl_fd("\nline_input: allocation error", 2);
	}
}

/*
**	\brief	Signaux à ignorer
*/

static void	catch_unused_sig(int signal)
{
	(void)signal;
}

/**
**	\brief	Gestion des signaux
*/

void		launch_signal(void)
{
	signal(SIGTSTP, catch_unused_sig);
	signal(SIGINT, ctrlc);
}