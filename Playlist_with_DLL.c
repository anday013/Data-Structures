#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Track
{
    char *title;
    char *genre;
    char *artist;
    int duration;
} typedef Track;

struct TrackNode
{
    Track *track;
    struct TrackNode *prevTrack;
    struct TrackNode *nextTrack;
} typedef TrackNode;

struct Playlist
{
    char *title;
    TrackNode *head;
    TrackNode *tail;
    int numOfTracks;
    int totalDuration;
    TrackNode *currentTrack;
    int currentDuration;
} typedef Playlist;

//Functions
Track *Track_new(char *title, char *genre, char *artist, int duration);
TrackNode *TrackNode_new(Track *track);
Playlist *Playlist_new(char *title);
void Playlist_remove(Playlist **playlist, char *TTitle);
void Playlist_append(Playlist **playlist, Track *TTrack);
void Playlist_play(Playlist *playlist);
void Playlist_clear(Playlist **playlist);
void PLaylist_shuffle(Playlist **playlist);
void Playlist_move2(Playlist **playlist1, Playlist **playlist, char *title);
TrackNode *Playlist_findNode(Playlist *playlist, char *title);
void Playlist_changeorder(Playlist **playlist, char *TTitle, int order);
// Track_new(); +
// TrackNode_new(track); +
// Playlist_new(Title); +
// Playlist_append(Playlist,TTrack); +
// Platlist_remove(Playlist,TTitle); +
// Playlist_move2(Pl1,Pl2,Title); +
// Playlist_clear(Playlist); +
// Playlist_changeorder(Playlist,TTitle, order);
// Playlist_sort_byTitle(Playlist);
// Playlist_shuffle(Playlist);

int main()
{
    Track *track1 = Track_new("Wish you were here", "Rock", "Pink Floyd", 240);
    Track *track2 = Track_new("Elif Dedim", "Turku", "Halk", 9999);
    Track *track3 = Track_new("Hekimoglu", "Turku", "Cakir", 42);
    Track *track4 = Track_new("Eysan", "OC", "Omer", 3);
    Playlist *playlist = Playlist_new("Kurtlar Vadisi");
    Playlist *playlist2 = Playlist_new("Ezel");
    Playlist_append(&playlist, track1);
    Playlist_append(&playlist, track2);
    Playlist_append(&playlist, track3);
    Playlist_append(&playlist, track4);
    printf("\nInitial version: \n");
    Playlist_play(playlist);
    Playlist_changeorder(&playlist, track2->title, 1);
    printf("\nAfter changeOrder: \n");
    Playlist_play(playlist);
    // Playlist_append(&playlist2, track4);
    // printf("***************************************\n");
    // Playlist_play(playlist);
    // printf("***************************************\n");
    // Playlist_move2(&playlist, &playlist2, track3->title);
    // printf("***************************************\n");
    // Playlist_play(playlist);
    // printf("******************\n");
    // Playlist_play(playlist2);

    // Playlist_remove(&playlist, track1->title);
    // Playlist_remove(&playlist, track1->title);
    // Playlist_clear(&playlist);
    // Playlist_play(playlist);
    // printf("%s\n", playlist->head->track->title);
    // printf("%s\n", playlist->head->nextTrack->track->title);
    // printf("%s\n", playlist->tail->track->title);

    return 0;
}

Track *Track_new(char *title, char *genre, char *artist, int duration)
{
    Track *newtrack = (Track *)malloc(sizeof(Track));
    newtrack->title = title;
    newtrack->artist = artist;
    newtrack->genre = genre;
    newtrack->duration = duration;
    return newtrack;
}

TrackNode *TrackNode_new(Track *track)
{
    TrackNode *newTrackNode = (TrackNode *)
        malloc(sizeof(TrackNode));
    newTrackNode->track = track;
    newTrackNode->nextTrack = NULL;
    newTrackNode->prevTrack = NULL;
    return newTrackNode;
}

Playlist *Playlist_new(char *title)
{
    Playlist *newPlaylist = (Playlist *)
        malloc(sizeof(Playlist));
    newPlaylist->title = title;
    newPlaylist->head = NULL;
    newPlaylist->tail = NULL;
    newPlaylist->currentTrack = NULL;
    return newPlaylist;
}

void Playlist_append(Playlist **playlist, Track *TTrack)
{
    TrackNode *newTrackNode = TrackNode_new(TTrack);
    if ((*playlist)->head == NULL)
    {
        (*playlist)->head = newTrackNode;
        (*playlist)->tail = newTrackNode;
        (*playlist)->totalDuration += newTrackNode->track->duration;
        (*playlist)->numOfTracks++;
        return;
    }
    // if ((*playlist)->tail == NULL)
    // {
    //     (*playlist)->tail = newTrackNode;
    //     (*playlist)->tail->prevTrack = (*playlist)->head;
    //     (*playlist)->head->nextTrack = (*playlist)->tail;
    //     (*playlist)->totalDuration += newTrackNode->track->duration;
    //     return;
    // }
    (*playlist)->tail->nextTrack = newTrackNode;
    newTrackNode->prevTrack = (*playlist)->tail;
    (*playlist)->tail = newTrackNode;
    (*playlist)->totalDuration += newTrackNode->track->duration;
    (*playlist)->numOfTracks++;
    printf("Track '%s' successfully added into playlist '%s'!\n", TTrack->title, (*playlist)->title);
}

void Playlist_remove(Playlist **playlist, char *TTitle)
{
    TrackNode *temp = (*playlist)->head;
    if (strcmp((*playlist)->head->track->title, TTitle) == 0)
    {
        (*playlist)->head = (*playlist)->head->nextTrack;
        (*playlist)->totalDuration -= (*playlist)->head->track->duration;
        (*playlist)->numOfTracks--;
        printf("Track '%s' successfully added into playlist '%s'!\n", TTitle, (*playlist)->title);
        return;
    }
    if (strcmp((*playlist)->tail->track->title, TTitle) == 0)
    {
        (*playlist)->tail = (*playlist)->tail->prevTrack;
        (*playlist)->tail->nextTrack = NULL;
        (*playlist)->totalDuration -= (*playlist)->head->track->duration;
        (*playlist)->numOfTracks--;
        printf("Track '%s' successfully added into playlist '%s'!\n", TTitle, (*playlist)->title);
        return;
    }
    while ((*playlist)->head->nextTrack != NULL)
    {
        if (strcmp((*playlist)->head->track->title, TTitle) == 0)
        {
            (*playlist)->head->prevTrack->nextTrack = (*playlist)->head->nextTrack;
            (*playlist)->head->nextTrack->prevTrack = (*playlist)->head->prevTrack;
            (*playlist)->totalDuration -= (*playlist)->head->track->duration;
            (*playlist)->numOfTracks--;
            printf("Track '%s' is succesfully deleted from playlist '%s'!\n", TTitle, (*playlist)->title);
            (*playlist)->head = temp;
            return;
        }
        (*playlist)->head = (*playlist)->head->nextTrack;
    }
    (*playlist)->head = temp;
    printf("The track '%s' couldn't been found in playlist '%s'!\n", TTitle, (*playlist)->title);
}

void Playlist_play(Playlist *playlist)
{
    TrackNode *temp = playlist->head;
    if (playlist->head == NULL)
    {
        printf("Playlist is empty.\n");
        return;
    }
    printf("Playlist '%s':\n", playlist->title);
    while (playlist->head != NULL)
    {
        printf("%s\n", playlist->head->track->title);
        playlist->head = playlist->head->nextTrack;
    }
    playlist->head = temp;
}

void Playlist_clear(Playlist **playlist)
{
    if ((*playlist)->head == NULL)
    {
        printf("Playlist '%s' is invalid!\n", (*playlist)->title);
        return;
    }
    if ((*playlist)->tail == NULL)
    {
        printf("Playlist '%s' is invalid!\n", (*playlist)->title);
        return;
    }
    (*playlist)->head = NULL;
    (*playlist)->tail = NULL;
    if ((*playlist)->currentTrack != NULL)
    {
        (*playlist)->currentTrack = NULL;
    }
    (*playlist)->currentDuration = 0;
    (*playlist)->numOfTracks = 0;
    (*playlist)->totalDuration = 0;
    printf("Playlist '%s' is clean now!\n", (*playlist)->title);
}

TrackNode *Playlist_findNode(Playlist *playlist, char *title)
{
    TrackNode *temp = playlist->head;
    if (strcmp(playlist->tail->track->title, title) == 0)
    {
        return playlist->tail;
    }
    while (playlist->head != playlist->tail)
    {
        if (strcmp(playlist->head->track->title, title) == 0)
        {
            TrackNode *newTrackNode = playlist->head;
            playlist->head = temp;
            return newTrackNode;
        }
        playlist->head = playlist->head->nextTrack;
    }
    playlist->head = temp;
    printf("The track '%s' couldn't been found in playlist '%s'!\n", title, playlist->title);
    return NULL;
}

void Playlist_move2(Playlist **playlist1, Playlist **playlist2, char *title)
{
    TrackNode *newTrackNode = Playlist_findNode((*playlist1), title);
    if (newTrackNode == NULL)
    {
        printf("Track title couldn't been found in playlist!\n");
        return;
    }
    Playlist_append(playlist2, newTrackNode->track);
    Playlist_remove(playlist1, title);
    printf("Track '%s' from playlist '%s' has been  successfully moved to playlist '%s'\n", title, (*playlist1)->title, (*playlist2)->title);
}

void Playlist_changeorder(Playlist **playlist, char *TTitle, int order)
{
    int counter = 0;
    TrackNode *temp = (*playlist)->head;
    TrackNode *newTrackNode;
    while ((*playlist)->head->nextTrack != NULL)
    {
        if (strcmp((*playlist)->head->track->title, TTitle) == 0)
        {
            TrackNode *newTrackNode = (*playlist)->head;
            Playlist_remove(playlist, newTrackNode->track->title);
            break;
        }
        (*playlist)->head = (*playlist)->head->nextTrack;
    }

    if(newTrackNode == NULL) 
    {
        printf("Track title couldn't been found in playlist!\n");
        return;
    }
    temp = (*playlist)->head;
    if (order >= (*playlist)->numOfTracks)
    {
        Playlist_append(playlist, newTrackNode->track);
    }
    else
    {
        while (counter != order - 1)
        {
            (*playlist)->head = (*playlist)->head->nextTrack;
            counter++;
        }
        if(order == 1)
        {
            newTrackNode->nextTrack = (*playlist)->head;
            (*playlist)->head->nextTrack = (*playlist)->head->nextTrack->nextTrack;
            (*playlist)->head = newTrackNode;
            return;
        }
        newTrackNode->nextTrack = (*playlist)->head->nextTrack;
        (*playlist)->head->nextTrack = newTrackNode;
        (*playlist)->head = temp;
    }
}