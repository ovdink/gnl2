#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;

	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);


	int n = 5;
	int gnl;
	while((gnl = get_next_line(p[0], &line)) && n--)
	{
		printf("gnl: %d, str: %s\n", gnl, line);
		free(line);
		line = 0x0;
	}
		printf("gnl: %d, str: %s\n", gnl, line);
}
