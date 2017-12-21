#ifndef LINE_INPUT_H
# define LINE_INPUT_H

# include "libft.h"
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>

# define INPUT_BUF_SIZE	50 // :4096

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
	size_t	nb_line;	/*!< Nombre de ligne nécessaires pour l'affichage */
	size_t	win_col;	/*!< Nombre de colonnes de la fenêtre */
}				t_line;

/*
**	line_input.c
*/

int				nb_line(size_t len, size_t col);
char			*line_input(size_t pt_len, const t_list *history);

/*
**	line_cursor_motion.c
*/

int				move_cursor_on_line(char m, t_line *line_info);
void			replace_cursor(t_line line_info);

/*
**	line_edit.c
*/

int				insert_char(char **line, char c, t_line *line_info);
int				delete_char(char **line, char t, t_line *line_info);

/*
**	line_print.c
*/

void			print_line(char *line, t_line line_info);

#endif
