/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessaadi <oessaadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:44:01 by oessaadi          #+#    #+#             */
/*   Updated: 2024/03/29 00:05:37 by oessaadi         ###   ########.fr       */
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

void	handle_signal(int sig)
{
	static int	count;
	static char	c;

	if (sig == SIGUSR1)
		c = (c << 1) | 1;
	else if (sig == SIGUSR2)
		c = c << 1;
	count++;
	if (count == 8)
	{
		write(1, &c, 1);
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
