/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawild <hawild@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:12:30 by hawild            #+#    #+#             */
/*   Updated: 2025/01/23 00:22:18 by hawild           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_token_heredoc(t_token **current_token, t_command **current_cmd,
		t_command **head, t_command **tail)
{
	if (!(*current_cmd))
	{
		(*current_cmd) = new_command();
		if (!(*head))
			(*head) = (*current_cmd);
		if (*tail)
			(*tail)->next = *current_cmd;
		*tail = *current_cmd;
	}
	*current_token = (*current_token)->next;
	if (!(*current_token) || (*current_token)->type != TOKEN_WORD)
	{
		(*current_cmd)->exit_status = 2;
		printf("minishell: syntax error near unexpected token '<<'\n");
		return (1);
	}
	(*current_cmd)->heredoc_delim = ft_strdup((*current_token)->value);
	return (0);
}

int	handle_token_pipe(t_token **current_token, t_command **current_cmd,
		t_command **tail)
{
	if (!(*current_cmd))
	{
		(*current_cmd) = new_command();
		(*current_cmd)->exit_status = 2;
		printf("minishell: syntax error\n");
		return (1);
	}
	if (!(*current_token)->next)
	{
		printf("minishell: syntax cannot end with pipe\n");
		(*current_cmd)->exit_status = 2;
		return (1);
	}
	if (*current_cmd)
	{
		*tail = *current_cmd;
		*current_cmd = NULL;
	}
	return (0);
}

void	initialize_new_command(t_command **current_cmd, t_command **head,
		t_command **tail)
{
	*current_cmd = new_command();
	if (!*head)
		*head = *current_cmd;
	else
		(*tail)->next = *current_cmd;
	*tail = *current_cmd;
}

void	handle_exit_status_token(t_token *current_token,
		t_shell_status *e_status)
{
	if (g_execute_external_running != 130 && g_execute_external_running != 131)
	{
		current_token->value = ft_itoa(e_status->last_exit_status);
	}
	else
	{
		if (g_execute_external_running == 130)
		{
			current_token->value = ft_itoa(130);
		}
		else if (g_execute_external_running == 131)
		{
			current_token->value = ft_itoa(131);
		}
		g_execute_external_running = 0;
	}
}
