/* CS261- Assignment 1 - Q.5*/
/* Name: Jessica Spokoyny
 * Date: 04/04/2016
 * Solution description: converts a word to StIcKy case
 */

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
    int i;

    // loop through string
    for(i = 0; word[i] != '\0'; i++)
    {
        // for odd index positions, letter must be lowercase
        if(i % 2)
        {
            // if uppercase
            if(word[i] >= 'A' && word[i] <= 'Z')
            {
                //convert to lowercase
                word[i] = toLowerCase(word[i]);
            }
        }
        else
        {
            // if lowercase
            if(word[i] >= 'a' && word[i] <= 'z')
            {
                //convert to uppercase
                word[i] = toUpperCase(word[i]);
            }
        }
    }
}

int main(){
    /*Read word from the keyboard using scanf*/
    char* word = malloc(30*sizeof(char));
    printf("\nEnter a word of up to 30 letters: ");
    scanf("%s",word);

    /*Call sticky*/
    sticky(word);

    /*Print the new word*/
    printf("\nThe new word is %s \n\n",word);

    return 0;
}
