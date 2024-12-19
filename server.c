
#include <stdio.h> // forbidden
#include <unistd.h>
#include <signal.h>

void	handler(int sig)
{
	static char	result;
	static int	i;

	if (sig == SIGUSR2)
		result |= 0b00000001 << i;

	i++;

	if (i == 8)
	{
		i = 0;
		if (result == 0)
			write(1, "\n", 1);
		else
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
