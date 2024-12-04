#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>

static jmp_buf env;

void f1() {
	setjmp(env);
	puts("here in f1");
}

void f2() {
	puts("here in f2");
	longjmp(env, 1);
	puts("here in f2");
}

int main() {
	f1();
	f2();
}
