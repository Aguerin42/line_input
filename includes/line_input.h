#ifndef LINE_INPUT_H
# define LINE_INPUT_H

# include "libft.h"
# include <unistd.h>
# include <term.h>

# define INPUT_BUF_SIZE	50
# define PROMPT			"$>"

/**
**	\brief	Informations sur la ligne
*/

typedef struct	s_line
{
	size_t	size;		/*!< Taille de l'allocation (sans compter le '\0') */
	size_t	len;		/*!< Taille de la chaîne */
	size_t	cursor_i;	/*!< Index du curseur dans la chaîne (>= 0) */
	size_t	cursor_x;	/*!< Colonne du curseur sur la ligne */
	size_t	cursor_y;	/*!< Ligne du curseur sur la ligne */
	size_t	prompt;		/*!< Longueur du prompt */
}				t_line;

/*
**	line_input.c
*/

char	*line_input(size_t pt_len, t_list *history);

#endif
