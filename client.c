/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessaadi <oessaadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:43:45 by oessaadi          #+#    #+#             */
/*   Updated: 2024/03/29 00:05:20 by oessaadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && result <= 2147483649)
	{
		result = (result * 10) + str[i++] - '0';
	}
	if (str[i] != '\0')
	{
		write(2, "Invalid PID\n", 13);
		exit(1);
	}
	return (sign * result);
}

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		usleep(600);
		if (((c >> i) & 1) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		write(2, "wrong number of arguments\n", 27);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1)
	{
		write(2, "Invalid PID\n", 13);
		exit(1);
	}
	i = 0;
	while (argv[2][i])
	{
		send_char(pid, argv[2][i]);
		i++;
	}
}
