/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:04:31 by kforfoli          #+#    #+#             */
/*   Updated: 2025/01/24 14:08:07 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file(t_command *cmd)
{
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
}

void	free_envp(char **envp)
{
	int	i;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	handle_first(t_command **current_cmd, t_token **current_token,
		t_command **head, t_command **tail)
{
	int	fd;

	initialize_new_command(current_cmd, head, tail);
	*current_token = (*current_token)->next;
	(*current_cmd)->output_file = ft_strdup((*current_token)->value);
	fd = open((*current_cmd)->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!(*current_token)->next)
		return (close(fd), 1);
	return (close(fd), 42);
}

int	check_input_status(int input_status, t_shell_status *e_status)
{
	if (input_status == -1)
		return (-1);
	else if (input_status == 2 || input_status == 0)
	{
		if (input_status == 2)
			e_status->last_exit_status = 2;
		return (2);
	}
	return (0);
}
