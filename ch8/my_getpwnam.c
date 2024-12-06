#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


struct passwd *my_getpwnam(const char *name);


int main(int argc, char *argv[]) {
	struct passwd *p;

	if(argc < 2) {
		fprintf(stderr, "Usage: %s [username]", argv[0]);
		exit(EXIT_FAILURE);
	}

	p = my_getpwnam(argv[1]);
	if(p == NULL) {
		fprintf(stderr, "Error: username doesn't exist");
		exit(EXIT_FAILURE);
	}
	
	printf("User name: %s\n", p->pw_name);
	printf("Encrypted password: %s\n", p->pw_passwd);
	printf("User ID: %ld\n", (long) p->pw_uid);
	printf("Group ID: %ld\n", (long) p->pw_gid);
	printf("Comment: %s\n", p->pw_gecos);
	printf("Home directory: %s\n", p->pw_dir);
	printf("Login shell: %s\n", p->pw_shell);

	return 0;
}

struct passwd *my_getpwnam(const char *name) {
	struct passwd *p = NULL;
	struct passwd *en;

	setpwent();
	errno = 0;
	while((en = getpwent()) != NULL) {
		if(strcmp(en->pw_name, name)== 0) {
			p = en;
			break;
		}
	}
	endpwent();

	return p;
}
