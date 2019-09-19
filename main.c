#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "word_game.h"
#ifndef WORD_GAME_H_INCLUDED
#define WORD_GAME_H_INCLUDED
#endif // WORD_GAME_H_INCLUDED
int main()
{

    char current_letters[] = {'b', 'e', 'l'};
    char target_letters[] = {'c', 'o', 'a'};
    const int NUMBER_OF_LETTERS = sizeof(current_letters);

    start_game(current_letters, target_letters, NUMBER_OF_LETTERS);


    return 0;
}


void start_game(char * pCurrent,  char* pTarget, const int size_of_word)
{
    int position_of_cursor = 0; // displays "_" under the letter in current_letters array i.e. the selected letter
    bool game_finished = false; // while false the game is being played
    int number_of_letter_changes = 0;
    int number_of_keystrokes = 0;
    const int MAX_NUMBER_OF_GUESSES = size_of_word * 2;
    const int MAX_KEYSTROKES = 20;
    char words_guessed[(MAX_NUMBER_OF_GUESSES + 1) * size_of_word]; // maximum amount of memory needed to hold all x guesses and \n
    int words_guessed_position = 0; // holds current position of words_guessed array so when adding new guess the loop knows where to continue
    int length = sizeof(words_guessed); // size of words_guessed array



    while(game_finished == false)
    {
        display_game_state (pCurrent, size_of_word, position_of_cursor, number_of_letter_changes, pTarget, number_of_keystrokes);
        printf("\nEnter a command: ");
        char move = getchar();
        getchar();
        if ((move == 60) | (move == 62) | (move >= 97 && move <= 122)) // 97 - 122 is deciaml for a - z
        {
            if(move == 60) // 60 is decimal for "<"
            {
                move_cursor_left(&position_of_cursor, size_of_word);
                number_of_keystrokes ++;
            }

            else if(move == 62) // 62 is deciaml for ">"
            {
                 move_cursor_right(&position_of_cursor, size_of_word);
                 number_of_keystrokes ++;
            }

            else
            {
                char new_letter = move;
                // changes letter in the current letters array
                change_letter(pCurrent, position_of_cursor, new_letter, size_of_word);
                // letter is changed so number_of_letters_changed is plused by 1 aswell as keystrokes
                number_of_letter_changes ++;
                number_of_keystrokes ++;
                for(int i = 0; i <= size_of_word; i++){ // appends 4 char guess to words_guessed array. words_guessed_position holds current position of array
                    if(i == size_of_word){
                        words_guessed[words_guessed_position] = 47; // 47 is decimal for "/". used that for end point in guess so once reached, will print next guess on next line
                        words_guessed[words_guessed_position + 1] = 33; // 33 is decimal for "!". Adds this to the end of every guess so once it reaches this iin loop it will stop
                    }
                    else{
                        words_guessed[words_guessed_position] = pCurrent[i];
                    }

                    words_guessed_position++;
                }

            }
        // scenarios in which the game can end
        game_finished = (compare_letters(pCurrent, pTarget, size_of_word) | (number_of_letter_changes == MAX_NUMBER_OF_GUESSES) | number_of_keystrokes == MAX_KEYSTROKES);

        }
    }
     bool compare = compare_letters(pCurrent, pTarget, size_of_word); // checks if the the two arrays match, if true user wins the game




     if(compare == false)
     {
        // prints reason as to why the user lost
         if(number_of_keystrokes == 20)
            printf("\nYou lost because you hit 20 keystrokes");

         else if(number_of_letter_changes == MAX_NUMBER_OF_GUESSES)
            printf("\nYou lost because you hit %d changes", MAX_NUMBER_OF_GUESSES);

         else if((number_of_keystrokes == 20) && (number_of_letter_changes == MAX_NUMBER_OF_GUESSES))
           printf("\nYou lost because you hit 20 keystrokes and because you hit %d changes", MAX_NUMBER_OF_GUESSES);

     }

     else{
        fputs(compare ? "\nCongradulations, you won because you matched the words!" : "\nYou lost :(", stdout);

        printf("\nWords guessed\n------------\n");
        for(int i = 0; i < length; i++){
            if(words_guessed[i] == 33){ // 33 is deciaml for "!"
                break;
            }
            else if(words_guessed[i] == 47){ // 47 is deciaml for char "/"
                printf("\n");
            }
           else{
                printf("%c", words_guessed[i]);
           }
        }


     }







}


