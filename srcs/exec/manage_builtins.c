/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:39:58 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 15:04:53 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	continue_all_builtin(t_data *data, int i)
{
	if (ft_strcmp(data->cmd_list[i].cmd[0], "env"))
	{
		data->cmd_list[i].builtin = 1;
		manage_exec_dir(data, i);
		data->exit_status = 1;
		cmd_env(data);
		return (1);
	}
	return (0);
}

int	continue_builtin(t_data *data, int i)
{
	if (ft_strcmp(data->cmd_list[i].cmd[0], "echo"))
	{
		data->cmd_list[i].builtin = 1;
		manage_exec_dir(data, i);
		echo(data->cmd_list[i].cmd);
		data->exit_status = 0;
		return (1);
	}
	if (ft_strcmp(data->cmd_list[i].cmd[0], "pwd"))
	{
		data->cmd_list[i].builtin = 1;
		manage_exec_dir(data, i);
		data->exit_status = pwd();
		if (data->exit_status == -1)
			exit_error(data, "failed malloc");
		return (1);
	}
	return (continue_all_builtin(data, i));
}

int	make_all_builtin(t_data *data, int i)
{
	if (ft_strcmp(data->cmd_list[i].cmd[0], "unset"))
	{
		data->cmd_list[i].builtin = 1;
		manage_exec_dir(data, i);
		data->exit_status = cmd_unset(data, data->cmd_list[i].cmd);
		if (data->exit_status == -1)
			exit_error(data, "failed malloc");
		return (1);
	}
	if (ft_strcmp(data->cmd_list[i].cmd[0], "export"))
	{
		data->cmd_list[i].builtin = 1;
		manage_exec_dir(data, i);
		data->exit_status = export(data, data->cmd_list[i].cmd);
		if (data->exit_status == -1)
			exit_error(data, "failed malloc");
		return (1);
	}
	return (continue_builtin(data, i));
}

int	make_builtin(t_data *data, int i)
{
	if (ft_strcmp(data->cmd_list[i].cmd[0], "exit"))
	{
		data->cmd_list[i].builtin = 1;
		manage_exec_dir(data, i);
		ft_exit(data, i);
		return (1);
	}
	if (ft_strcmp(data->cmd_list[i].cmd[0], "cd"))
	{
		data->cmd_list[i].builtin = 1;
		manage_exec_dir(data, i);
		data->exit_status = cd(data, data->cmd_list[i].cmd);
		if (data->exit_status == -1)
			exit_error(data, "failed malloc");
		return (1);
	}
	return (make_all_builtin(data, i));
}
