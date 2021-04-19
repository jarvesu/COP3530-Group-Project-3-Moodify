#include "song.h"
#include "retrieve_data.h"
#include <iostream>

int main()
{
    std::vector<Song> songs;
    loadSongs(songs);

    songs.at(0).getArtists();



    //Song newSong = Song(0, "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 0, 0, 0, 0, 0);

    return 0;
    
}