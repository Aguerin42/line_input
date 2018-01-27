/**
**	\file	line_input.h
**	\author	Alexis Guérin
**	\date	14 décembre 2017
*/

#ifndef LINE_INPUT_H
# define LINE_INPUT_H

# include "libft.h"
# include "libag.h"
# include <stdlib.h>
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>
# include <signal.h>

/**
**	\brief	Taille d'allocation
**
**	L'allocation de la chaîne nécessaire à contenir la commande se fait de
**	4096 en 4096
*/

# define INPUT_BUF_SIZE 4096

/**
**	\brief	Allocation maximale pour la ligne de commande
*/

# define MAX_ALLOC 262144

/**
**	\brief	Informations sur la ligne
*/

/*
**	size		Taille de l'allocation
**	len			Taille de la chaîne
**	cursor_i	Index du curseur dans la chaîne (>= 0)
**	cursor_x	Colonne du curseur sur la ligne
**	cursor_y	Ligne du curseur sur la ligne de commande
**	prompt		Longueur du prompt
**	nb_line		Nombre de ligne nécessaires à l'affichage
**	win_col		Nombre de colonnes de la fenêtre
**	cursor_s	Indice du début/de la fin de la sélection par rapport au curseur
**	term		Booléen indiquant si l'environnement a pu être récupéré ou non
*/

typedef struct	s_line
{
	size_t	size; 		/*!< Taille de l'allocation */
	size_t	len;		/*!< Taille de la chaîne */
	size_t	cursor_i;	/*!< Index du curseur dans la chaîne (>=0) */
	size_t	cursor_x;	/*!< Colonne du curseur sur la ligne */
	size_t	cursor_y;	/*!< Ligne du curseur sur la ligne de commande */
	size_t	prompt;		/*!< Longueur du prompt */
	size_t	nb_line;	/*!< Nombre de ligne nécaissaires à l'affichage */
	size_t	win_col;	/*!< Nombre de colonnes de la fenêtre */
	int		cursor_s;	/*!< Indice du début/de la fin de la séléction par
							 rapport au cursur */
	int		term;		/*!< Booléen indiquand si l'environnement à pu être
							 récupéré ou non */
}				t_line;

/*
**	input.c
*/

t_line			init_line_info(size_t size, char *prompt);
char			*line_input(char *prompt, t_list *history);

/*
**	cursor_motion.c
*/

int				move_cursor_on_line(char m, t_line *line_info);
int				move_ctrl_arrow(char m, char *line, t_line *line_info);

/*
**	edit.c
*/

int				insert_char(char **line, char c, t_line *line_info);
int				delete_char(char **line, char t, t_line *line_info);
int				swap_char(char **line, t_line *line_info);

/*
**	history.c
*/

int				manage_history(char **line, char m, t_line *line_info,
															t_list *history);

/*
**	key.c
*/

int				check_key(char **line, char buf[], t_line *line_info,
															t_list *history);

/*
**	print.c
*/

void			print_line(char *line, t_line line_info, char *prompt);

/*
**	read.c
*/

void			input(char **line, t_line *line_info, char *prompt,
															t_list *history);

/*
**	selection.c
*/

int				selection(char n, char m, char *line, t_line *line_info);

/*
**	selection_edit.c
*/

char			*get_clipboard(char *content, int del);
int				paste_selection(char **line, t_line *line_info);
int				copy_cut_selection(char **line, int cut, t_line *line_info);
int				insert_char_selection(char **line, char c, t_line *line_info);
int				delete_selection(char **line, t_line *line_info);

/*
**	sigleton.c
*/

t_line			*get_line_info(t_line *info);
char			**get_line(char **line);
char			*get_prompt(char *prompt);

/*
**	signal.c
*/

void			launch_signal(void);

/*
**	update.c
*/

int				nb_line(size_t len, size_t col);
void			update_info(t_line *line_i, const char *line);
void			replace_cursor(t_line line_info);

/*
**	debug.c
*/

void			debug_struct(t_line line_info, char *msg);
void			debug_read(char buf[]);

#endif
