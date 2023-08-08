#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "candidate.h"

#define ID_LEN 7
#define NAME_LEN 20

struct candidate {
	char candidate_name[NAME_LEN];
	char candidate_id[ID_LEN];
	int candidate_number;
	int num_voates;
	bool banned;
	struct candidate *next;
};

struct election_type {
	char election_id[ID_LEN];
	struct candidate *top;
};

/*functions*/

PRIVATE void terminate(const char *message)
{
	printf("\n%s\n", message);
	exit(EXIT_FAILURE);
}

PRIVATE int read_word(char *word, int len)
{
	int pos = 0;
	char ch;

	while ((ch = getchar()) != '\n') {
		if (pos < len)
			word[pos++] = ch; 
	}
	return pos;
}

PRIVATE struct candidate *search(election el,
					struct candidate *cur_node,
					struct candidate *prev_node)
{
	int candidate_number;

	printf("Enter candidate registration number: ");
	scanf("%d", &candidate_number);

	for(cur_node = el->top, prev_node = NULL;
	 	cur != NULL, candidate_number != cur_node->candidate_number;
		prev_node = cur, cur_node = cur->next)
			;

	if(!cur_node)
		printf("Candidate with registration number %d, not found\n", candidate_number);
	
	return cur_node;
}

PUBLIC void print_profile(election el)
{
	struct candidate *cur, *prev;

	if(!(search(el, cur, prev)))
		return;
	
	printf("\n\
			Canddiate name: %s\n \
			Candidate ID: %s\n\
			Candidate registration number: %d\n\
			number votes: %d\n");

	if (!cur->banned)
		printf("\nStatus: Banned\n");
	else
		printf("\nStatus: Active\n");
}

PUBLIC create_election(void)
{
	election el = malloc(sizeof(struct election_type));

	if (el == NULL)
		terminate("Error in create: Election could not be started");

	el->top = NULL;

	printf("You need an election ID to continue\n"
			"Enter an election ID: ");
	read_word(el->election_id, ID_LEN);
	return el;
}

PUBLIC void make_candidate(election el)
{
	struct candidate *new_node = malloc(sizeof(struct candidate));

	if (new_node == NULL)
		terminate("Error in create: Candidate could not be created");
	
	printf("Candidate needs an ID number\n"
			"Enter candidate ID number: ");
	read_word(new_node->candidate_id, ID_LEN);

	printf("Enter Candidate name: ");
	read_word(new_node->candidate_name, NAME_LEN);

	new_node->num_voates = 0;
	new_node->banned = false;

	new_node->next = el->top;
	el->top = new_node;
}

PUBLIC void delete_candidate(election el)
{
	 struct candidate *cur, *prev;
	 int candidate_number;

	 printf("Enter candidate number: ");
	 scanf("%d", &candidate_number);

	 for(cur = el->top, prev = NULL;
	 	cur != NULL, candidate_number != cur->candidate_number;
		prev = cur, cur = cur->next)
			;
	
	if(!cur) {
		printf("\ncandidate number %d, not found\n", candidate_number);
		return;
	}

	printf("\nWARNING!!!: Deleting this candidate\n")
	/* function to print candidate profile here*/

	printf("Continue ? (Y/N)");

	
	if (toupper((ch = getchar())) == 'Y') {
		prev->next = cur->next;
		free(cur);
	}

	else
		printf("Operation Aborted\n");
		
}

PUBLIC void ban_candidate(election el)
{
	struct candidate *p;
	int candidate_number;
	char ch;

	printf("Enter candidate registration number: ");
	scanf("%d", &candidate_number);

	for(p = el->top;
		p != NULL, p->candidate_number != candidate_number;
		p = p->next)
			;

	if(!p) {
		printf("Candidate with registration number %d, not found\n", candidate_number);
		return;
	}

	/*print candidate profile function comes here*/

	printf("WARNINg!!!: Baning this candidate"
			"if candidate is baned three times then can never stand for elections");
	
	printf("Contitnue ? (Y/N): ");
	if((toupper(ch = getchar())) != 'Y') {
		printf("Operation Aborted\n");
		return;
	}

	p->banned = true;
	printf("Candidate banned succesfully\n");
}

PUBLIC  void vote(election el)
{
	struct candidate *p;

}