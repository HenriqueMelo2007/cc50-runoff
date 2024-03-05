#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char candidateName[50];
  int votes;
} Candidate;

int main(int argc, char const *argv[])
{

  if (argc < 2) {
    printf("Define at least one candidate.");
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


  for (int i = 0; i < voters; i++) {

    for (int indexVotes = 0; indexVotes < 3; indexVotes++) {
      printf("Rank %i: ", indexVotes + 1);
      scanf("%s", votersVotes[i][indexVotes]);
    }

    printf("\n");
  }



  
  return 0;
}