/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:43:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/24 10:55:57 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	var_is_valid(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0)
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] == '@' || arg[i] == '!'
			|| arg[i] == '"' || arg[i] == '\\' || arg[i] == '\'')
			return (false);
		i++;
	}
	return (true);
}

int	add_env_variable(char *arg, t_env **env)
{
	t_env	*new;
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (var_is_valid(arg) == false)
		{
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			return (1);
		}
		if (ft_strncmp(arg, tmp->data, ft_strlen_export(arg)) == 0
			&& ft_strlen_export(tmp->data) == ft_strlen_export(arg))
		{
			ft_delete_list_node(env, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	new = ft_create_new_node(arg);
	ft_add_at_tail(env, new);
	return (0);
}

// prints every entry with the value between quotes ("")
void	print_export(char *env_export)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 12);
	while (env_export[i] != '\0')
	{
		write (1, &env_export[i], 1);
		if (env_export[i] == '=')
			write(1, "\"", 1);
		i++;
	}
	if (ft_strchr(env_export, '=') != NULL)
		write(1, "\"", 1);
	write(1, "\n", 1);
}
