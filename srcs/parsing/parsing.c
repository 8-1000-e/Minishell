/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:06:28 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/25 11:35:51 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	add_error(t_data *data, int i, int *error, int error_code)
{
	data->cmd_list[i].error++;
	*error += error_code;
	return (1);
}

int	finish_check_error(t_data *data, int i, int j, int *error)
{
	if (ft_strcmp(data->cmd_list[i].cmd[j], ">>"))
	{
		if (!data->cmd_list[i].cmd[j + 1] && add_error(data, i, error, 2))
			ft_printf(2, BOLD RED"/!\\ "
				BOLD BEIGE "Shellokitty: syntax error near \"<\"\n" RESET);
		else if (access(data->cmd_list[i].cmd[j + 1], F_OK) != -1
			&& access(data->cmd_list[i].cmd[j + 1], W_OK) == -1
			&& add_error(data, i, error, 1))
			ft_printf(2, BOLD RED"/!\\ "
				BOLD BEIGE "Shellokitty: %s: %s: Permission denied \n",
				data->cmd_list[i].cmd[0], data->cmd_list[i].cmd[j + 1]);
	}
	else if (ft_strcmp(data->cmd_list[i].cmd[j], ">"))
	{
		if (!data->cmd_list[i].cmd[j + 1] && add_error(data, i, error, 2))
			ft_printf(2, BOLD RED"/!\\ "
				BOLD BEIGE "Shellokitty: syntax error near \">\"\n" RESET);
	}
	return (1);
}

int	check_error(t_data *data, int i, int j, char *redir)
{
	int	error;

	error = 0;
	if (!data->cmd_list[i].path && !data->cmd_list[i].builtin)
		error = 127;
	else if (ft_strcmp(redir, "<"))
		check_all_error(data, i, j, error);
	else if (ft_strcmp(redir, "<<"))
		if (!data->cmd_list[i].cmd[j + 1] && add_error(data, i, &error, 2))
			ft_printf(2, BOLD RED"/!\\ "
				BOLD BEIGE "Shellokitty: syntax error near \"<<\"\n" RESET);
	if (finish_check_error(data, i, j, &error) && error != 0)
		exit(error);
	return (0);
}

void	sort_redir(char **full_line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = full_line[0];
	while (full_line[i])
	{
		full_line[i] = full_line[i + 1];
		i++;
	}
	full_line[i - 1] = tmp;
}

void	sort_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_list[i].cmd)
	{
		if (ft_arraylen(data->cmd_list[i].cmd) > 2 && check_for_cmd(data, i))
		{
			while (data->cmd_list[i].cmd[0][0] == '<'
				|| data->cmd_list[i].cmd[0][0] == '>')
			{
				sort_redir(data->cmd_list[i].cmd);
				sort_redir(data->cmd_list[i].cmd);
			}
		}
		i++;
	}
}
