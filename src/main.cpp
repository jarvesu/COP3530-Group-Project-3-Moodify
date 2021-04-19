#include "song.h"
#include "retrieve_data.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
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
    unordered_map<string, Song> songs;
    vector<pair<bool, float>> criteria; //Vector containing whether or not to use the nth criteria, and the value given for said criteria.
    loadSongs(songs);

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

        //Continue from here


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
//Extracts the minimum element from the heap
pair<float, string>* extractMin(pair<float, string>* arr, int size)
{
    arr[0] = arr[size-1];
    arr[size-1] = { };
    //Sort array heapwise
    int i = 0;
    while((arr[i].first > arr[2*i+1].first || arr[i].first > arr[2*i+1].first && i < (size-3)/2))
    {
        
        if(arr[2*i+1] > arr[2*i+2])
        {
            float tempFloat = arr[i].first;
            string tempStr = arr[i].second;
            arr[i].first = arr[2*i+2].first;
            arr[i].second = arr[2*i+2].second;
            arr[2*i+2].first = tempFloat;
            arr[2*i+2].second = tempStr;
            
        }
        else
        {
            float tempFloat = arr[i].first;
            string tempStr = arr[i].second;
            arr[i].first = arr[2*i+1].first;
            arr[i].second = arr[2*i+1].second;
            arr[2*i+1].first = tempFloat;
            arr[2*i+1].second = tempStr;
        }
    }
    return arr;
}
*/
//Returns the pointer to an array of pairs of floats for the distance and strings for the IDs with a size specified by the user.
//Keeps only the arrSize smallest heaps, discards the rest.
pair<float, string>* calcHeap(const unordered_map<string, Song>& songs, const int arrSize, const vector<pair<bool, float>> criteria)
{
    pair<float, string>* ptr = new pair<float, string>[arrSize]();
    //if the array is empty, set arr[0] equal to the current song's distance.
    //while not in position, shift around
    //if value tries to shift OOB, drop the value from importance
    
    return ptr;
}
//Prints out the playlist generated by the heap.
void returnPlaylist(const pair<float, string>* heapPtr, const unordered_map<string, Song>& songs)
{

}