#include "tools.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

//
//	private
//

#define _UNWRAP_THEN_STDPRINT(prefix)	\
	va_list args;						\
	va_start(args, fmt);				\
	stdprint(prefix, fmt, args);		\
	va_end(args)


void stdprint(const char *prefix, const char *fmt, va_list args)
{
	printf("%s", prefix);
	vprintf(fmt, args);
	printf("\n");
}

//
//	public
//

void debug(const char *fmt, ...)
{
	_UNWRAP_THEN_STDPRINT("\033[34mDEBUG \033[38;2;80;80;80m>> \033[0m");
}

void error(const char *fmt, ...)
{
	_UNWRAP_THEN_STDPRINT("\033[31mERROR \033[38;2;80;80;80m>> \033[0m");
	exit(EXIT_FAILURE);
}