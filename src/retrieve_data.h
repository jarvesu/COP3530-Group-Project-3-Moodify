#pragma once
#include <fstream>
#include "song.h"
#include <iostream>
#include <unordered_map>

using namespace std;
//Loads song from a row
Song loadSong(std::ifstream& file, std::string& data)
{
    //19 Elements from CSV Row
    std::string elements[19];
    for(int i = 0; i < 19; i++)
    {
        if(i == 18) //If final element in row
        {
            file >> data;
            elements[i] = data;
            continue;
        }

        getline(file, data, ',');
        elements[i] = data;
    }

    return Song(elements[0], elements[1], elements[2], elements[3], elements[4], elements[5], elements[6], elements[7], elements[8], elements[9], elements[10], elements[11], elements[12], elements[13], elements[14], elements[15], elements[16], elements[17], elements[18]);
}

//Loads data from file
bool loadSongs(std::unordered_map<string, Song>& songs)
{
    //Open File
    std::ifstream file;
    std::string filename = "tracks.csv";
    file.open(filename);

    if(!file)
    {
        std::cout << "Could not open file!" << std::endl;
        return false;
    }

    //Skips the first line with categories
    std::string line;
    std::getline(file, line);

    //Go through each line and load corresponding songs
    while(!file.eof())
    {
        Song newSong = loadSong(file, line);
        songs.insert(make_pair(newSong.getID(), newSong));
    }

    //Close File
    file.close();
    return true;
}