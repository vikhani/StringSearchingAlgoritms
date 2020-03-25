#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Foo()
{
	const char *home;
	home = getenv("HOME");
	if (home != NULL)
	{
	  char *guessed_xdg_home;
	  guessed_xdg_home = malloc(strlen(home) + strlen("/.local/share/")+1);
	    if(guessed_xdg_home!=NULL)
	    {
	      strcpy(guessed_xdg_home, home);
	      strcat(guessed_xdg_home, "/.local/share/");
	      free(guessed_xdg_home);
	    }
	}
}
