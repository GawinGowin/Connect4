/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:05:57 by saraki            #+#    #+#             */
/*   Updated: 2023/08/19 20:40:32 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INT_H
#define FT_PRINTF_INT_H

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef int (*t_func_pt)(int fd, void *, ...);

// core va_list implementation shared by ft_printf and ft_dprintf
int ft_vdprintf(int fd, const char *fmt, va_list args);

// sub functions
/* Map a format specifier character to its corresponding print function. */
t_func_pt switch_fmt_render(char specifier);
/* write uintptr_t number as n base number */
int dec_to_nbase(uintptr_t n, char *base, int fd);

// usecase functions
/* %c Prints a single character. */
int c_print_char(int fd, va_list args);
/* %s Prints a string (as defined by the common C convention). */
int s_print_str(int fd, va_list args);
/* %p The void * pointer argument has to be printed in hexadecimal format. */
int p_print_pt(int fd, va_list args);
/* %d Prints a decimal (base 10) number. */
int d_print_dec(int fd, va_list args);
/* %i Prints an integer in base 10. */
int i_print_dec(int fd, va_list args);
/* %u Prints an unsigned decimal (base 10) number. */
int u_print_dec(int fd, va_list args);
/* %x Prints a number in hexadecimal (base 16) lowercase format. */
int x_print_dec_lower(int fd, va_list args);
/* %X Prints a number in hexadecimal (base 16) uppercase format. */
int x_print_dec_upper(int fd, va_list args);
/* %% Prints a percent sign. */
int _print_percent(int fd, va_list args);
/* detect wrong format i.e. %w */
int _other_format(int fd, va_list args, char c);

#endif /* FT_PRINTF_INT_H */
