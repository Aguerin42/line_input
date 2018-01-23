#include "line_input.h"

static void	input_simple(char buf[], char **line, t_line *line_info)
{
	if (!buf[1] && buf[0] > 31 && buf[0] < 127)
	{
		ft_putchar(buf[0]);
		insert_char(line, buf[0], line_info);
		update_info(line_info, *line);
	}
	else if (!buf[1] && buf[0] == 127)
	{
		if (line_info->cursor_i > 0)
		{
			ft_putchar(8);
			ft_putchar(' ');
			ft_putchar(8);
			delete_char(line, buf[0], line_info);
			update_info(line_info, *line);
		}
	}
}

void		input(char **line, t_line *line_info, char *prompt, t_list *history)
{
	char	buf[7];

	if (line)
	{
		buf[0] = 0;
		while (buf[0] != 10 && line_info->size)
		{
			update_info(line_info, *line);
			ft_bzero(buf, 7);
			read(0, buf, 6);
			if (line_info->size && line_info->term)
			{
				if (!check_key(line, buf, line_info, history))
				{
					line_info->cursor_s = -1;
					print_line(*line, *line_info, prompt);
					update_info(line_info, *line);
					replace_cursor(*line_info);
				}
			}
			else
				input_simple(buf, line, line_info);
		}
	}
}
