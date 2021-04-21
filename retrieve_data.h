#pragma once
#include <fstream>
#include "song.h"
#include <iostream>
#include <unordered_map>

using namespace std;
//Loads song from a row
Song loadSong(std::ifstream& file, std::string& data)
{
    //19 Elements from CSV Row, Only Need 13
    std::string elements[13];

    getline(file, data, ',');
    elements[0] = data; //Acousticness

    getline(file, data, ']');
    elements[1] = data; //Artists

    getline(file, data, ',');

    getline(file, data, ',');
    elements[2] = data; //Danceability

    getline(file, data, ',');
    elements[3] = data; //Duration

    getline(file, data, ',');
    elements[4] = data; //Energy

    getline(file, data, ',');
    elements[5] = data; //Explicit

    getline(file,data, ',');
    elements[6] = data; //ID

    getline(file, data, ',');
    elements[7] = data; //Instrumentalness

    getline(file, data, ','); //Skipping the Key

    getline(file, data, ',');
    elements[8] = data; //Liveness

    getline(file, data, ','); //Skipping the Loudness
    getline(file, data, ','); //Skipping the Mode

    getline(file, data, ',');
    elements[9] = data; //Name

    getline(file, data, ','); //Skipping the Popularity
    getline(file, data, ','); //Skipping the Release Date

    getline(file, data, ',');
    elements[10] = data; //Speechiness

    getline(file, data, ',');
    elements[11] = data; //Tempo

    getline(file, data, ',');
    elements[12] = data; //Happiness

    file >> data; //Skipping the year

    return Song(elements[0], elements[1], elements[2], elements[3], elements[4], elements[5], elements[6], elements[7], elements[8], elements[9], elements[10], elements[11], elements[12]);
}

//Loads data from file
bool loadSongs(std::unordered_map<string, Song>& songs)
{
    //Open File
    std::ifstream file;
    std::string filename = "C:\\Users\\gioco\\Dropbox\\My PC (Gio)\\Documents\\Coding\\VisualStudioCode\\DataStructuresProjects\\Final Project\\tracks.csv";
    file.open(filename);
    cout << "File Opened..." << endl;

    if(!file)
    {
        std::cout << "Could not open file!" << std::endl;
        return false;
    }

    //Skips the first line with categories
    std::string line;
    std::getline(file, line);

    //Go through each line and load corresponding songs
    int i = 0;
    while(!file.eof())
    {
        Song newSong = loadSong(file, line);
        songs.insert(make_pair(newSong.getID(), newSong));
        i++;
        if(i == 100)
            break;
    }

    //Close File
    file.close();
    return true;
}