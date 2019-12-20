/**
 * file linkedlist.h
 *
 * Author: Erten
 * brief Structure definition and function prototypes for linkedlist creation and operation
 **/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct Song {
    char name[25];           /* Song */
    char genre[15];          /* Genre of the song */
    int year;                /* Release year of the song */

    struct Song *pNext;      /* pointer to next song */
};

void Create_User_Playlist(struct Song **Playlist, struct Song **UserPlaylist, int del_number);               /* Prototype for user playlist creation function */
void Insert_New_Song(struct Song **Playlist, char *song_name, char *song_genre, int32_t *song_year);         /* Prototype new node creation function */
void Delete_Year(struct Song **Playlist, int32_t year);                                                      /* Prototype for delete function older than given year */
void Delete_Genre(struct Song **Playlist, char  *genre);                                                     /* Prototype for delete function for given genre */
void Display (struct Song *Playlist);                                                                        /* Prototype for playlist display function */

#endif /* LINKEDLIST_H_ */