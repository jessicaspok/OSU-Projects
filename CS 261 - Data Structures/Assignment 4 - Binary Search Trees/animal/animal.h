#ifndef ANIMAL_H
#define ANIMAL_H

struct Tree {
	struct Node *root;
	int size;
};

struct Node *read(FILE *fp);
void write(FILE *fp, struct Node *current);

#endif
