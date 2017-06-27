#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "animal.h"

struct Node {
	char *text;
	struct Node *left;
	struct Node *right;
};

int main() {
	// read from text file
	FILE *fp = fopen("animals.txt", "r");

	// error opening file
	if (fp == NULL)
    {
		printf("Cannot open file.\n");
		printf("Press Enter to exit.\n");
		getchar();
	}

    else
    {
        struct Tree *tree= malloc(sizeof(struct Tree));
        assert(tree != 0);
        tree->root = read(fp);
        fclose(fp);

        printf("Beginning Animal game...\n\n");
        printf("Please think of an animal!\n");
        printf("Answer questions by typing 'yes' or 'no'.\n\n");

        struct Node *current = tree->root;
        char ans[5];

        // while the current node is not null
        while (current != 0)
        {
            // if the current node has children
            if (current->left != 0 || current->right != 0)
            {
                printf("%s\n", current->text);
                scanf("%s", ans);

                // user enters yes - traverse left
                if (strcmp(ans,"y") == 0 || strcmp(ans,"Y") == 0 || strcmp(ans,"yes") == 0
                    || strcmp(ans,"Yes") == 0 || strcmp(ans,"YES") == 0)
                {
                    current = current->left;
                }

                // user enters no - traverse right
                else if (strcmp(ans,"n") == 0 || strcmp(ans,"N") == 0 || strcmp(ans,"no") == 0
                    || strcmp(ans,"No") == 0 || strcmp(ans,"NO") == 0)
                {
                    current = current->right;
                }
            }

            // once leaf is reached, guess the animal
            else
            {
                printf("Is it a(n) %s?\n", current->text);
                scanf("%s", ans);

                // if guess is correct
                if (strcmp(ans,"y") == 0 || strcmp(ans,"Y") == 0 || strcmp(ans,"yes") == 0
                    || strcmp(ans,"Yes") == 0 || strcmp(ans,"YES") == 0)
                {
                    printf("\nThat was great! You were thinking of a %s.\n\n", current->text);
                    printf("Press Enter to exit.\n");
                    getchar();
                    return 0;
                }

                // if guess is wrong
                else if (strcmp(ans,"n") == 0 || strcmp(ans,"N") == 0 || strcmp(ans,"no") == 0
                    || strcmp(ans,"No") == 0 || strcmp(ans,"NO") == 0)
                {
                    printf("\nI'm stumped.. What animal were you thinking of?\n");

                    // learn new animal
                    // get animal's name
                    char temp[80];
                    getchar();
                    fgets(temp, 80, stdin);
                    strtok(temp, "\n");
                    char *tmp1 = malloc(strlen(temp) + 1);
                    strcpy(tmp1, temp);

                    // create left and right nodes
                    current->left = malloc(sizeof(struct Node));
                    current->right = malloc(sizeof(struct Node));

                    // set left child to animal entered
                    current->left->text = tmp1;

                    // set right child to incorrect guess
                    current->right->text = current->text;

                    // assigns children of newly created children to null
                    current->left->left = current->left->right = current->right->left = current->right->right = 0;

                    // get new question to differentiate
                    printf("\nGive me a question that will be true for %s but false for %s\n",
                        current->left->text, current->right->text);
                    fgets(temp, 80, stdin);
                    strtok(temp, "\n");
                    char *tmp2 = malloc(strlen(temp) + 1);
                    strcpy(tmp2, temp);

                    // set current node to the question
                    current->text = tmp2;
                    printf("\nThanks, I have learned a new animal!\n\n");

                    // save new tree to the file
                    fp = fopen("animals.txt", "w");

                    // error saving file
                    if (fp == NULL)
                    {
                        printf("Cannot save file.\n");
                        printf("Press Enter to exit.\n");
                        getchar();
                    }

                    else
                    {
                        write(fp, tree->root);
                        fclose(fp);
                        printf("Press Enter to exit.\n");
                        getchar();
                    }

                    return 0;
                }
            }
        }
    }

	return 0;
}
