/**
 * file main.c
 *
 * Author: Erten
 * brief Implementation of multithread application
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "main.h"
#include "linkedlist.h"

struct Song* Playlist1     = NULL;  /* Initializing new playlist */
struct Song* Playlist2     = NULL;  /* Initializing new playlist */
struct Song* User_Playlist = NULL;  /* Initializing new playlist */

pthread_mutex_t List1;              /* Declare mutex for Playlist1 */
pthread_mutex_t List2;              /* Declare mutex for Playlist2 */
pthread_mutex_t UserList;           /* Declare mutex for User Playlist */

int song_year;                      /* Variable for user input */
char *genre[15] ;                   /* Variable for user input */

void main()
{
    int i, Random_Number;

    pthread_t tid[5];

    for(i= 0; i<10; i++)     /* Creating a playlist with 10 node */
    {
        Random_Number = rand() % 20;
        Insert_New_Song(&Playlist1, Listed_Songs[Random_Number][0], Listed_Songs[Random_Number][1], Song_Years[Random_Number]); /* Taking name, genre and year from look up table in main.h */
    }

    for(i= 10; i<20; i++)    /* Creating a playlist with 10 node */
    {
        Random_Number = rand() % 20;
        Insert_New_Song(&Playlist2, Listed_Songs[Random_Number][0], Listed_Songs[Random_Number][1], Song_Years[Random_Number]); /* Taking name, genre and year from look up table in main.h */
    }

    /* Display initial playlists (Playlist 1 and Playlist 2) without any operation on them */
    printf("Initial playlists are created as follows:\n");

    printf("Playlist One: \n");
    Display(Playlist1);
    
    printf("Playlist Two: \n");
    Display(Playlist2);

    /* Take inputs from the user for deletion operation */
    printf("Please enter the genre you want to delete:\n");
    scanf("%s", &genre);
    
    printf("\nPlease enter the year that you don't want older than it:\n");
    scanf("%d", &song_year);
    printf("\n");

    /* Initialize mutexs */
    pthread_mutex_init(&List1, NULL);
    pthread_mutex_init(&List2, NULL);
    pthread_mutex_init(&UserList, NULL);
    
    /* Create threads */
    for(i=0; i<3; i++)
    {
            pthread_create(&tid[i], NULL, (void *) threadFunction_1, NULL);
    }

    pthread_create(&tid[3], NULL, (void *) threadFunction_2,  NULL);
    pthread_create(&tid[4], NULL, (void *) threadFunction_3,  NULL);

    /* End threads */
    for(i=0; i<5; i++)
    {
        pthread_join(tid[i], NULL);
    }

    /* Remove mutexs */
    pthread_mutex_destroy(&List1);
    pthread_mutex_destroy(&List2);
    pthread_mutex_destroy(&UserList);
    
    /* Display all playlist after threads done with their operation */
    printf("Playlist One: \n");
    Display(Playlist1);
    printf("\n");
    printf("Playlist Two: \n");
        Display(Playlist2);
    printf("\n");
    printf("User Playlist: \n");
    Display(User_Playlist);

    exit(0); /* Terminate application */

}

void* threadFunction_1(void* args)
{
        if(!pthread_mutex_lock(&List1))           /* Check if the mutex for Playlist 1 is free */
        {
            if(!pthread_mutex_lock(&UserList))    /* Check if the mutex for User Playlist is free */
            {
                Create_User_Playlist(&Playlist1, &User_Playlist, (rand() % 10 + 1));    /* Cut and paste random amount of song to the user playlist */
                pthread_mutex_unlock(&List1);     /* Release the mutex for Playlist 1 */
                pthread_mutex_unlock(&UserList);  /* Release the mutex for User Playlist */
            }
        }

        if(!pthread_mutex_lock(&List2))           /* Check if the mutex for Playlist 2 is free */
        {
            if(!pthread_mutex_lock(&UserList))    /* Check if the mutex for User Playlist is free */
            {
                Create_User_Playlist(&Playlist2, &User_Playlist, (rand() % 10 + 1));    /* Cut and paste random amount of song to the user playlist */
                pthread_mutex_unlock(&List2);     /* Release the mutex for Playlist 2 */
                pthread_mutex_unlock(&UserList);  /* Release the mutex for User Playlist */
            }
        }

        pthread_exit(NULL);    /* Terminate thread */
}

void* threadFunction_2(void* args)
{
    if(!pthread_mutex_lock(&List1))           /* Check if the mutex for Playlist 1 is free */
    {
        Delete_Genre(&Playlist1, genre);      /*Delete songs with given genre from Playlist 1 */
        pthread_mutex_unlock(&List1);         /* Release the mutex for Playlist 1 */
    }

    if(!pthread_mutex_lock(&List2))           /* Check if the mutex for Playlist 2 is free */
    {
        Delete_Genre(&Playlist2, genre);      /*Delete songs with given genre from Playlist 2 */
        pthread_mutex_unlock(&List2);         /* Release the mutex for Playlist 2 */
    }

    if(!pthread_mutex_lock(&UserList))        /* Check if the mutex for User Playlist is free */
    {
        Delete_Genre(&User_Playlist, genre);  /*Delete songs with given genre from User Playlist */
        pthread_mutex_unlock(&UserList);      /* Release the mutex for User Playlist */
    }

    pthread_exit(NULL);    /* Terminate thread */
}

void* threadFunction_3(void* args)
{
    if(!pthread_mutex_lock(&List1))              /* Check if the mutex for Playlist 1 is free */
    {
        Delete_Year(&Playlist1, song_year);      /* Delete songs older than given year from Playlist 1 */
        pthread_mutex_unlock(&List1);            /* Release the mutex for Playlist 1 */
    }

    if(!pthread_mutex_lock(&List2))              /* Check if the mutex for Playlist 2 is free */
    {
        Delete_Year(&Playlist2, song_year);      /* Delete songs older than given year from Playlist 2 */
        pthread_mutex_unlock(&List2);            /* Release the mutex for Playlist 2 */
    }

    if(!pthread_mutex_lock(&UserList))           /* Check if the mutex for Playlist 2 is free */
    {
        Delete_Year(&User_Playlist, song_year);  /* Delete songs older than given year from User Playlist */
        pthread_mutex_unlock(&UserList);         /* Release the mutex for User Playlist */
    }

    pthread_exit(NULL);    /* Terminate thread */
}