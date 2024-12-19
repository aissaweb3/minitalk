
#include <string.h> // forbidden
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/*
void	send_bit(char bit, pid_t receiver_pid)
{
	int res;

	res = -1;
	while (res == -1)
	{
		if (bit == 0)
			res = kill(receiver_pid, SIGUSR2);
		else
			res = kill(receiver_pid, SIGUSR1);
	}

	char c = bit + '0';
	write(1, &c, 1);
}
*/

void	send_bit(char bit, pid_t receiver_pid)
{
	int res;


	if (bit == 0)
		res = kill(receiver_pid, SIGUSR1);
	else
		res = kill(receiver_pid, SIGUSR2);

	usleep(100);
}

void	send_message(char *msg, pid_t receiver_pid)
{
	int i;

	while (*msg)
	{
		i = 0;
		char c = *msg;
		while (i < 8)
		{
			send_bit(c % 2, receiver_pid);
			c /= 2;
			i++;
		}
		++msg;
	}
	i = -1;
	while (++i < 8)
		send_bit(0, receiver_pid);
	
}

int main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	pid_t pid = atoi(av[1]);
	send_message(av[2], pid);
}
