/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_here_doc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:16:52 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 14:47:02 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*random_name(void)
{
	int		fd;
	char	*s;
	char	c;
	int		i;

	i = 1;
	c = 0;
	s = ft_calloc(50, 1);
	if (!s)
		return (NULL);
	*s = '.';
	fd = open("/dev/urandom", O_RDONLY);
	if (fd >= 0)
	{
		while (i < 48)
		{
			read(fd, &c, 1);
			if (ft_strchr(RDM_NAME, c))
				s[i++] = c;
		}
	}
	if (fd > 2)
		close(fd);
	return (s);
}

int	destroy_here_doc(t_data *data)
{
	int	i;

	i = 0;
	while (data->here_doc_name && data->here_doc_name[i])
	{
		unlink(data->here_doc_name[i]);
		dh_free(data->here_doc_name[i]);
		i++;
	}
	dh_free(data->here_doc_name);
	return (0);
}

void	child_fork(t_data *data, char *rdm_name, char *lim)
{
	char	*line;
	int		fd;

	line = NULL;
	rl_clear_history();
	rl_catch_signals = 1;
	fd = open(rdm_name, O_CREAT | O_WRONLY, 0644);
	keep_fd(fd);
	write_fd(fd, line, lim, data);
}
