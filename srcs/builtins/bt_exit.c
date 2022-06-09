/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:47:54 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/09 12:38:28 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

// checks if the argument is numeric. Takes into account the - or + that can
// prefix the argument. it will return true if the argument is numeric and
// false if not
bool	is_arg_valid(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-' && arg[i] != '+' && '0' > arg[i] && arg[i] > '9')
		return (false);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) != 1)
			return (false);
		i++;
	}
	return (true);
}

// converts the numeric argument in base 256 to provide the correct error code
void	handle_valid_arg(t_shell *shell, char *arg)
{
	int	code;

	code = ft_atoi(arg);
	if (0 <= code)
		if (code > 255)
			code %= 256;
	else
	{
		code *= -1;
		if (code > 256)
			code %= 256;
		code = 256 - (code);
	}
	free_case_exit(shell);
	exit(code);
}

void	handle_invalid_arg(t_shell *shell, char *arg)
{
	printf("bash: exit: %s: numeric argument required", arg);
	free_case_exit(shell);
	exit(2);
}

// built in function exit. allows the user to quit the program at any given
// time by calling it.
// here's how it works:
// 	- if exit doesn't get any argument, it will return the exit status of
// 		the last executed function / program
// 	- if exit get more than one argument, it will print an error message
// 		and return 2
// 	- if exit get a non numeric argument, it will print an error message
// 		and return 2
// 	- if exit gets a numeric argument:
// 		- if this argument is <256, it will return the argument.
// 		- if this argument is >0, it will return 256 - the unsigned value
// 			of the argument. it works in base 256.
// 		- if this argument is >256, it will return the % arg.
// A few specific numbers:
// 1		Catchall for general errors
// 2		Misuse of shell builtins (according to Bash documentation)
// 126		Command invoked cannot execute
// 127		Command not found
// 128		Invalid argument to exit command
// 128+n	Fatal error signal “n”
// 130		Bash script terminated by Control-C
// 255*	Exit status out of range
void	built_in_exit(t_shell *shell, char **cmd_args)
{
	if (!cmd_args[1])
	{
		free_case_exit(shell);
		exit(shell->exit_status);
	}
	else if (cmd_args[2])
	{
		printf("bash: exit: too many arguments");
		free_case_exit(shell);
		exit(2);
	}
	else if (cmd_args[1] && is_arg_valid(cmd_args[1]) == true)
		handle_valid_arg(shell, cmd_args[1]);
	else if (cmd_args[1] && is_arg_valid(cmd_args[1]) == false)
		handle_invalid_arg(shell, cmd_args[1]);
}
