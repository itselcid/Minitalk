/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessaadi <oessaadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:43:54 by oessaadi          #+#    #+#             */
/*   Updated: 2024/03/29 00:05:32 by oessaadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int nb)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		n = n % 10 + '0';
		write(1, &n, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		n = n % 10 + '0';
		write(1, &n, 1);
	}
}

void	process_pid(int *pid_received, int *client_pid, char c)
{
	if (*pid_received == 0)
	{
		if (c == '\0')
		{
			*pid_received = 1;
		}
		else
			*client_pid = *client_pid * 10 + (c - '0');
	}
	else
	{
		if (c != '\0')
			write(1, &c, 1);
		else
		{
			kill(*client_pid, SIGUSR1);
			*pid_received = 0;
			*client_pid = 0;
		}
	}
}

void	handle_signal(int sig)
{
	static int	client_pid;
	static int	pid_received;
	static int	count;
	static char	c;

	if (sig == SIGUSR1)
		c = (c << 1) | 1;
	else if (sig == SIGUSR2)
		c = c << 1;
	count++;
	if (count == 8)
	{
		process_pid(&pid_received, &client_pid, c);
		c = 0;
		count = 0;
	}
}

int	main(void)
{
	write(1, "PID:", 5);
	ft_putnbr(getpid());
	write(1, "  ", 3);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
