/* registry.c */
#include <unistd.h>
#include "registry.h"

static registry_t func;

void register_func(registry_t f)
{
	func = f;
}

static void on_some_event(void)
{
	...func();
...}
