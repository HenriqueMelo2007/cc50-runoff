#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char candidateName[50];
  int votes;
} Candidate;

int numberOfCandidates;

void initializeCandidates (Candidate candidates[], int numberOfCandidates, char const *argv[]);
void receivesVotesChecksIfItIsValid (char votersVotes[][numberOfCandidates][50], Candidate candidates[], int voters, int numberOfCandidates);
void assigningVotes (char votersVotes[][numberOfCandidates][50], Candidate candidates[], int voters, int numberOfCandidates);
void isThereAWinner (Candidate candidates[], int voters, int *indexMostVotedCandidate, int *votesMostVotedCandidate);
void candidateFewestVotes (Candidate candidates[], int *votesFewestVotedCandidate);
void removingCandidates (Candidate candidates[], int votesFewestVotedCandidate, char nameRemovedCandidates[], int *numberOfCandidatesRemoved);


int main(int argc, char const *argv[])
{
  if (argc < 3) {
    printf("Define at least two candidates.");
    return 1;
  }
  
  int voters;
  numberOfCandidates = argc - 1;

  printf("Number of voters: ");
  scanf("%i", &voters);

  Candidate candidates[numberOfCandidates];

  initializeCandidates(candidates, numberOfCandidates, argv);  

  char votersVotes[voters][numberOfCandidates][50];

  receivesVotesChecksIfItIsValid(votersVotes, candidates, voters, numberOfCandidates);

  assigningVotes(votersVotes, candidates, voters, numberOfCandidates);

  int indexMostVotedCandidate = 0;
  int votesMostVotedCandidate = 0;

  isThereAWinner (candidates, voters, &indexMostVotedCandidate, &votesMostVotedCandidate);

  char nameRemovedCandidates[numberOfCandidates][50];
  int numberOfCandidatesRemoved = 0;

  int votesFewestVotedCandidate = candidates[0].votes;

  candidateFewestVotes(candidates, &votesFewestVotedCandidate);

  removingCandidates (candidates, votesFewestVotedCandidate, nameRemovedCandidates, &numberOfCandidatesRemoved);


  return 0;
}



void initializeCandidates (Candidate candidates[], int numberOfCandidates, char const *argv[]) {
  for (int i = 0; i < numberOfCandidates; i++) {
    strcpy(candidates[i].candidateName, argv[i + 1]);
    candidates[i].votes = 0;
  }
}

void receivesVotesChecksIfItIsValid (char votersVotes[][numberOfCandidates][50], Candidate candidates[], int voters, int numberOfCandidates) {
  for (int i = 0; i < voters; i++) {

    for (int indexVotes = 0; indexVotes < numberOfCandidates; indexVotes++) {
      printf("Rank %i: ", indexVotes + 1);
      scanf("%s", votersVotes[i][indexVotes]);

      for (int ii = 0; ii < numberOfCandidates; ii++) {
        int candidateExists = strcmp(votersVotes[i][indexVotes], candidates[ii].candidateName);
        int thereIsRepeatedVote = 1;

        for (int isRepeated = 0; isRepeated < indexVotes; isRepeated++) {
          int possibleRepeatedVote = strcmp(votersVotes[i][indexVotes], votersVotes[i][isRepeated]);

          if ( possibleRepeatedVote == 0 ) {
            thereIsRepeatedVote = 0;
          }
        }

        if ( candidateExists == 0 && thereIsRepeatedVote != 0 ) {
          break;
        } else if ( ii == numberOfCandidates - 1 ) {
          printf("Invalid or repeated vote\n");
          indexVotes -= 1;
          break;
        }
      }

    }

    printf("\n");
  }
}

void assigningVotes (char votersVotes[][numberOfCandidates][50], Candidate candidates[], int voters, int numberOfCandidates) {
  for (int voter = 0; voter < voters; voter++) {
    
    char votersOfVoter[numberOfCandidates][50];
    for (int i = 0; i < numberOfCandidates; i++) {
      strcpy(votersOfVoter[i], votersVotes[voter][i]);
    }

    for (int rank = 0; rank < numberOfCandidates; rank++) {
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

void isThereAWinner (Candidate candidates[], int voters, int *indexMostVotedCandidate, int *votesMostVotedCandidate) {
  for (int allCandidatesOneByOne = 0; allCandidatesOneByOne < numberOfCandidates; allCandidatesOneByOne++) {
    int votesOfThisCandidate = candidates[allCandidatesOneByOne].votes;

    if ( votesOfThisCandidate > *votesMostVotedCandidate ) {
      *indexMostVotedCandidate = allCandidatesOneByOne;
      *votesMostVotedCandidate = votesOfThisCandidate;
    }
  }

  if ( *votesMostVotedCandidate > (float) voters / 2 ) {
    printf("The winner is: %s", candidates[*indexMostVotedCandidate].candidateName);
  }
}

void candidateFewestVotes (Candidate candidates[], int *votesFewestVotedCandidate) {
  for (int allCandidatesOneByOne = 0; allCandidatesOneByOne < numberOfCandidates; allCandidatesOneByOne++) {
    int votesOfThisCandidate = candidates[allCandidatesOneByOne].votes;
    
    if ( votesOfThisCandidate < *votesFewestVotedCandidate ) {
      *votesFewestVotedCandidate = votesOfThisCandidate;
    }
  }
}

void removingCandidates (Candidate candidates[], int votesFewestVotedCandidate, char nameRemovedCandidates[], int *numberOfCandidatesRemoved) {
  for (int allCandidatesOneByOne = 0; allCandidatesOneByOne < numberOfCandidates; allCandidatesOneByOne++) {
    int votesOfThisCandidate = candidates[allCandidatesOneByOne].votes;

    if ( votesOfThisCandidate == votesFewestVotedCandidate ) {
      strcpy(nameRemovedCandidates[*numberOfCandidatesRemoved], candidates[allCandidatesOneByOne].candidateName);
      *numberOfCandidatesRemoved++;
    }
  }
}