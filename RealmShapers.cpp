#include "RealmShapers.h"
#include <cmath>
#include <algorithm>

ShaperTree::ShaperTree()
{
}

ShaperTree::~ShaperTree()
{
    // TODO: Free any dynamically allocated memory if necessary
    for (RealmShaper *shaper : realmShapers)
    {
        delete shaper;
    }
    realmShapers.clear();
}

void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers)
{
    // TODO: Insert innitial shapers to the tree
    for (RealmShaper *shaper : shapers)
    {
        insert(shaper);
    }
}

int ShaperTree::getSize()
{
    // TODO: Return number of shapers in the tree
    return realmShapers.size();
}

std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    bool isValid = false;

    // TODO: Check if the index is valin in the tree
    isValid = index >= 0 && index < int(realmShapers.size()) && realmShapers[index] != nullptr;
    return isValid;
}

void ShaperTree::insert(RealmShaper *shaper)
{
    // TODO: Insert shaper to the tree
    // find the correct position for the new shaper
    realmShapers.push_back(shaper);
    /*int index;
    for (index = 0; index < int(realmShapers.size()); index++)
    {
        if (realmShapers[index]->getHonour() < shaper->getHonour())
        {
            break;
        }
    }
    realmShapers.insert(realmShapers.begin() + index, shaper);*/
}

int ShaperTree::remove(RealmShaper *shaper)
{
    // TODO: Remove the player from tree if it exists
    // Make sure tree protects its form (complate binary tree) after deletion of a node
    // return index if found and removed
    // else
    for (size_t i = 0; i < realmShapers.size(); i++)
    {
        if (realmShapers[i] == shaper)
        {
            realmShapers.erase(realmShapers.begin() + i);
            return i;
        }
    }
    return -1;
}

int ShaperTree::findIndex(RealmShaper *shaper)
{
    // return index in the tree if found
    // else
    for (size_t i = 0; i < realmShapers.size(); i++)
    {
        if (realmShapers[i] == shaper)
        {
            return i;
        }
    }
    return -1;
}

int ShaperTree::getDepth(RealmShaper *shaper)
{
    // return depth of the node in the tree if found
    // else
    int index = findIndex(shaper);
    if (index != -1)
    {
        return int(log2(index + 1));
    }
    return -1;
}

int ShaperTree::getDepth()
{
    // return total|max depth|height of the tree
    return getDepth(realmShapers.back());
}

RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    // TODO: Implement duel logic, return the victor
    // Use   std::cout << "[Duel] " << victorName << " won the duel" << std::endl;
    // Use   std::cout << "[Honour] " << "New honour points: ";
    // Use   std::cout << challengerName << "-" << challengerHonour << " ";
    // Use   std::cout << opponentName << "-" << opponentHonour << std::endl;
    // Use   std::cout << "[Duel] " << loserName << " lost all honour, delete" << std::endl;
    RealmShaper *opponent = getParent(challenger);
    if (result)
    {
        challenger->gainHonour();
        opponent->loseHonour();
        replace(challenger, opponent);
        std::cout << "[Duel] " << challenger->getName() << " won the duel" << std::endl;
    }
    else
    {
        challenger->loseHonour();
        opponent->gainHonour();
    }
    std::cout << "[Honour] " << "New honour points: ";
    std::cout << challenger->getName() << "-" << challenger->getHonour() << std::endl;
    std::cout << opponent->getName() << "-" << opponent->getHonour() << std::endl;
    if (challenger->getHonour() <= 0)
    {
        std::cout << "[Duel] " << challenger->getName() << " lost all honour, delete" << std::endl;
        remove(challenger);
    }
    else if (opponent->getHonour() <= 0)
    {
        std::cout << "[Duel] " << opponent->getName() << " lost all honour, delete" << std::endl;
        remove(opponent);
    }
    return *challenger;
}

RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    RealmShaper *parent = nullptr;

    // TODO: return parent of the shaper
    parent = realmShapers[(findIndex(shaper) - 1) / 2];
    return parent;
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high)
{
    // TODO: Change player_low and player_high's positions on the tree
    int index_low = findIndex(player_low);
    int index_high = findIndex(player_high);
    if (index_low != -1 && index_high != -1)
    {
        std::swap(realmShapers[index_low], realmShapers[index_high]);
    }
}

RealmShaper *ShaperTree::findPlayer(RealmShaper shaper)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by object
    // Return the shaper if found
    // Return nullptr if shaper not found
    int index = findIndex(&shaper);
    if (index != -1)
    {
        foundShaper = realmShapers[index];
    }
    return foundShaper;
}

// Find shaper by name
RealmShaper *ShaperTree::findPlayer(std::string name)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by name
    // Return the shaper if found
    // Return nullptr if shaper not found
    for (RealmShaper *shaper : realmShapers)
    {
        if (shaper->getName() == name)
        {
            foundShaper = shaper;
            break;
        }
    }
    return foundShaper;
}

std::vector<std::string> ShaperTree::inOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement inOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation

    // Note: Since SheperTree is not an binary search tree,
    // in-order traversal will not give rankings in correct order
    // for correct order you need to implement level-order traversal
    // still you are to implement this function as well
    if (!isValidIndex(index))
    {
        return result;
    }

    std::vector<std::string> left = inOrderTraversal(2 * index + 1);
    result.insert(result.end(), left.begin(), left.end());

    result.push_back(realmShapers[index]->getName());

    std::vector<std::string> right = inOrderTraversal(2 * index + 2);
    result.insert(result.end(), right.begin(), right.end());

    return result;
}

std::vector<std::string> ShaperTree::preOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement preOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation
    if (!isValidIndex(index))
    {
        return result;
    }

    result.push_back(realmShapers[index]->getName());

    std::vector<std::string> left = preOrderTraversal(2 * index + 1);
    result.insert(result.end(), left.begin(), left.end());

    std::vector<std::string> right = preOrderTraversal(2 * index + 2);
    result.insert(result.end(), right.begin(), right.end());

    return result;
}

std::vector<std::string> ShaperTree::postOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement postOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation
    if (!isValidIndex(index))
    {
        return result;
    }

    std::vector<std::string> left = postOrderTraversal(2 * index + 1);
    result.insert(result.end(), left.begin(), left.end());

    std::vector<std::string> right = postOrderTraversal(2 * index + 2);
    result.insert(result.end(), right.begin(), right.end());

    result.push_back(realmShapers[index]->getName());

    return result;
}

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile)
{
    // TODO: Implement preOrderTraversal in tree
    // write nodes to output file

    // Define and implement as many helper functions as necessary for recursive implementation
    std::vector<std::string> result = preOrderTraversal(index);
    for (std::string name : result)
    {
        outFile << name << std::endl;
    }
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile)
{
    // TODO: Implement level-order traversal
    // write nodes to output file

    // Define and implement as many helper functions as necessary
    for (RealmShaper *shaper : realmShapers)
    {
        outFile << shaper->getName() << std::endl;
    }
}

void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    // TODO: Calculate left index
    int left = 2 * index + 1;
    // TODO: Calculate right index
    int right = 2 * index + 2;

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{
    // TODO: Write the shapers to filename output level by level
    // Use std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
    std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
    std::ofstream file(filename);
    breadthFirstTraversal(file);
}

void ShaperTree::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output pre-order
    // Use std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
    std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
    std::ofstream file(filename);
    preOrderTraversal(0, file);
}
