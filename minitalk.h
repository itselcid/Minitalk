/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessaadi <oessaadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:11:52 by oessaadi          #+#    #+#             */
/*   Updated: 2024/03/29 00:14:41 by oessaadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

long	ft_atoi(const char *str);
char	*ft_itoa(int n);
void	send_char(int pid, char c);
void	send_string(int pid, char *str);
void	message_received(int sig);

#endif