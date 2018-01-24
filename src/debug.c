#include "line_input.h"

void	debug_struct(t_line line_info, char *msg)
{
	ft_putendl_fd(msg, 2);
	ft_putstr_fd("col : ", 2);
	ft_putnbr_fd(line_info.win_col, 2);
	ft_putstr_fd("\nsize : ", 2);
	ft_putnbr_fd(line_info.size, 2);
	ft_putstr_fd(" len : ", 2);
	ft_putnbr_fd(line_info.len, 2);
	ft_putstr_fd("\ncursor_i : ", 2);
	ft_putnbr_fd(line_info.cursor_i, 2);
	ft_putstr_fd(" cursor_s : ", 2);
	ft_putnbr_fd(line_info.cursor_s, 2);
	ft_putstr_fd(" cursor_x : ", 2);
	ft_putnbr_fd(line_info.cursor_x, 2);
	ft_putstr_fd(" cursor_y : ", 2);
	ft_putnbr_fd(line_info.cursor_y, 2);
	ft_putendl_fd("\n", 2);
}
