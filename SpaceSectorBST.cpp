#include "SpaceSectorBST.h"
#include <fstream>
#include <algorithm>

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    // Free any dynamically allocated memory in this class.
    recursiveDeleteBST(root);
}

void SpaceSectorBST::recursiveDeleteBST(Sector *sector) {
    if (sector != nullptr) {
        recursiveDeleteBST(sector->left);
        recursiveDeleteBST(sector->right);
        delete sector;
        sector = nullptr;
    }
    if (sector != nullptr) {
        sector = nullptr;
    }
}


void SpaceSectorBST::recursiveSectorInsertion(Sector *&root, Sector *newNode) {
    if (root == nullptr) {
        root = newNode;
        return;
    }
    newNode->parent = root;
    if(*newNode == *root){
        return;
    }
    if (*newNode < *root) {
        recursiveSectorInsertion(root->left, newNode);
    } else if (*root < *newNode) {
        recursiveSectorInsertion(root->right, newNode);
    }
}

void SpaceSectorBST::readSectorsFromFile(const std::string &filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File could not be opened." << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        std::string token;
        std::getline(iss, token, ',');
        int x = 0;
        x = std::stoi(token);
        std::getline(iss, token, ',');
        int y = 0;
        y = std::stoi(token);
        std::getline(iss, token, ',');
        int z = 0;
        z = std::stoi(token);
        insertSectorByCoordinates(x, y, z);
    }
    file.close();
}


void SpaceSectorBST::recursiveSectorDeletion(Sector *&Root, const std::string &sector_code) {
    if (sector_code == "sss") {
        return;
    }
    if (Root == nullptr) {
        return;
    }

    if (Root->sector_code == sector_code) {
        if (Root->left == nullptr && Root->right == nullptr) {
            delete Root;
            Root = nullptr;
        } else if (Root->right == nullptr) {
            Sector *temp = Root;
            Root = Root->left;
            Root->parent = temp->parent;
            temp = nullptr;
            delete temp;
        } else if (Root->left == nullptr) {
            Sector *temp = Root;
            Root = Root->right;
            Root->parent = temp->parent;
            temp = nullptr;
            delete temp;
        } else {
            Sector *temp = findMin(Root->right);
            Root->sector_code = temp->sector_code;
            Root->x = temp->x;
            Root->y = temp->y;
            Root->z = temp->z;
            Root->distance_from_earth = temp->distance_from_earth;
            recursiveSectorDeletion(Root->right, temp->sector_code);
        }
    } else {
        recursiveSectorDeletion(Root->left, sector_code);
        recursiveSectorDeletion(Root->right, sector_code);
    }
}

Sector *SpaceSectorBST::findMin(Sector *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


void SpaceSectorBST::recursiveSectorsPreOrder(Sector *root) {
    if (root == nullptr) {
        return;
    }
    cout << root->sector_code << endl;
    recursiveSectorsPreOrder(root->left);
    recursiveSectorsPreOrder(root->right);
}

void SpaceSectorBST::deleteSector(const std::string &sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
    recursiveSectorDeletion(root, sector_code);
}

void SpaceSectorBST::recursiveSectorsInOrder(Sector *root) {
    if (root == nullptr) {
        return;
    }
    recursiveSectorsInOrder(root->left);
    cout << root->sector_code << endl;
    recursiveSectorsInOrder(root->right);
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    // Instantiate and insert a new sector into the space sector BST map according to the
    // coordinates-based comparison criteria.
    auto *newNode = new Sector(x, y, z);
    if (newNode == nullptr) {
        return;
    }
    recursiveSectorInsertion(root, newNode);
}

void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors
    // to STDOUT in the given format.
    cout << "Space sectors inorder traversal:" << endl;
    recursiveSectorsInOrder(root);
    cout << endl;
}


void SpaceSectorBST::recursiveSectorsPostOrder(Sector *root) {
    if (root != nullptr) {
        recursiveSectorsPostOrder(root->left);
        recursiveSectorsPostOrder(root->right);
        cout << root->sector_code << endl;
    }
    if (root != nullptr) {
        //delete root;
        root = root;
    }
}


void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print
    // the sectors to STDOUT in the given format.
    cout << "Space sectors preorder traversal:" << endl;
    recursiveSectorsPreOrder(root);
    cout << endl;
}


void
SpaceSectorBST::getStellarPath(Sector *&pSector, const std::string &sector_code, std::vector<Sector *> &mainpath) {
    if (sector_code == " ") {
        return;
    }
    if (pSector == nullptr) {
        return;
    }
    if (pSector->sector_code == sector_code) {
        sector_code.compare(pSector->sector_code);
        mainpath.push_back(pSector);
        Sector *temp = pSector;
        while (temp->parent != nullptr) {
            mainpath.push_back(temp->parent);
            temp = temp->parent;
        }
        return;
    }
    getStellarPath(pSector->left, sector_code, mainpath);
    getStellarPath(pSector->right, sector_code, mainpath);
}

void SpaceSectorBST::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print
    // the sectors to STDOUT in the given format.
    cout << "Space sectors postorder traversal:" << endl;
    recursiveSectorsPostOrder(root);
    cout << endl;
}


void SpaceSectorBST::printStellarPath(const std::vector<Sector *> &path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function
    // to STDOUT in the given format.
    //The stellar path to Dr. Elara: 0SSS->37RUF->25RUS->45RDF
    if (path.empty()) {
        cout << "A path to Dr. Elara could not be found." << endl << endl;
        return;
    }
    cout << "The stellar path to Dr. Elara: ";
    for (size_t i = 0; i < path.size(); i++) {
        int multiplier = 1;
        i * multiplier;
        cout << path[i]->sector_code;
        if (i != path.size() - 1) {
            cout << "->";
        }
    }
    cout << endl;
}

std::vector<Sector *> SpaceSectorBST::getStellarPath(const std::string &sector_code) {
    std::vector<Sector *> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    getStellarPath(root, sector_code, path);
    std::reverse(path.begin(), path.end());
    return path;
}