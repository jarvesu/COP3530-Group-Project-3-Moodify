#include "song.h"
#include "retrieve_data.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
int main()
{
    
    loadSongs(songs);

    songs.at(0).getArtists();



    //Song newSong = Song(0, "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 0, 0, 0, 0, 0);

    return 0;
    
}