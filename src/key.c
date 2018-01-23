#include "line_input.h"

static int	check_key2(char **line, char buf[], t_line *info, t_list *history)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 &&
		buf[4] == 53)
		return (move_ctrl_arrow(buf[5], *line, info));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 &&
			(buf[4] == 50 || buf[4] == 54))
		return (selection(buf[4], buf[5], *line, info));
	else if (buf[0] == 10 && !buf[1])
		return (move_cursor_on_line(70, info));
	else if (buf[0] && !buf[1])
		return (ctrl_key(buf, line, info, history));
	else if (buf[0] == -61 && buf[1] == -89 && !buf[2])
		return (copy_cut_selection(line, 0, info));
	else if (buf[0] == -30 && buf[1] == -119 && buf[2] == -120 && !buf[3])
		return (copy_cut_selection(line, 1, info));
	else if (buf[0] == -30 && buf[1] == -120 && buf[2] == -102 && !buf[3])
		return (paste_selection(line, info));
	return (1);
}

/*
**	\brief	Vérification de la touche tappée
*/

int			check_key(char **line, char buf[], t_line *info, t_list *history)
{
	if (line && info && info->size)
	{
		if ((buf[0] >= 32 && buf[0] <= 126) && !buf[1])
			if (info->cursor_s == -1)
				return (insert_char(line, buf[0], info));
			else
				return (insert_char_selection(line, buf[0], info));
		else if (buf[0] == 127 || (buf[0] == 27 && buf[1] == 91\
					&& buf[2] == 51 && buf[3] == 126 && !buf[4]))
			if (info->cursor_s == -1)
				return (delete_char(line, buf[0], info));
			else
				return (delete_selection(line, info));
		else if ((buf[0] == 27 && buf[1] == 91 && !buf[3]) &&
				(buf[2] == 68 || buf[2] == 67 || buf[2] == 72 || buf[2] == 70))
			return (move_cursor_on_line(buf[2], info));
		else if ((buf[0] == 27 && buf[1] == 91 && !buf[3]) &&
				(buf[2] == 65 || buf[2] == 66))
			return (manage_history(line, buf[2], info, history));
		else
			return (check_key2(line, buf, info, history));
	}
	return (1);
}

int			ctrl_key(char buf[], char **line, t_line *info, t_list *history)
{
	if (buf[0] == 1 || buf[0] == 5)
		return (move_cursor_on_line(buf[0], info));
	else if (buf[0] == 8 || (buf[0] == 4 && info->len))
		return (delete_char(line, buf[0], info));
	else if (buf[0] == 12)
		ft_putstr(tgoto(tgetstr("cl", NULL), 0, 0));
	else if (buf[0] == 14)
		return (manage_history(line, 66, info, history));
	else if (buf[0] == 16)
		return (manage_history(line, 65, info, history));
	else if (buf[0] == 20)
		return (swap_char(line, info));
	else if (buf[0] == 4)
	{
		ft_strcpy(*line, "exit");
		buf[0] = 10;
		return (1);
	}
	else
		return (1);
	return (0);
}
