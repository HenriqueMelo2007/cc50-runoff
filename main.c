#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char candidateName[50];
  int votes;
} Candidate;

void voteIsValid (char votersVotes[][3][50], Candidate candidates[], int voters, int numberOfCandidates);
void initializeCandidates (Candidate candidates[], int numberOfCandidates, char const *argv[]);
void assigningVotes (char votersVotes[][3][50], Candidate candidates[], int voters, int numberOfCandidates);


int main(int argc, char const *argv[])
{
  if (argc != 4) {
    printf("Define three candidates.");
    return 1;
  }
  
  int voters;
  int numberOfCandidates = argc - 1;

  printf("Number of voters: ");
  scanf("%i", &voters);

  Candidate candidates[numberOfCandidates];

  initializeCandidates(candidates, numberOfCandidates, argv);  

  char votersVotes[voters][3][50];

  voteIsValid(votersVotes, candidates, voters, numberOfCandidates);

  assigningVotes(votersVotes, candidates, voters, numberOfCandidates);

 

  return 0;
}



void initializeCandidates (Candidate candidates[], int numberOfCandidates, char const *argv[]) {
  for (int i = 0; i < numberOfCandidates; i++) {
    strcpy(candidates[i].candidateName, argv[i + 1]);
    candidates[i].votes = 0;
  }
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

void assigningVotes (char votersVotes[][3][50], Candidate candidates[], int voters, int numberOfCandidates) {
  for (int voter = 0; voter < voters; voter++) {
    char votersOfVoter[3][50];
    
    for (int i = 0; i < 3; i++) {
      strcpy(votersOfVoter[i], votersVotes[voter][i]);
    }

    for (int rank = 0; rank < 3; rank++) {
      char voteInOrder[50];
      int stopLoop = 1;
      strcpy(voteInOrder, votersOfVoter[rank]);

      for (int possibleVoteOwner = 0; possibleVoteOwner < numberOfCandidates; possibleVoteOwner++) {
        int voteOwner = strcmp(voteInOrder, candidates[possibleVoteOwner].candidateName);

        if ( voteOwner == 0 ) {
          candidates[possibleVoteOwner].votes += 1;
          stopLoop = 0;
          break;
        }
      }

      if ( stopLoop == 0 ) {
        break;
      }

    }
  }
}