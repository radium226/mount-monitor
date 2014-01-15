#ifndef TEXT_H
#define	TEXT_H

#define RED "\033[0;31m"
#define DEFAULT "\033[0m"

#include <string.h>

int text_length(char *);

char *text_copy(char *);

char *text_color(char*, char*);

char *text_red(char *);

#endif	/* TEXT_H */

