#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Track
{
    char *title;
    char *genre;
    char *artist;
    double duration;
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
void Playlist_sort_byTitle(Playlist **playlist);
static int myCompare(const void *a, const void *b);
void sort(const char *arr[], int n);
void swap(char **a, char **b);
void randomize(const char *arr[], int n);
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
    Track *track1 = Track_new("Wish you were here", "Rock", "Pink Floyd", 5);
    Track *track2 = Track_new("Bohemian Rhapsody", "Rock", "Queen", 6);
    Track *track3 = Track_new("We Will Rock You", "Rock", "Queen", 4);
    Track *track4 = Track_new("Don't Stop Me Now", "Rock", "Queen", 3);
    Track *track5 = Track_new("Havana", "Pop", "Camila Cabello", 3.5);
    Track *track6 = Track_new("Happy", "Pop", "Pharrell Williams", 4.5);
    Playlist *playlist = Playlist_new("Mix");
    Playlist *playlist2 = Playlist_new("Rock");
    Playlist_append(&playlist, track1);
    Playlist_append(&playlist2, track1);
    Playlist_append(&playlist, track2);
    Playlist_append(&playlist2, track2);
    Playlist_append(&playlist, track3);
    Playlist_append(&playlist2, track3);
    Playlist_append(&playlist, track4);
    Playlist_append(&playlist2, track4);
    Playlist_append(&playlist, track5);
    Playlist_append(&playlist, track6);
    // printf("\nInitial version: \n");
    printf("\n*********************************************\n");
    Playlist_play(playlist);
    printf("\n*********************************************\n");
    // Playlist_sort_byTitle(&playlist);
    PLaylist_shuffle(&playlist);
    // Playlist_changeorder(&playlist, track2->title, 1);
    // printf("\nAfter changeOrder: \n");
    printf("\n*********************************************\n");
    Playlist_play(playlist);
    printf("\n*********************************************\n");
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
        (*playlist)->head->nextTrack->prevTrack = NULL;
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

    if ((*playlist)->head == NULL || (*playlist)->tail == NULL)
    {
        printf("Playlist '%s' is invalid!\n", (*playlist)->title);
        return;
    }
    while ((*playlist)->head->nextTrack != NULL)
    {
        free((*playlist)->head);
    }
    if ((*playlist)->currentTrack != NULL || (*playlist)->currentTrack == NULL)
    {
        free((*playlist)->currentTrack);
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
//Change_order doesn't working
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

    if (newTrackNode == NULL)
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
        if (order == 1)
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

void Playlist_sort_byTitle(Playlist **playlist)
{
    int numOfTracks = (*playlist)->numOfTracks;
    TrackNode *temp = (*playlist)->head;
    const char *arr[numOfTracks];
    if ((*playlist)->head == NULL)
    {
        printf("Playlist is empty.\n");
        return;
    }
    int i = 0;
    while ((*playlist)->head != NULL)
    {
        arr[i++] = (*playlist)->head->track->title;
        // printf("%s\n", (*playlist)->head->track->title);
        (*playlist)->head = (*playlist)->head->nextTrack;
    }
    (*playlist)->head = temp;
    int n = sizeof(arr) / sizeof(arr[0]);
    sort(arr, n);
    i = 0;
    while (i < numOfTracks)
    {
        char *name = (char *)arr[i++];
        TrackNode *newTrackNode = Playlist_findNode((*playlist), name);
        Playlist_remove(playlist, newTrackNode->track->title);
        Playlist_append(playlist, newTrackNode->track);
    }
}





void PLaylist_shuffle(Playlist **playlist) {
	int numOfTracks = (*playlist)->numOfTracks;
    TrackNode *temp = (*playlist)->head;

	const char* arr[numOfTracks];
	if ((*playlist)->head == NULL)
    {
        printf("Playlist is empty.\n");
        return;
    }

    int i=0;
    while ((*playlist)->head != NULL)
    {
    	arr[i++] = (*playlist)->head->track->title;
        (*playlist)->head = (*playlist)->head->nextTrack;
    }
    (*playlist)->head = temp;

	int n = sizeof(arr) / sizeof(arr[0]);
	randomize(arr, n);

	i=0;
    while(i<numOfTracks){
    	char* name = (char *)arr[i++];
    	TrackNode *newTrackNode = Playlist_findNode((*playlist), name);
    	Playlist_remove(playlist, newTrackNode->track->title);
    	Playlist_append(playlist, newTrackNode->track);
    }
}








static int myCompare(const void *a, const void *b)
{
    return strcmp(*(const char**)a, *(const char**)b); 
}

void sort(const char *arr[], int n)
{
    qsort(arr, n, sizeof(const char *), myCompare);
}

void swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void randomize(const char *arr[], int n)
{
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap((char **)&arr[i], (char **)&arr[j]);
    }
}