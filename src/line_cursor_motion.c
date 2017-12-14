#include "line_input.h"

int	move_cursor_on_line(char m, t_line *line_info)
{
	if (m == 68 && line_info->cursor_i > 0)
		line_info->cursor_i -= 1;
	else if (m == 67 && line_info->cursor_i < line_info->len)
		line_info->cursor_i += 1;
	else
		return (1);
	return (0);
}
