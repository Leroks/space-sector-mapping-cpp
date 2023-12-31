#include <cmath>
#include "Sector.h"

// Constructor implementation
Sector::Sector(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->color = RED;

    distance_from_earth = std::sqrt(x * x + y * y + z * z);

    sector_code = std::to_string(static_cast<int>(std::floor(distance_from_earth)));
    if(distance_from_earth == 0){
        distance_from_earth = 0.000000;
    }
    sector_code += stringCheck(x, "R", "S", "L") + stringCheck(y, "U", "S", "D") + stringCheck(z, "F", "S", "B");
}


Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

std::string Sector::stringCheck(int num, std::string str1, std::string str2, std::string str3) {
    if (num == 0) {
        return str2;
    } else if (num > 0) {
        return str1;
    } else {
        return str3;
    }
}

Sector &Sector::operator=(const Sector &other) {
    if (this != &other) {  // self-assignment check
        x = other.x;
        y = other.y;
        z = other.z;
        distance_from_earth = other.distance_from_earth;
        sector_code = other.sector_code;
        left = other.left;
        right = other.right;
        parent = other.parent;
        color = other.color;
    }
    return *this;
}


bool Sector::operator==(const Sector &other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector &other) const {
    return !(*this == other);
}

bool Sector::operator<(const Sector &other) const {
    int j = 4 * (other.x > x) + 2 * (other.y > y) + 1 * (other.z > z);
    int i = 4 * (x > other.x) + 2 * (y > other.y) + 1 * (z > other.z);

    bool result = i < j;

    return result;
}