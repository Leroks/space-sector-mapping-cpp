#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {

public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);

    Sector *findMin(Sector *node);

    void deleteSector(const std::string& sector_code);
    void recursiveSectorDeletion(Sector*& Root, const std::string& sector_code);
    void recursiveDeleteBST(Sector* sector);
    void recursiveSectorsInOrder(Sector* root);
    void displaySectorsInOrder();
    void recursiveSectorsPreOrder(Sector* root);
    void displaySectorsPreOrder();
    void recursiveSectorsPostOrder(Sector* root);
    void displaySectorsPostOrder();
    void recursiveSectorInsertion(Sector*& root, Sector* newNode);
    void getStellarPath(Sector*& pSector, const std::string& sector_code, std::vector<Sector*>& mainpath);

    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);


};

#endif // SPACESECTORBST_H
