#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char candidateName[50];
  int votes;
} Candidate;

void voteIsValid (char votersVotes[][3][50], Candidate candidates[], int voters, int numberOfCandidates);


int main(int argc, char const *argv[])
{
// mudar numero depois !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if (argc < 2) {
    printf("Define at least three candidates.");
    return 1;
  }
  
  int voters;
  int numberOfCandidates = argc - 1;

  printf("Number of voters: ");
  scanf("%i", &voters);

  Candidate candidates[numberOfCandidates];

  for (int i = 0; i < numberOfCandidates; i++) {
    strcpy(candidates[i].candidateName, argv[i + 1]);
    candidates[i].votes = 0;
  }

  char votersVotes[voters][3][50];

  voteIsValid(votersVotes, candidates, voters, numberOfCandidates);


  
  



  
  return 0;
}

void voteIsValid (char votersVotes[][3][50], Candidate candidates[], int voters, int numberOfCandidates) {
  for (int i = 0; i < voters; i++) {

    for (int indexVotes = 0; indexVotes < 3; indexVotes++) {
      printf("Rank %i: ", indexVotes + 1);
      scanf("%s", votersVotes[i][indexVotes]);

      for (int ii = 0; ii < numberOfCandidates; ii++) {
      int stringEquality = strcmp(votersVotes[i][indexVotes], candidates[ii].candidateName);
     
        if ( stringEquality == 0 ) {
          break;
        } else if ( ii == numberOfCandidates - 1 ) {
          printf("Invalid vote\n");
          indexVotes -= 1;
          break;
        }
      }

    }

    printf("\n");
  }

}