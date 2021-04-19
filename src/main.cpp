#include "song.h"
#include "retrieve_data.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void getUserChoices(bool options[]);
void getUserInputs(bool options[], float inputs[]);
bool checkInput(string choice);
float calcDistance(const vector<pair<bool, float>> criteria, Song song);
pair<float, string>* calcHeap(const unordered_map<string, Song>& songs, const int arrSize, const vector<pair<bool, float>> criteria);
void returnPlaylist(const pair<float, string>* heapPtr, const unordered_map<string, Song>& songs);

int main()
{
    unordered_map<string, Song> songs;
    vector<pair<bool, float>> criteria; //Vector containing whether or not to use the nth criteria, and the value given for said criteria.
    loadSongs(songs);

    //Input Interface goes here
    cout << "Welcome to Moodify!" << endl << endl;

    bool runApplication = true;
    while(runApplication)
    {
        /* Get User Input */
        cout << "Getting user input..." << endl;
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
















// //Calculates distance based on the criteria specified from the input song and returns a float value.
// float calcDistance(const vector<pair<bool, float>> criteria, Song song)
// {
//     return 0.0f;
// }
// //Returns the pointer to an array of pairs of floats for the distance and strings for the IDs with a size specified by the user.
// //Keeps only the arrSize smallest heaps, discards the rest.
// pair<float, string>* calcHeap(const unordered_map<string, Song>& songs, const int arrSize, const vector<pair<bool, float>> criteria)
// {
//     pair<float, string> paired = make_pair(0.0f, "");
//     pair<float, string>* ptr = &paired;
//     return ptr;
// }
// //Prints out the playlist generated by the heap.
// void returnPlaylist(const pair<float, string>* heapPtr, const unordered_map<string, Song>& songs)
// {

// }