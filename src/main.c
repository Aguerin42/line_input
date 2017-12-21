/**
**	\file	main.c
**	\author	Alexis Guérin
**	\date	7 décembre 2017
*/

#include "line_input.h"
#include <term.h>
#include <stdlib.h>
#define PROMPT "$>"

void		debug(t_line line)
{
	ft_putstr_fd("\nalloc : ", 2);
	ft_putnbr_fd(line.size, 2);
	ft_putstr_fd("\nlen : ", 2);
	ft_putnbr_fd(line.len, 2);
	ft_putstr_fd("\ncursor_i : ", 2);
	ft_putnbr_fd(line.cursor_i, 2);
	ft_putstr_fd("\ncursor_x : ", 2);
	ft_putnbr_fd(line.cursor_x, 2);
	ft_putstr_fd("\ncursor_y : ", 2);
	ft_putnbr_fd(line.cursor_y, 2);
	ft_putstr_fd("\nnb_line : ", 2);
	ft_putnbr_fd(line.nb_line, 2);
	ft_putstr_fd("\nwin_col : ", 2);
	ft_putnbr_fd(line.win_col, 2);
	ft_putstr_fd("\n", 2);
}

static void	set_term(struct termios new)
{
	new.c_lflag &= ~(ICANON);
	new.c_lflag &= ~(ECHO);
	new.c_cc[VTIME] = 0;
	new.c_cc[VMIN] = 1;
	tcsetattr(0, TCSADRAIN, &new);
}

static void	reset_term(struct termios save)
{
	tcsetattr(0, 0, &save);
}

/**
**	\brief	Entrée du programme
*/

int	main(void)
{
//	extern char		**environ;
	char			*line;
	struct termios	save;
	struct termios	new;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &save);
	tcgetattr(0, &new);
	set_term(new);
	ft_putstrs(PROMPT);
	if ((line = line_input(ft_strlen(PROMPT) + 1, NULL)))
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
	line = NULL;
	reset_term(save);
	while (1)
		;
	return (0);
}
