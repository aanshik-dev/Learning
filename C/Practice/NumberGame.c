#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
   srand(time(0));
   int l, guess, count = 0, user, random = (rand()) % 100;
   printf("Difficulty Level\n\n EASY:   1\n MEDIUM: 2\n HARD:   3\n\nSelect Level: ");
   scanf("%d", &l);
   switch (l) {
   case 1:
      guess = 10;
      break;
   case 2:
      guess = 8;
      break;
   case 3:
      guess = 6;
      break;
   default:
      guess = -1;
   }

   if (guess == -1)
      printf("ERROR !! No Such Level");
   else {
      printf("\nEnter any Number to Start: ");
      do {
         count++;
         scanf("%d", &user);
         if (user == random) {
            printf("\n\n    !! CONGRATS !!  YOU WON !!\n       Number Of Guesses: %d\n\n", count);
            break;
         } else if (count == guess) {
            printf("\n\n    SORRY !! YOU LOSE !!\n    The Number Was %d\n", random);
            break;
         } else if (user < random)
            printf("\nNumber iS GREATER, Try Again: ");
         else if (user > random)
            printf("\nNumber is SMALLER, Try Again: ");

      } while (user != random);
   }

   return 0;
}