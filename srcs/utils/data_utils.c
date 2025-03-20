/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:09:55 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 14:48:03 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	assign_absolute_path(t_data *data, int j)
{
	char	*abs_path;

	abs_path = absolute_path(data, j);
	if (abs_path)
	{
		data->cmd_list[j].path = abs_path;
	}
}

char	*find_valid_path(char **paths, char *cmd)
{
	char	*tmp_path;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoinfree(tmp_path, cmd, 1);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		dh_free(full_path);
		i++;
	}
	return (NULL);
}

void	delete_cmd(t_data *data, int i)
{
	t_cmd	cmd_tmp;

	cmd_tmp = data->cmd_list[i];
	while (data->cmd_list[i].cmd)
	{
		data->cmd_list[i] = data->cmd_list[i + 1];
		i++;
	}
	ft_free_tab(cmd_tmp.cmd);
	dh_free(cmd_tmp.path);
}

void	handler_var_env(t_data *data)
{
	int		i;
	char	*value_epur;

	value_epur = NULL;
	i = 1;
	while (data->cmd_list[0].cmd[i])
	{
		value_epur = build_var_env(data->cmd_list[0].cmd[i],*data);
		data->cmd_list[0].cmd[i++] = value_epur;
	}
}

void	fill_data(t_data *data, char **full_line, char *line)
{
	fill_command(data, full_line);
	sort_cmd(data);
	dh_free(full_line);
	fill_paths(data);
	handler_var_env(data);
	data->redir_fd[0] = 0;
	data->redir_fd[1] = 0;
	data->line = line;
	keep_data(data);
	add_history(line);
}
