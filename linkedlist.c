/**
 * file linkedlist.c
 *
 * Author: Erten
 * brief Function definitions for linkedlist operations
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/* Allocates memory and creates new node for the new song and returns pointer of new node. */
void Insert_New_Song(struct Song **Playlist, char *song_name, char *song_genre, int *song_year)
{
    struct Song* Temp = *Playlist;
    struct Song* New_Song = (struct Song*)malloc(sizeof(struct Song));  /* Allocate memory for the New_Song */

    strcpy(New_Song->name, song_name);                                  /* Inserting song name */
    strcpy(New_Song->genre, song_genre);                                /* Inserting song genre */
    New_Song->year = song_year;                                         /* Inserting song year */
    New_Song->pNext = NULL;                                             /* Appoint a pointer for the next node as NULL */

    if(*Playlist == NULL)                                               /* If the head is NULL it is the first element */
    {
        *Playlist = New_Song;                                           /* Assigning head to new node */
    }
    else
    {
        while (Temp->pNext != NULL) Temp = Temp->pNext;                 /* If next node is not empty iterate through other nodes */
        Temp->pNext = New_Song;                                         /* Appointing the previous of the Initial node to New song */
        New_Song->pNext = NULL;                                         /* Appoint a pointer for the next node as NULL */
    }
}

/* Deletes songs older than given year */
void Delete_Year(struct Song **Playlist, int year)
{
    struct Song* current = *Playlist;         /* Point a new structure to the Playlist */
    struct Song* prev=*Playlist;              /* Point a new structure to the Playlist */

    while(current != NULL)                    /* If the given Playlist is not empty */
    {
        if(current->year < year)              /* If the song's release year is older than the year given*/
        {
            if(current == *Playlist)          /* If the Node is head */
            {
                *Playlist=current->pNext;     /* Move head to the next node */
                free(current);                /* Remove the node that is older than the given year  */
                current = *Playlist;          /* Hold the next node */
            }
            else
            {
                prev->pNext = current->pNext;  /* Bind the next of the node to the prev's next */
                free(current);                 /* Remove the node that is older than the given year  */
                current = prev->pNext;         /* Hold the next node  */
            }
        }

        else
        {
            prev = current;                    /* Hold current node in the previous */
            current = current->pNext;          /* Move to the next node */
        }
    }

}

/* Deletes songs with given genre */
void Delete_Genre(struct Song **Playlist, char  *genre)
{
    struct Song* current = *Playlist;           /* Point a new structure to the Playlist */
    struct Song* prev=*Playlist;                /* Point a new structure to the Playlist */

    while(current != NULL)                      /* If the given Playlist is not empty */
    {
        if(!strcasecmp(current->genre, genre))  /* If the given genre is match with the one with the node */
        {
            if(current == *Playlist)            /* If the Node is head */
            {
                *Playlist=current->pNext;       /* Move head to the next node */
                free(current);                  /* Remove the node that holds unwanted genre  */
                current = *Playlist;            /* Hold the next node */
            }
            else
            {
                prev->pNext = current->pNext;   /* Bind the next of the node to the prev's next */
                free(current);                  /* Remove the node that holds unwanted genre  */
                current = prev->pNext;          /* Hold the next node  */
            }
        }

        else 
        {
            prev = current;                     /* Hold current node in the previous */
            current = current->pNext;           /* Move to the next node */ 
        }
    }

}

/* Combine two created playlist and creates a user playlist after deletions */
void Create_User_Playlist(struct Song **Playlist, struct Song **UserPlaylist, int del_number)
{
    struct Song* current = *Playlist;           /* Point a new structure to the Playlist */
    struct Song* prev=*Playlist;                /* Point a new structure to the Playlist */
    int j = 0;

    while(current != NULL && j < del_number)    /* If the list is note empty and it is not exceed the number that is given to cut and paste */
    {
        if(current == *Playlist)                /* If the Node is head */
        {
            *Playlist=current->pNext;           /* Move head to the next node */
            Insert_New_Song(UserPlaylist, current->name, current->genre, current->year);  /* Insert the cut node to the User Playlist */
            free(current);                      /* Remove the node from Playlist */
            current = *Playlist;                /* Hold the next node */
        }
        else
        {
            prev->pNext = current->pNext;       /* Bind the next of the node to the prev's next */
            Insert_New_Song(UserPlaylist, current->name, current->genre, current->year);  /* Insert the cut node to the User Playlist */
            free(current);                      /* Remove the node from Playlist */
            current = prev->pNext;              /* Hold the next node  */
        }

        j++;                                    /* Increase the cut and paste count */
    }

}

/* Display the playlists */
void Display (struct Song *Playlist)
{
    if(Playlist == NULL)                /* If the playlist is NULL */
    {
        printf("List is empty!\n");
    }
    else                               /* If the playlist is not empty */
    {
        struct Song* Temp = Playlist;  /* Hold playlist in a temporary list */

        while(Temp != NULL)            /* Until come to the end */
        {
            printf("Name:%s, Genre:%s, Year:%d\n", Temp->name, Temp->genre, Temp->year);
            Temp = Temp->pNext;       /* Move to the next one */
        }

        printf("\n");
    }
}