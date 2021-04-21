#include "song.h"
#include "retrieve_data.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <iomanip>
#include <queue>

using namespace std;

void getUserChoices(bool options[]);
void getUserInputs(bool options[], float inputs[]);
bool checkInput(string choice);
float calcDistance(const vector<pair<bool, float>> criteria, Song song);
pair<float, string>* calcHeap(const unordered_map<string, Song>& songs, const int arrSize, const vector<pair<bool, float>> criteria);
void returnPlaylist(const pair<float, string>* heapPtr, const unordered_map<string, Song>& songs);
//pair<float, string>* extractMin(pair<float, string>* arr, int size);
int main()
{
    bool runApplication = true;
    cout << "Welcome to Moodify!" << endl << endl;

    cout << "Loading songs..." << endl;
    unordered_map<string, Song> songs;
    bool loaded = loadSongs(songs);
    if(!loaded)
    {
        cout << "Error loading songs!";
        runApplication = false;
    }

    cout << "Songs loaded." << endl << endl;

    while(runApplication)
    {
        vector<pair<bool, float>> criteria; //Vector containing whether or not to use the nth criteria, and the value given for said criteria.
        /* Get User Input */
        cout << "Getting user input..." << endl;
        string numSongsStr;
        cout << "How many songs do you want in the playlist: ";
        cin >> numSongsStr;
        if(!checkInput(numSongsStr)) { cout << "Please enter a valid number" << endl << endl; continue;}
        int numSongs = int(stof(numSongsStr));
        cout << "Do you want to include explicit songs? (Y/N): ";
        string choice;
        cin >> choice;
        bool _explicit = (choice == "Y") ? true : false;


        cout << endl << "For each of the following indicate which you would like to include (Y/N)" << endl << endl;
        bool options[8];
        getUserChoices(options);
        cout << endl << "For each of the following indicate the percentage you would like (0-100)" << endl << endl;
        float inputs[8];
        getUserInputs(options, inputs);

        for(int i = 0; i < 8; i++)
            criteria.push_back({options[i], inputs[i]});


        /* Begin Playlist Creation */
        cout << "Creating a new playlist..." << endl;

        //Get the songs that most match user needs
        pair<float, string>* minDistanceIDs;
        minDistanceIDs = calcHeap(songs, numSongs, criteria);

        //Print the songs
        //returnPlaylist(minDistanceIDs, songs);


        /* Exit if Needed */
        cout << "Do you want to create a new playlist? (Y/N): ";
        cin >> choice;

        if(choice == "N")
        {
            cout << endl << "Thank you for using Moodify! Have a nice day";
            runApplication = false;
        }
    }

    return 0;
}

//Gets the choices the user wants to use
void getUserChoices(bool options[])
{
    string option;
    cout << "1. Acousticness: ";
    cin >> option;
    options[0] = (option == "Y") ? true : false;

    cout << "2. Danceability: ";
    cin >> option;
    options[1] = (option == "Y") ? true : false;

    cout << "3. Energy: ";
    cin >> option;
    options[2] = (option == "Y") ? true : false;

    cout << "4. Instrumentalness: ";
    cin >> option;
    options[3] = (option == "Y") ? true : false;

    cout << "5. Liveness: ";
    cin >> option;
    options[4] = (option == "Y") ? true : false;

    cout << "6. Speechiness: ";
    cin >> option;
    options[5] = (option == "Y") ? true : false;

    cout << "7. Happiness: ";
    cin >> option;
    options[6] = (option == "Y") ? true : false;

    cout << "8. Tempo: ";
    cin >> option;
    options[7] = (option == "Y") ? true : false;

    cout << endl;
}

//Gets the inputs from the user
void getUserInputs(bool options[], float inputs[])
{
    string choice;
    if(options[0])
    {
        cout << "Acousticness: ";
        cin >> choice;
        inputs[0] = (checkInput(choice)) ? stof(choice)/100 : 0;
    }

    if(options[1])
    {
        cout << "Danceability: ";
        cin >> choice;
        inputs[1] = (checkInput(choice)) ? stof(choice)/100 : 0;
    }

    if(options[2])
    {
        cout << "Energy: ";
        cin >> choice;
        inputs[2] = (checkInput(choice)) ? stof(choice)/100 : 0;
    }

    if(options[3])
    {
        cout << "Instrumentalness: ";
        cin >> choice;
        inputs[3] = (checkInput(choice)) ? stof(choice)/100 : 0;
    }

    if(options[4])
    {
        cout << "Liveness: ";
        cin >> choice;
        inputs[4] = (checkInput(choice)) ? stof(choice)/100 : 0;
    }

    if(options[5])
    {
        cout << "Speechiness: ";
        cin >> choice;
        inputs[5] = (checkInput(choice)) ? stof(choice)/100 : 0;
    }

    if(options[6])
    {
        cout << "Happiness: ";
        cin >> choice;
        inputs[6] = (checkInput(choice)) ? stof(choice)/100 : 0;
    }

    if(options[7])
    {
        cout << "Tempo (0-250 BPM): ";
        cin >> choice;
        float tempo = (checkInput(choice)) ? stof(choice) : 0;
        inputs[7] = 1/tempo;
    }

    cout << endl;
}

bool checkInput(string choice)
{
    for(char i : choice)
        if(!isdigit(i))
            return false;
    return true;
}

//Calculates distance based on the criteria specified from the input song and returns a float value.
float calcDistance(const vector<pair<bool, float>> criteria, Song& song)
{
    vector<float> songCrit;
    songCrit.push_back(song.getAcousticness());
    songCrit.push_back(song.getDanceability());
    songCrit.push_back(song.getEnergy());
    songCrit.push_back(song.getInstrumentalness());
    songCrit.push_back(song.getLiveness());
    songCrit.push_back(song.getSpeechiness());
    songCrit.push_back(song.getTempo());
    songCrit.push_back(song.getHappiness());

    float running = 0.0f;
    for(int i = 0; i < criteria.size(); ++i)
    {
        if(criteria[i].first)
            running += pow(criteria[i].second - songCrit[i], 2);
    }
    return pow(running, 0.5);
}
/*
struct comparator {
    float operator() (const Song& s1, const Song& s2) {
        return s1.getDistance() > s2.getDistance();
    }
};
*/
typedef pair<float, string> pM;

 priority_queue <pM, vector<pM>, greater<pM> >* calcHeap(const unordered_map<string, Song>& songs_, const vector<pair<bool, float>> criteria) {
    priority_queue <pM, vector<pM>, greater<pM> > mH;
    auto ptr = &mH;
    auto it = songs_.begin();
    // Iterate over the map using iterator
    while (it != songs_.end())
    {
        float dist = calcDistance(criteria, it->second);
        mH.push(make_pair(dist, it->first));
        it++;
    }
    return ptr;
}

//Prints out the playlist generated by the heap.
void returnPlaylist(const pair<float, string>* heapPtr, const unordered_map<string, Song>& songs, int arrSize)
{
    //Setup the Table
    cout << setw(60) << "Your New Spotify Playlist" << endl;
    cout << left
    << setw(5) << "No."
    << setw(40) << "Title"
    << setw(50) << "Artist"
    << setw(10) << "Duration"
    << setw(60) << "Link"
    << endl;

    //Iterate through the heap
    for(int i = 0; i < arrSize; i++)
    {
        //Get ID and Song
        string ID = heapPtr[i].second;
        Song currSong = songs.find(ID)->second;

        //Get Title for Resizing
        string title = currSong.getName();
        if(title.size() > 35)
        {
            title = title.substr(0, 32);
            title += "...";
        }

        //Get Artists for Resizing
        vector<string> artistVec = currSong.getArtists();
        string artists = artistVec.at(0);
        for(int i = 1; i < artistVec.size(); i++)
            artists += ", " + artistVec.at(i);
        if(artists.size() > 45)
        {
            artists = artists.substr(0, 42);
            artists += "...";
        }

        //Get Duration
        int duration = currSong.getDuration();

        cout << left
        << setw(5) << i
        << setw(40) << title
        << setw(50) << artists
        << setw(10) << duration / 60 << ":" << duration % 60
        << setw(60) << "https://open.spotify.com/track/" << currSong.getID()
        << endl;
    }
    cout << endl << endl;
}