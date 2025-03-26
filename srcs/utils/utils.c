/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:00:32 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/25 15:22:03 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	exit_error(t_data *data, char *msg)
{
	if (data)
		reset_data_here(data);
	if (msg)
		ft_printf(2, BOLD RED"/!\\ " BOLD BEIGE "%s!\n"RESET, msg);
	exit(2);
}

char	*relatif_cmd(char *str)
{
	char	*path;
	char	p[1024];

	getcwd(p, sizeof(p));
	str += 3;
	while (p[ft_strlen(p) - 1] != '/')
		p[ft_strlen(p) - 1] = '\0';
	path = ft_strjoin(p, str);
	if (!path)
		exit_error(NULL, "failed malloc");
	return (path);
}

char	*absolute_path(t_data *data, int j)
{
	struct stat	sb;
	char		*cmd;

	cmd = data->cmd_list[j].cmd[0];
	if (!ft_strncmp(cmd, "../", 3))
	{
		if (stat(relatif_cmd(cmd), &sb) == 0 && (sb.st_mode & S_IXUSR))
			return (ft_strdup(relatif_cmd(cmd)));
	}
	if (!ft_strncmp(cmd, "./", 2))
	{
		if (stat(cmd, &sb) == 0 && (sb.st_mode & S_IXUSR))
			return (ft_strdup(cmd));
	}
	if (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/')
	{
		if (stat(cmd, &sb) == 0 && (sb.st_mode & S_IXUSR))
			return (ft_strdup(cmd));
	}
	return (NULL);
}

t_data	*keep_data(t_data *data)
{
	static t_data	*d = 0;

	if (data)
		d = data;
	return (d);
}

int	check_for_cmd(t_data *data, int i)
{
	int	j;
	int	cmd_count;

	cmd_count = 0;
	j = 0;
	while (data->cmd_list[i].cmd && data->cmd_list[i].cmd[j])
	{
		if (ft_strchr("<>", data->cmd_list[i].cmd[j][0]) && j++)
			continue ;
		if (j > 0 && data->cmd_list[i].cmd && data->cmd_list[i].cmd[0]
			&& data->cmd_list[i].cmd[j + 1]
			&& (!ft_strchr("<>", data->cmd_list[i].cmd[j + 1][0])
			|| !ft_strchr("<>", data->cmd_list[i].cmd[j - 1][0])))
			cmd_count = 1;
		if (j == 0 && data->cmd_list[i].cmd && data->cmd_list[i].cmd[0]
			&& data->cmd_list[i].cmd[j + 1]
			&& !ft_strchr("<>", data->cmd_list[i].cmd[j + 1][0]))
			cmd_count = 1;
		if (j > 0 && !data->cmd_list[i].cmd[j + 1]
			&& !ft_strchr("<>", data->cmd_list[i].cmd[j - 1][0]))
			cmd_count = 1;
		j++;
	}
	return (cmd_count);
}
