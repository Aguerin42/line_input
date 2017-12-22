#ifndef LINE_INPUT_H
# define LINE_INPUT_H

# include "libft.h"
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>

# define INPUT_BUF_SIZE	4096

/*
**	\brief	Informations sur la ligne
**
**	size		Taille de l'allocation (sans compter le '\0')
**	len			Taille de la chaîne
**	cursor_i	Index du curseur dans la chaîne (>= 0)
**	cursor_x	Colonne du curseur sur la ligne
**	cursor_y	Ligne du curseur sur la ligne
**	prompt		Longueur du prompt
**	nb_line		Nombre de ligne nécessaires pour l'affichage
**	win_col		Nombre de colonnes de la fenêtre
*/

typedef struct	s_line
{
	size_t	size;
	size_t	len;
	size_t	cursor_i;
	size_t	cursor_x;
	size_t	cursor_y;
	size_t	prompt;
	size_t	nb_line;
	size_t	win_col;
}				t_line;

/*
**	line_input.c
*/

int				nb_line(size_t len, size_t col);
char			*line_input(char *prompt, const t_list *history);

/*
**	line_ctrl.c
*/

int				ctrl_key(char buf[], char **line, t_line *line_info);

/*
**	line_cursor_motion.c
*/

int				move_cursor_on_line(char m, t_line *line_info);
int				move_to_word(char m, char *line, t_line *line_info);
void			replace_cursor(t_line line_info);

/*
**	line_edit.c
*/

int				insert_char(char **line, char c, t_line *line_info);
int				delete_char(char **line, char t, t_line *line_info);
int				swap_char(char **line, t_line *line_info);

/*
**	line_print.c
*/

void			print_line(char *line, t_line line_info);

#endif
