/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _x_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:48 by saraki            #+#    #+#             */
/*   Updated: 2023/08/19 18:28:07 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

int	x_print_dec_upper(va_list args)
{
	int				digits;
	unsigned int	value;
	uintptr_t		ulong_value;

	value = va_arg(args, unsigned int);
	ulong_value = (uintptr_t) value;
	digits = dec_to_nbase(ulong_value, "0123456789ABCDEF", STDOUT_FILENO);
	return (digits);
}

int	x_print_dec_lower(va_list args)
{
	int				digits;
	unsigned int	value;
	uintptr_t		ulong_value;

	value = va_arg(args, unsigned int);
	ulong_value = (uintptr_t) value;
	digits = dec_to_nbase(ulong_value, "0123456789abcdef", STDOUT_FILENO);
	return (digits);
}

// int	test_helper_upper(const char *fmt, ...)
// {
// 	va_list	args;
// 	int		a;

// 	va_start(args, fmt);
// 	a = x_print_dec_upper(args);
// 	va_end(args);
// 	return (a);
// }

// int	test_helper_lower(const char *fmt, ...)
// {
// 	va_list	args;
// 	int		a;

// 	va_start(args, fmt);
// 	a = x_print_dec_lower(args);
// 	va_end(args);
// 	return (a);
// }

// #include <stdio.h>
// int	main(void)
// {
// 	int	a;

// 	a = test_helper_upper("", 4294967295);
// 	printf("\n%d\n", a);
// 	a = test_helper_upper("", 2147483647);
// 	printf("\n%d\n", a);
// 	a = test_helper_upper("", -2147483648);
// 	printf("\n%d\n", a);
// 	a = test_helper_upper("", -2147483649);
// 	printf("\n%d\n", a);
// 	printf("--------------\n");
// 	a = test_helper_lower("", 4294967295);
// 	printf("\n%d\n", a);
// 	a = test_helper_lower("", 2147483647);
// 	printf("\n%d\n", a);
// 	a = test_helper_lower("", -2147483648);
// 	printf("\n%d\n", a);
// 	a = test_helper_lower("", -2147483649);
// 	printf("\n%d\n", a);
// 	printf("--------------\n");
// 	a = printf("%x", 4294967295);
// 	printf("\n%d\n", a);
// 	a = printf("%x", 2147483647);
// 	printf("\n%d\n", a);
// 	a = printf("%x", -2147483648);
// 	printf("\n%d\n", a);
// 	a = printf("%x", -2147483649);
// 	printf("\n%d\n", a);
// }
