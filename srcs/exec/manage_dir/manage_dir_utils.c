/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:13:55 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 14:38:14 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	handle_input_redirection(t_data *data, int i, int j)
{
	if (data->redir_fd[0] > 2)
		close(data->redir_fd[0]);
	if (data->cmd_list[i].cmd[j + 1])
		data->redir_fd[0] = open(data->cmd_list[i].cmd[j + 1], O_RDONLY);
}

void	handle_heredoc_redirection(t_data *data, int i, int j)
{
	if (data->redir_fd[0] > 2)
		close(data->redir_fd[0]);
	data->redir_fd[0] = open(data->cmd_list[i].cmd[j + 1], O_RDONLY, 0644);
}

void	handle_output_redirection(t_data *data, int i, int j)
{
	if (data->redir_fd[1] > 2)
		close(data->redir_fd[1]);
	data->redir_fd[1] = open(data->cmd_list[i].cmd[j + 1],
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
}

void	handle_append_redirection(t_data *data, int i, int j)
{
	if (data->redir_fd[1] > 2)
		close(data->redir_fd[1]);
	data->redir_fd[1] = open(data->cmd_list[i].cmd[j + 1],
			O_CREAT | O_WRONLY | O_APPEND, 0644);
}
