/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:40:02 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/18 08:31:31 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_strswap(t_data *data, int i[2], char *from, char *to)
{
	char	*save;

	save = from;
	data->cmd_list[i[0]].cmd[++i[1]] = to;
	dh_free(save);
}

int	check_filename(char *filename)
{
	if (filename && access(filename, F_OK) == -1)
	{
		ft_printf(2, BOLD RED"/!\\ " BOLD BEIGE
			"Heredoc file deleted !\n" RESET);
		return (1);
	}
	return (0);
}

void	swap_and_reset(t_data *data, int i[2], char *delim, char *filename)
{
	ft_strswap(data, i, delim, filename);
	filename = NULL;
}

int	handle_here_doc(t_data *data, int i[2])
{
	char	*filename;
	char	*delim;

	i[1] = 0;
	while (data->cmd_list[i[0]].cmd[i[1]])
	{
		filename = NULL;
		if (ft_strcmp("<<", data->cmd_list[i[0]].cmd[i[1]])
			&& data->cmd_list[i[0]].cmd[i[1] + 1])
		{
			filename = start_here_doc(data,
					data->cmd_list[i[0]].cmd[i[1] + 1]);
			delim = data->cmd_list[i[0]].cmd[i[1] + 1];
		}
		if (check_filename(filename))
			return (0);
		if (filename)
			swap_and_reset(data, i, delim, filename);
		else if (ft_strcmp("<<", data->cmd_list[i[0]].cmd[i[1]]))
			return (0);
		i[1]++;
	}
	return (1);
}

int	create_here_doc(t_data *data)
{
	int		i[2];

	i[0] = 0;
	while (data->cmd_list[i[0]].cmd)
	{
		if (!handle_here_doc(data, i))
			return (0);
		i[0]++;
	}
	return (1);
}
