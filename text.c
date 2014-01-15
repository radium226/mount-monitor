#include <stdio.h>
#include <stdlib.h>

#include "text.h"

int text_length(char *text)
{
    int length = 0; 
    while (text[length] != '\0') length++;
    return length; 
}

char *text_color(char *text, char *color)
{
    char *colored_text = (char *)malloc(sizeof(char) * (text_length(text) + 1 + text_length(color) + text_length(DEFAULT)));
    sprintf(colored_text, "%s%s%s", color, text, DEFAULT);
    return colored_text;
}

char *text_red(char *text) {
    return text_color(text, RED);
}

char *text_copy(char *text) {
    int size = text_length(text);
    char *copied_text = (char *)malloc(sizeof(char) * (size + 1));
    strcpy(copied_text, text);
    return copied_text;
}

