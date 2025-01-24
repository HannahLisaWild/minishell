/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:11:03 by hawild            #+#    #+#             */
/*   Updated: 2025/01/24 15:05:30 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token_env_var(t_envvar **env_list, t_token *current_token,
		t_command *current_cmd)
{
	char	*env_value;

	env_value = get_env_var(env_list, current_token->value);
	if (env_value)
		current_token->value = ft_strdup(env_value);
	else
		current_token->value = ft_strdup("dontadd");
	if (!current_cmd->args && env_value)
		current_cmd->env_exp = ft_strdup(env_value);
	if (!env_value)
		current_cmd->env_exp = ft_strdup(":still:");
}

void	handle_token_merge_flag(t_envvar **env_list, t_command *current_cmd,
		t_token *current_token, t_shell_status *e_status)
{
	char	*merged_arg;
	char	*temp;

	temp = NULL;
	merged_arg = NULL;
	if (ft_strcmp(current_token->value, "dontadd") != 0)
		merged_arg = ft_strdup(current_token->value);
	else
	{
		merged_arg = ft_strdup("");
		current_token = current_token->next->next;
		if (current_token->type == TOKEN_EXIT_STATUS)
			current_token->value = ft_itoa(e_status->last_exit_status);
		if (current_token->type == TOKEN_ENV_VAR)
			handle_token_env_var(env_list, current_token, current_cmd);
		else if (ft_strcmp(current_token->value, "dontadd") == 0)
			current_token->value = ft_strdup("");
		temp = merged_arg;
		merged_arg = ft_strjoin(temp, current_token->value);
		free(temp);
	}
	current_token->value = ft_strdup(merged_arg);
	current_token->type = TOKEN_WORD;
	free(merged_arg);
}

int	handle_token_input_redirect(t_command **current_cmd,
		t_token **current_token)
{
	if (!(*current_cmd))
	{
		(*current_cmd) = new_command();
		(*current_cmd)->exit_status = 2;
		printf("minishell: syntax error near unexpected token '<'\n");
		return (1);
	}
	if ((*current_cmd)->output_file != NULL)
		(*current_cmd)->output = 1;
	*current_token = (*current_token)->next;
	if (!(*current_token) || ((*current_token)->type != TOKEN_WORD
			&& (*current_token)->type != TOKEN_QUOTE
			&& (*current_token)->type != TOKEN_DOUBLE_QUOTE))
	{
		printf("minishell : syntax error near unexpected token '<'\n");
		(*current_cmd)->exit_status = 2;
		return (1);
	}
	(*current_cmd)->input_file = ft_strdup((*current_token)->value);
	if (access((*current_cmd)->input_file, F_OK) == 0
		&& access((*current_cmd)->input_file, R_OK) != 0)
		(*current_cmd)->exit_status = 127;
	return (0);
}

int	open_outputfile(t_command *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->output_file)
	{
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (access(cmd->output_file, F_OK) == 0 && access(cmd->output_file,
				W_OK) != 0)
			cmd->exit_status = 300;
	}
	return (fd);
}

int	handle_token_output_append(t_command **current_cmd, t_token **current_token,
		t_command **head, t_command **tail)
{
	int	fd;

	if (!(*current_cmd))
	{
		return (handle_first(current_cmd, current_token, head, tail));
	}
	fd = open_outputfile(*current_cmd);
	(*current_cmd)->append = ((*current_token)->type == TOKEN_APPEND_REDIRECT);
	*current_token = (*current_token)->next;
	if (!(*current_token) || ((*current_token)->type != TOKEN_WORD
			&& (*current_token)->type != TOKEN_QUOTE
			&& (*current_token)->type != TOKEN_DOUBLE_QUOTE))
	{
		(*current_cmd) = new_command();
		(*current_cmd)->exit_status = 2;
		printf("minishell: syntax error near unexpected token '>' or '>>'\n");
		return (1);
	}
	(*current_cmd)->output_file = ft_strdup((*current_token)->value);
	return (0);
}
