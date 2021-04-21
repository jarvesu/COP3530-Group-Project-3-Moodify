#pragma once
#include <fstream>
#include "song.h"
#include <iostream>
#include <unordered_map>

using namespace std;
//Loads song from a row
Song loadSong(std::ifstream& file, std::string& data)
{
    //19 Elements from CSV Row, Only Need 
    std::string elements[13];

    getline(file, data, ',');
    elements[0] = data; //ID

    getline(file, data, ',');
    elements[1] = data; //Name

    getline(file, data, ','); 
    getline(file, data, ','); 
    elements[2] = data; //Duration

    getline(file, data, ','); 
    elements[3] = data; //Explicit

    getline(file, data, ',');
    elements[4] = data; //Artists

    getline(file, data, ',');
    getline(file, data, ',');
    getline(file, data, ',');
    elements[5] = data; //Danceability

    getline(file,data, ',');
    elements[6] = data; //Energy

    getline(file, data, ',');
    getline(file, data, ',');
    getline(file, data, ',');
    getline(file, data, ',');
    elements[7] = data; //Speechiness


    getline(file, data, ',');
    elements[8] = data; //Liveness

    getline(file, data, ',');
    elements[9] = data; //Name

    getline(file, data, ','); //Skipping the Release Date

    getline(file, data, ',');
    elements[10] = data; //Speechiness

    getline(file, data, ',');
    elements[11] = data; //Tempo

    getline(file, data, ',');
    elements[12] = data; //Happiness

    getline(file, data, ',');
    file >> data; //Skipping the year

    return Song(elements[0], elements[1], elements[2], elements[3], elements[4], elements[5], elements[6], elements[7], elements[8], elements[9], elements[10], elements[11], elements[12]);
}


//Loads data from file
void loadSongs(std::unordered_map<string, Song>& songs)
{
    //Open File
    string filename = "C:/Users/Julian/Documents/GitHub/COP3530-Group-Project-3-Moodify/src/tracks.csv";
    string line;
    ifstream file(filename, ios_base::in);

    if(!file)
    {
        std::cout << "Could not open file!" << std::endl;
        return;
    }

    //Skips the first line with categories
    std::getline(file, line);

    //Go through each line and load corresponding songs
    while(!file.eof())
    {
        cout << "Loading new song" << endl;
        Song newSong = loadSong(file, line);
        songs.insert(make_pair(newSong.getID(), newSong));
    }

    //Close File
    file.close();


}