#include "export.h"

namespace vale_of_mean_creatures
{
	void this_one_for_the_birds() {	}



	void this_one_for_the_whales() {	}



	namespace the_abyss
	{
		void bubble_sort() {	}
	}
}

extern "C" PUBLIC void get_function_addresses_2(void (*&f1)(), void (*&f2)(), void (*&f3)())
{
	// do this in order to prevent early inclusion of pc-based offset thunk usage in GCC
	for (volatile int i = 1, j = 1; i < 1000; j = i, ++i)
		i = i + j;
	f1 = &vale_of_mean_creatures::this_one_for_the_birds;
	f2 = &vale_of_mean_creatures::this_one_for_the_whales;
	f3 = &vale_of_mean_creatures::the_abyss::bubble_sort;
}

extern "C" PUBLIC void bubble_sort(int * volatile begin, int * volatile end);

extern "C" PUBLIC void function_with_a_nested_call_2()
{
	bubble_sort(0, 0);
}

extern "C" PUBLIC void bubble_sort2(int * volatile begin, int * volatile end)
{
	bubble_sort(begin, end);
}

extern "C" PUBLIC void bubble_sort_expose(void (*&f)(int * volatile begin, int * volatile end))
{
	// do this in order to prevent early inclusion of pc-based offset thunk usage in GCC
	for (volatile int i = 1, j = 1; i < 1000; j = i, ++i)
		i = i + j;
	f = &bubble_sort;
}

#include <stdio.h>
#include <stdarg.h>

extern "C" PUBLIC int guinea_snprintf(char *buffer, size_t count, const char *format, ...)
{
	for (volatile int i = 1, j = 1; i < 1000; j = i, ++i)
		i = i + j;

	va_list args;

	va_start(args, format);
	int n = vsnprintf(buffer, count, format, args);
	va_end(args);

	return n;
}

extern "C" PUBLIC int datum1 = 1123;
extern "C" PUBLIC char datum2[] = "SOMETEXTSOMETEXTSOMETEXT";
