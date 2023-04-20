/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:31:56 by ahajji            #+#    #+#             */
/*   Updated: 2023/04/20 00:58:21 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	count_dicimal(int *two, int *com)
{
	int	i;

	*two = 2;
	i = 1;
	while (i < *com)
	{
		*two = *two * 2;
		i++;
	}
}

int	convert_disimal(int number)
{
	int	com;
	int	tmp;
	int	two;

	com = 0;
	tmp = 0;
	while (number)
	{
		if (number % 2 == 1)
		{
			if (com == 0)
				tmp = 1;
			else
			{
				count_dicimal(&two, &com);
				tmp += two;
			}
		}
		number /= 10;
		com++;
	}
	return (tmp);
}

void	handler(int signo, siginfo_t *info, void *context)
{
	static int	count;
	static int	tmp;
	int			k;
	static int	id;

	if (id == 0)
		id = info->si_pid;
	if (id != info->si_pid)
	{
		id = info->si_pid;
		tmp = 0;
		count = 0;
	}
	count++;
	if (signo == 30)
		tmp = (tmp * 10) + 0;
	else if (signo == 31)
		tmp = (tmp * 10) + 1;
	if (count == 8)
	{
		k = convert_disimal(tmp);
		write(1, &k, 1);
		count = 0;
		tmp = 0;
	}
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	act;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
