
#include <stdio.h> // forbidden
#include <unistd.h>
#include <signal.h>

int	power_two(int n)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	while (i < n)
	{
		result *= 2;
		i++;
	}
	return (result);
}

void	handler(int sig)
{
	static char	result;
	static int	i;

	if (sig == SIGUSR2)
		result += power_two(i);
	i++;

	if (i == 8)
	{
		i = 0;
		write(1, &result, 1);
		result = 0;
	}
}


int main()
{
	printf("this is the PID : %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
