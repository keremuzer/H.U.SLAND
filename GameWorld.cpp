#include "GameWorld.h"

GameWorld::GameWorld() : mapTree(), shaperTree() {}

void GameWorld::initializeGame(std::vector<Isle *> places, std::vector<RealmShaper *> players)
{
    shaperTree.initializeTree(players);
    mapTree.initializeMap(places);
}

Map &GameWorld::getMapTree()
{
    return mapTree;
}
ShaperTree &GameWorld::getShaperTree()
{
    return shaperTree;
}

bool GameWorld::hasAccess(RealmShaper *realmShaper, Isle *isle)
{
    bool hasAccess = false;

    // TODO: Check if the realmShaper has access to explore the isle
    // Get necessary depth values
    // Use mapTree.calculateMinMapDepthAccess
    // Use // std::cout << "[Access Control] " << "RealmShaper not found!" << std::endl;

    RealmShaper *shaper = shaperTree.findPlayer(realmShaper->getName());
    if (shaper == nullptr)
    {
        std::cout << "[Access Control] " << "RealmShaper not found!" << std::endl;
        return hasAccess;
    }
    int playerDepth = shaperTree.getDepth(shaper);
    int totalHeight = shaperTree.getDepth();
    int totalMapDepth = mapTree.getDepth();
    int minMapDepthAccess = mapTree.calculateMinMapDepthAccess(playerDepth, totalHeight, totalMapDepth);
    int isleDepth = mapTree.getIsleDepth(isle);
    if (isleDepth >= minMapDepthAccess)
    {
        hasAccess = true;
    }

    return hasAccess;
}

void GameWorld::exploreArea(RealmShaper *realmShaper, Isle *isle)
{
    // TODO:
    // Check if realmShaper has access
    // Use // std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
    // If realmShaper has access
    // Visit isle,
    // collect item,
    // check overcrowding for Isle,
    // delete Isle if necessary

    // Use // std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
    // Use // std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;
    // Use // std::cout << "[Owercrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;

    // You will need to implement a mechanism to keep track of how many realm shapers are at an Isle at the same time
    // There are more than one ways to do this, so it has been left completely to you
    // Use shaperCount, but that alone will not be enough,
    // you will likely need to add attributes that are not currently defined
    // to RealmShaper or Isle or other classes depending on your implementation
    if (!hasAccess(realmShaper, isle))
    {
        std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
        return;
    }
    if (realmShaper->currentIsle != nullptr)
    {
        realmShaper->currentIsle->decreaseShaperCount();
    }
    realmShaper->currentIsle = isle;
    std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
    realmShaper->collectItem(isle->getItem());
    std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;

    isle->increaseShaperCount();
    if (isle->getShaperCount() > isle->getCapacity())
    {
        std::cout << "[Owercrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;
        realmShaper->currentIsle = nullptr;
        if (isle)
        {
            // mapTree.remove(isle);
        }
    }
}

void GameWorld::craft(RealmShaper *shaper, const std::string &isleName)
{
    // TODO: Check energy and craft new isle if possible
    // Use std::cout << "[Energy] " << shaperName << " has enough energy points: " << shaperEnergyLevel << std::endl;
    // Use std::cout << "[Craft] " << shaperName << " crafted new Isle " << isleName << std::endl;
    // Use std::cout << "[Energy] " << shaperName << " does not have enough energy points: " << shaperEnergyLevel << std::endl;
    if (shaper->hasEnoughEnergy())
    {
        std::cout << "[Energy] " << shaper->getName() << " has enough energy points: " << shaper->getEnergyLevel() << std::endl;
        Isle *isle = new Isle(isleName);
        mapTree.insert(isle);
        shaper->loseEnergy();
        std::cout << "[Craft] " << shaper->getName() << " crafted new Isle " << isleName << std::endl;
    }
    else
    {
        std::cout << "[Energy] " << shaper->getName() << " does not have enough energy points: " << shaper->getEnergyLevel() << std::endl;
    }
}

void GameWorld::displayGameState()
{
    // mapTree.displayMap();
    // shaperTree.displayTree();
}

// TODO: Implement functions to read and parse Access and Duel logs
std::vector<std::pair<std::string, std::string>> GameWorld::readAccessLogs(const std::string &accessLogs)
{
    std::vector<std::pair<std::string, std::string>> logs;
    std::ifstream file(accessLogs);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string player, isle;
        ss >> player >> isle;
        logs.push_back({player, isle});
    }
    return logs;
}

std::vector<std::pair<std::string, std::string>> GameWorld::readDuelLogs(const std::string &duelLogs)
{
    std::vector<std::pair<std::string, std::string>> logs;
    std::ifstream file(duelLogs);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string player1, player2;
        ss >> player1 >> player2;
        logs.push_back({player1, player2});
    }
    return logs;
}

void GameWorld::processGameEvents(const std::string &accessLogs, const std::string &duelLogs)
{
    // TODO:
    // Read logs
    // For every 5 access, 1 duel happens
    // If there are still duel logs left after every access happens duels happens one after other

    // This function should call exploreArea and craft functions

    // Use displayGameState();
    std::vector<std::pair<std::string, std::string>> access = readAccessLogs(accessLogs);
    std::vector<std::pair<std::string, std::string>> duel = readDuelLogs(duelLogs);
    size_t duelIndex = 0;
    for (size_t i = 0; i < access.size(); i++)
    {
        if (mapTree.findIsle(access[i].second))
        {
            exploreArea(shaperTree.findPlayer(access[i].first), mapTree.findIsle(access[i].second));
        }
        else
        {
            craft(shaperTree.findPlayer(access[i].first), access[i].second);
        }
        if ((i + 1) % 5 == 0 && duelIndex < duel.size() && i != 0)
        {
            bool result = true ? duel[duelIndex].second == "1" : false;
            shaperTree.duel(shaperTree.findPlayer(duel[duelIndex].first), result);
            duelIndex++;
        }
    }

    while (duelIndex < duel.size())
    {
        bool result = (duel[duelIndex].second == "1");
        auto player = shaperTree.findPlayer(duel[duelIndex].first);

        if (player)
        {
            shaperTree.duel(player, result);
        }
        duelIndex++;
    }

    displayGameState();
}

void GameWorld::saveGameState(const std::string &currentIsles, const std::string &currentWorld, const std::string &currentShapers, const std::string &currentPlayerTree)
{
    mapTree.writeIslesToFile(currentIsles);
    mapTree.writeToFile(currentWorld);
    shaperTree.writeToFile(currentPlayerTree);
    shaperTree.writeShapersToFile(currentShapers);
}
