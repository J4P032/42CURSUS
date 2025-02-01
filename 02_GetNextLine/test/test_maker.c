/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werodrig <werodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:22:26 by werodrig          #+#    #+#             */
/*   Updated: 2025/02/01 20:22:26 by werodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define c_red "\033[31m"
#define c_blue "\033[34m"
#define c_yellow "\033[33m"
#define c_bold "\033[1m"
#define c_null "\033[0m"

void	print(const char *color, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	printf("%s", color);
	vprintf(format, args);
	printf("%s", c_null);
	va_end(args);
}

void	open_terminal(void)
{
	freopen("/dev/tty", "w", stdout);
}

void	close_terminal(void)
{
	//if (!freopen("/dev/null", "w", stdout))
	if (!freopen("__output.txt", "w", stdout))
	{
		print(c_red, "✘ Internal Error: ");
		perror("freopen");
		exit(EXIT_FAILURE);
	}
}

void	test_file(char const *file_name)
{
	int fd = open(file_name, O_RDONLY);

	if (fd == -1)
		return (print(c_red, "✘ No file called: %s\n", file_name));
	char *line;
	int breaker = 0, max_break = 100;

	close_terminal();
	while (++breaker < max_break)
	{
		line = get_next_line(fd);
        if (!line)
            break;
		printf("%s", line);
		free(line);
	}
	open_terminal();
	close(fd);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (print(c_red, "✘ Usage: <source_file>"), EXIT_FAILURE);
	test_file(argv[1]);
}
