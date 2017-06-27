#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "animal.h"

struct Node {
	char *text;
	struct Node *left;
	struct Node *right;
};

// read file
struct Node *read(FILE *fp)
{
	char ch = fgetc(fp);
	char temp[80];
	struct Node *current = malloc(sizeof(struct Node));

	// if first char is not > the text is an animal
	if (ch != '>')
	{
		fgets(temp, 80, fp);
		strtok(temp, "\n");
		char *tmp = malloc(strlen(temp) + 1);
		strcpy(tmp, temp);
		current->text = tmp;
		current->left = 0;
		current->right = 0;
	}

	//if first char is > the text is a question
	else
	{
		fgets(temp, 80, fp);
		strtok(temp, "\n");
		char *tmp = malloc(strlen(temp) + 1);
		strcpy(tmp, temp);
		current->text = tmp;
		current->left = read(fp);
		current->right = read(fp);
	}

    return current;
}

// write to file
void write(FILE *fp, struct Node *current)
{
	// if the current node is not null
	if (current != 0)
	{
		// if the current node has children, it's a question
		if (current->left != 0 || current->right != 0)
        {
            // mark with > to indicate question
            fputc('>', fp);
        }

		// if the current node has no children, it's an animal
		else
        {
            // mark with - to indicate animal
            fputc('-', fp);
        }

		// print the current node's text to file
		fprintf(fp, "%s\n", current->text);

		// call recursively
		write(fp, current->left);
		write(fp, current->right);
	}
}

