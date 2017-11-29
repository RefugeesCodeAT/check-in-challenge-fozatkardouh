#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

typedef struct PARTICIPANT
{
    string name;
    bool checked_in;
    struct PARTICIPANT * next;
}
PARTICIPANT;

PARTICIPANT * root = NULL;

#define CHECKED_IN true
#define CHECKED_OUT false
#define SIZE_OF_PARTICIPANT sizeof(PARTICIPANT)

string get_user_input();
bool perform(string user_input);

// TODO: Functions to implement
void add_one(string participant_name);
void remove_one(string participant_name);
void check_one(string participant_name);
void display_participants();
void free_memory();

// My functions
void add_To_The_Last_Participant(PARTICIPANT * new_Participant);
void display_Participant(PARTICIPANT * participant);
PARTICIPANT * free_All(PARTICIPANT * participant);

int main(void)
{
    bool working = true;

    while(working)
    {
        string user_input = get_user_input();
        working = perform(user_input);
    }

    free_memory();
}

string get_user_input()
{
    return get_string("Command: ");
}

// Performs the action from the "user_input"
bool perform(string user_input)
{
    // Read the string of user input into two variables
    string action_name = strtok(user_input, " ");
    string participant_name = strtok(NULL, " ");

    if(strcmp(action_name, "add") == 0)
    {
        add_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "remove") == 0)
    {
        remove_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "check") == 0)
    {
        check_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "display") == 0)
    {
       display_participants();
       return true;
    }
    if(strcmp(action_name, "exit") == 0)
    {
        return false;
    }

    return true;
}

/*
    Adds a participant to the beginning of the list
*/
void add_one(string participant_name)
{
    printf("add %s\n", participant_name);

    PARTICIPANT * new_Participant = malloc(SIZE_OF_PARTICIPANT);
    new_Participant->name = participant_name;
    new_Participant->checked_in = CHECKED_OUT;
    new_Participant->next = NULL;

    if (root == NULL)
    {
        root = malloc(SIZE_OF_PARTICIPANT);
        root->name = NULL;
        root->checked_in = NULL;
        root->next = new_Participant;
    }
    else
    {
        add_To_The_Last_Participant(new_Participant);
    }

}

void add_To_The_Last_Participant(PARTICIPANT * new_Participant)
{
    PARTICIPANT * ptr = root;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = new_Participant;
}

/*
    Search for a participant in the list and if it exists, remove it.
*/
void remove_one(string participant_name)
{
    printf("remove %s\n", participant_name);

    PARTICIPANT * previos_Participant = root;
    while (previos_Participant->next != NULL && strcmp(previos_Participant->next->name, participant_name))
    {
        previos_Participant = previos_Participant->next;
    }
    PARTICIPANT * next_Participant = previos_Participant->next->next;
    free(previos_Participant->next);
    previos_Participant->next = NULL;
    previos_Participant->next = next_Participant;
}

/*
    Check a participant from the list in or out
*/
void check_one(string participant_name)
{
    printf("check %s\n", participant_name);

    PARTICIPANT * ptr = root->next;
    while (ptr->next != NULL && strcmp(ptr->name, participant_name))
    {
        ptr = ptr->next;
    }
    ptr->checked_in = CHECKED_IN;
}

/*
    Display all participants and their status.
*/
void display_participants()
{
    printf("display\n");
    display_Participant(root->next);
}

void display_Participant(PARTICIPANT * participant)
{
    printf("Name: %s\nChecked in?: %s\n", participant->name, participant->checked_in ? "true" : "false");
    if (participant->next != NULL)
    {
        display_Participant(participant->next);
    }
}
/*
    Free all memory used by participants in the list
*/
void free_memory()
{
    printf("freeing stuff.\n");
    root = free_All(root);
}

PARTICIPANT * free_All(PARTICIPANT * participant)
{
    if(participant->next != NULL)
    {
        participant->next = free_All(participant->next);
    }
    free(participant);
    return NULL;
}