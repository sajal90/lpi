#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024
extern char **environ;

int getname(char *e, char *name) {
	int len = strlen(e);
	int i;
	int j = 0;

	for(int i=0; i<len; ++i) {
		if(e[i] == '=')
			break;
		name[j++] = e[i];
	}
	name[j] = '\0';

	if(i == len)
		return -1;
	return 0;
}


int my_unsetenv(const char *name) {
	char **e, **f;
	char a[BUF_SIZE];

	for(e = environ; *e != NULL; ++e) {
		if(getname(*e, a) == -1) {
			return -1;
		}

		if(strcmp(name, a) == 0) {
			for(f = e; *f != NULL; ++f) {
				*f = *(f+1);
			}
	 	}
	}
	return 0;
}

int my_setenv(const char *name, const char *value, int replace) {
	char *final_str;
	int name_len = strlen(name);
	int val_len = strlen(value);
	final_str = malloc(name_len + val_len + 2); // extra space for = and null character
	if(final_str == NULL) {
		return -1;
	}
	
	strncpy(final_str, name, name_len);
	final_str[name_len] = '=';
	strncat(final_str, value, val_len);
	final_str[name_len+val_len+1] = '\0';

	if(getenv(name) != NULL && !replace) {
		return -1;
	}
	if(replace)
		my_unsetenv(final_str);

	putenv(final_str);

	return 0;
}


void print_env() {
	char **e;
	for(e = environ; *e!=NULL; ++e) {
		puts(*e);
	}

}

int main(int argc, char *argv[]) {
	clearenv();

	my_setenv("GREET", "Hello World",0);
	my_setenv("bitch", "BOO",0);
	my_setenv("OPS", "HOP",0);
	my_setenv("CHARIZARD", "best",0);
	my_setenv("C", "> java",0);
	print_env();
	printf("---------------------\n");
	my_unsetenv("CHARIZARD");
	print_env();
	printf("---------------------\n");
	my_unsetenv("GREET");
	my_unsetenv("C");
	print_env();
	printf("---------------------\n");

	return 0;
}
