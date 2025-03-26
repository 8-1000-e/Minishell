/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:19:06 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/25 14:48:12 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	handle_redirection_removal(t_data *data, int i, int j)
{
	int		h;
	int		save_j;
	char	*save_str[2];

	h = j + 1;
	save_j = j;
	save_str[0] = data->cmd_list[i].cmd[j];
	save_str[1] = data->cmd_list[i].cmd[j + 1];
	while (data->cmd_list[i].cmd[j])
		data->cmd_list[i].cmd[j++] = data->cmd_list[i].cmd[h++];
	j = save_j;
	h = save_j + 1;
	while (data->cmd_list[i].cmd[j])
		data->cmd_list[i].cmd[j++] = data->cmd_list[i].cmd[h++];
	if (!data->cmd_list[i].builtin)
	{
		dh_free(save_str[0]);
		dh_free(save_str[1]);
	}
}

void	remove_redirections_from_cmd(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->cmd_list[i].cmd[j])
	{
		if (data->cmd_list[i].cmd[j][0] == '<' ||
			data->cmd_list[i].cmd[j][0] == '>')
		{
			handle_redirection_removal(data, i, j);
		}
		else
			j++;
	}
}

void	process_redirections(t_data *data, int i, int j)
{
	if (ft_strcmp(data->cmd_list[i].cmd[j], "<")
		&& !check_error(data, i, j, "<"))
		handle_input_redirection(data, i, j);
	else if (ft_strcmp(data->cmd_list[i].cmd[j], "<<")
		&& !check_error(data, i, j, "<<"))
		handle_heredoc_redirection(data, i, j);
	else if (ft_strcmp(data->cmd_list[i].cmd[j], ">")
		&& !check_error(data, i, j, ">"))
		handle_output_redirection(data, i, j);
	else if (ft_strcmp(data->cmd_list[i].cmd[j], ">>")
		&& !check_error(data, i, j, ">>"))
		handle_append_redirection(data, i, j);
}

void	manage_exec_dir(t_data *data, int i)
{
	int	j;

	j = 0;
	if (data->cmd_list[i].cmd)
	{
		while (data->cmd_list[i].cmd[j])
		{
			process_redirections(data, i, j);
			j++;
		}
		remove_redirections_from_cmd(data, i);
	}
}
