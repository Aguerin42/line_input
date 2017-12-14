#ifndef LINE_INPUT_H
# define LINE_INPUT_H

# include "libft.h"
# include <unistd.h>
# include <term.h>

# define INPUT_BUF_SIZE	4096

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

/*
**	line_cursor_motion.c
*/

int		move_cursor_on_line(char m, t_line *line_info);

/*
**	line_edit.c
*/

int		insert_char(char **line, char c, t_line *line_info);
int		delete_char(char **line, char t, t_line *line_info);

#endif
