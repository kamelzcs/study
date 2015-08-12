/*
 * list_entry.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

struct foobar{
	unsigned int foo;
	char bar;
	char boo;
};

int main(int argc, char** argv){

	struct foobar tmp;

	printf("address of &tmp is= %p\n\n", &tmp);
	printf("address of tmp->foo= %p \t offset of tmp->foo= %lu\n", &tmp.foo, (unsigned long) &((struct foobar *)0)->foo);
	printf("address of tmp->bar= %p \t offset of tmp->bar= %lu\n", &tmp.bar, (unsigned long) &((struct foobar *)0)->bar);
	printf("address of tmp->boo= %p \t offset of tmp->boo= %lu\n\n", &tmp.boo, (unsigned long) &((struct foobar *)0)->boo);

	printf("computed address of &tmp using:\n");
	printf("\taddress and offset of tmp->foo= %p\n",
	      (struct foobar *) (((char *) &tmp.foo) - ((unsigned long) &((struct foobar *)0)->foo)));
	printf("\taddress and offset of tmp->bar= %p\n",
	      (struct foobar *) (((char *) &tmp.bar) - ((unsigned long) &((struct foobar *)0)->bar)));
	printf("\taddress and offset of tmp->boo= %p\n",
	      (struct foobar *) (((char *) &tmp.boo) - ((unsigned long) &((struct foobar *)0)->boo)));
    printf("address of &tmp using macro is= %p\n\n", list_entry(&tmp.bar, struct foobar, bar));

	return 0;
}


