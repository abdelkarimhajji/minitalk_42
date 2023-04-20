/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:11:08 by ahajji            #+#    #+#             */
/*   Updated: 2023/04/20 00:26:03 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	st;
	int	result;

	st = 1;
	i = 0;
	result = 0;
	while ((str[i] == 32 || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			st *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * st);
}

int	leng_int(int number)
{
	int	i;

	i = 0;
	while (number)
	{
		i++;
		number /= 2;
	}
	return (i);
}

void	send_0_or_1(char *ptr3, int pid, int tmp)
{
	int	j;
	int	leng;

	leng = leng_int(tmp);
	j = 0;
	while (leng < 8)
	{
		kill(pid, SIGUSR1);
		usleep(250);
		leng++;
	}
	while (ptr3[j])
	{
		if (ptr3[j] == '0')
		{
			kill(pid, SIGUSR1);
			usleep(250);
		}
		else
		{
			kill(pid, SIGUSR2);
			usleep(250);
		}
		j++;
	}
}

void	send_signal(char *ptr, int pid)
{
	int		i;
	int		j;
	char	*ptr3;
	int		number;
	int		tmp;

	i = 0;
	while (ptr[i])
	{
		number = ptr[i];
		tmp = number;
		j = leng_int(number);
		ptr3 = malloc(j);
		ptr3[j--] = '\0';
		while (number)
		{
			ptr3[j] = (number % 2) + 48;
			j--;
			number /= 2;
		}
		send_0_or_1(ptr3, pid, tmp);
		free(ptr3);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*ptr;

	if (argc != 3)
	{
		write(1,"Eroor\n", 6);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	ptr = argv[2];
	send_signal(ptr, pid);
	return (0);
}
