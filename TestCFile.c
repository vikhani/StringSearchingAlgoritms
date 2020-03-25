#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Foo()
{
	const char *home;
	home = getenv("HOME");
	if (home != NULL)
	{
	  char *buff;
	  buff = malloc(strlen(home) + strlen("/.local/share/")+1);
	  strcpy(buff, home);
	  strcat(buff, "/.local/share/");
	  free(buff);
	}
}
