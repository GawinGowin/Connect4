/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _other.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:44:25 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 19:43:17 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

int	_print_percent(va_list args)
{
	if (args == NULL)
		return (0);
	if (write(STDOUT_FILENO, "%", 1) == -1)
		return (0);
	return (1);
}

int	_other_format(va_list args, char c)
{
	int	digits;

	digits = 0;
	if (args == NULL)
		return (0);
	if (write(STDOUT_FILENO, "%", 1) != -1)
		digits ++;
	if (write(STDOUT_FILENO, &c, 1) != -1)
		digits ++;
	return (digits);
}

// void	test_helper(const char *fmt, ...)
// {
// 	va_list	args;
// 	int		a;

// 	va_start(args, fmt);
// 	a = _print_percent(args);
// 	va_end(args);
// }

// int	main(void)
// {
// 	test_helper("", 0);
// 	write(1,"\n",1);
// }
