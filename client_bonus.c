/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessaadi <oessaadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:43:36 by oessaadi          #+#    #+#             */
/*   Updated: 2024/03/29 00:06:12 by oessaadi         ###   ########.fr       */
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
		usleep(500);
		if (((c >> i) & 1) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
	}
}

void	send_string(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
}

void	message_received(int sig)
{
	if (sig == SIGUSR1)
		write(1, "message received\n", 17);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*client_pid;

	if (argc != 3)
	{
		write(2, "wrong number of arguments\n", 27);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	client_pid = ft_itoa(getpid());
	if (pid < 1)
	{
		write(2, "Invalid PID\n", 13);
		exit(1);
	}
	send_string(pid, client_pid);
	free(client_pid);
	signal(SIGUSR1, message_received);
	send_string(pid, argv[2]);
	sleep(1);
}
