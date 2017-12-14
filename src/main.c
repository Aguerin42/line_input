/**
**	\file	main.c
**	\author	Alexis Guérin
**	\date	7 décembre 2017
*/

#include "line_input.h"
#include <term.h>
#include <stdlib.h>

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
	return (0);
}
