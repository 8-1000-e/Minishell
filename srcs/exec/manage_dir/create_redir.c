/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:25:47 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/17 17:41:51 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	open_redir(t_data *data, char *redir)
{
	int	i;
	int	j;
	int	fd;

	i = 0;
	while (data->cmd_list[i].cmd)
	{
		j = 0;
		while (data->cmd_list[i].cmd[j])
		{
			fd = 0;
			if (ft_strcmp(data->cmd_list[i].cmd[j], redir)
				&& ft_strcmp(redir, ">>") && data->cmd_list[i].cmd[j + 1])
				fd = open(data->cmd_list[i].cmd[j + 1],
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else if (ft_strcmp(data->cmd_list[i].cmd[j], redir)
				&& ft_strcmp(redir, ">") && data->cmd_list[i].cmd[j + 1])
				fd = open(data->cmd_list[i].cmd[j + 1],
						O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd > 2)
				close(fd);
			j++;
		}
		i++;
	}
}

int	create_redir(t_data *data)
{
	open_redir(data, ">>");
	open_redir(data, ">");
	return (1);
}
