#ifndef SECTOR_H
#define SECTOR_H

#include <string>

// Define color constants for Red-Black Tree
const bool RED = true;
const bool BLACK = false;

class Sector {
public:

    Sector(int x, int y, int z); // Constructor declaration
    ~Sector(); // Destructor

    int x, y, z; // Coordinates of the sector 
    double distance_from_earth; // Calculated Euclidean distance from the Earth
    std::string sector_code; // Unique identifier based on coordinates and distance
    Sector *left, *right, *parent; // Pointers to child and parent nodes
    bool color; // Node color for Red-Black Tree

    // Overloaded operators
    bool operator<(const Sector& other) const;
    static std::string stringCheck(int num, std::string str1, std::string str2, std::string str3);
    Sector& operator=(const Sector& other);
    bool operator==(const Sector& other) const;
    bool operator!=(const Sector& other) const;

};

#endif // SECTOR_H
