#include "line_input.h"

static int	alter_line(char **line, t_line *line_info, char *new)
{
	size_t	len;

	if (line && line_info && new)
	{
		len = ft_strlen(new);
		ft_bzero(*line, line_info->len);
		if (line_info->size < len)
			if (!(*line = (char*)ft_memrealloc(*line, line_info->size,\
								line_info->size + (len - line_info->size) + 1)))
			{
				line_info->size = 0;
				return (ft_putendl_fd("line_input: allocation error.", 2));
			}
		ft_strcpy(*line, new);
		line_info->cursor_i = len;
		return (0);
	}
	return (1);
}

int	manage_history(char **line, char m, t_line *line_info, t_list *history)
{
	static t_list	*list = NULL;

	if (history && line && line_info)
	{
		if (!list && m == 65)
			list = history;
		else if (m == 65 && list && list->next)
			list = list->next;
		else if (m == 66 && list)
			list = list->prev;
		if (list)
			return (alter_line(line, line_info, list->content));
		return (0);
	}
	return (1);
}
