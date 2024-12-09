#include "Map.h"

Map::Map()
{
    this->root = nullptr;
}
Map::~Map()
{
    // TODO: Free any dynamically allocated memory if necessary
    MapNode *current = root;
    std::queue<MapNode *> q;
    q.push(current);
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
        delete current;
    }
    root = nullptr;
}

void Map::initializeMap(std::vector<Isle *> isles)
{
    // TODO: Insert innitial isles to the tree
    // Then populate with Goldium and Einstainium items
    for (Isle *isle : isles)
    {
        this->insert(isle);
    }
    for (Isle *isle : isles)
    {
        delete isle;
    }
}

MapNode *Map::rotateRight(MapNode *current)
{
    // TODO: Perform right rotation according to AVL
    // return necessary new root
    // Use std::cerr << "[Right Rotation] " << "Called on invalid node!" << std::endl;
    if (current == nullptr || current->left == nullptr)
    {
        std::cerr << "[Right Rotation] " << "Called on invalid node!" << std::endl;
    }

    MapNode *temp = current->left;
    current->left = temp->right;
    temp->right = current;

    current->height = 1 + std::max(height(current->left), height(current->right));
    temp->height = 1 + std::max(height(temp->left), height(temp->right));

    return temp;
}

MapNode *Map::rotateLeft(MapNode *current)
{
    // TODO: Perform left rotation according to AVL
    // return necessary new root
    // Use std::cerr << "[Left Rotation] " << "Called on invalid node!" << std::endl;
    if (current == nullptr || current->right == nullptr)
    {
        std::cerr << "[Left Rotation] " << "Called on invalid node!" << std::endl;
    }

    MapNode *temp = current->right;
    current->right = temp->left;
    temp->left = current;

    current->height = 1 + std::max(height(current->left), height(current->right));
    temp->height = 1 + std::max(height(temp->left), height(temp->right));

    return temp;
}

int calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{
    return (int)totalMapDepth * ((double)playerDepth / totalShaperTreeHeight);
}

int Map::height(MapNode *node)
{
    // TODO: Return height of the node
    return node == nullptr ? 0 : node->height;
}

MapNode *Map::insert(MapNode *node, Isle *isle)
{
    // MapNode *newNode = nullptr;

    // TODO: Recursively insert isle to the tree
    // returns inserted node
    if (node == nullptr)
    {
        return new MapNode(isle);
    }
    if (isle->getName() < node->isle->getName())
    {
        node->left = insert(node->left, isle);
    }
    else if (isle->getName() > node->isle->getName())
    {
        node->right = insert(node->right, isle);
    }
    else
    {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = height(node->left) - height(node->right);
    if (balance > 1 && isle->getName() < node->left->isle->getName())
    {
        return rotateRight(node);
    }
    if (balance < -1 && isle->getName() > node->right->isle->getName())
    {
        return rotateLeft(node);
    }
    if (balance > 1 && isle->getName() > node->left->isle->getName())
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && isle->getName() < node->right->isle->getName())
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Map::insert(Isle *isle)
{
    root = insert((root), isle);

    // you might need to insert some checks / functions here depending on your implementation
}

MapNode *Map::remove(MapNode *node, Isle *isle)
{
    // TODO: Recursively delete isle from the tree
    // Will be called if there is overcrowding
    // returns node
    // Use std::cout << "[Remove] " << "Tree is Empty" << std::endl;

    return node;
}

void Map::remove(Isle *isle)
{
    root = remove((root), isle);
    // you might need to insert some checks / functions here depending on your implementation
}

void Map::preOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop EINSTEINIUM according to rules
    // Use std::cout << "[Item Drop] " << "EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
}

// to Display the values by Post Order Method .. left - right - node
void Map::postOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop GOLDIUM according to rules
    // Use  std::cout << "[Item Drop] " << "GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
}

MapNode *Map::findFirstEmptyIsle(MapNode *node)
{
    // TODO: Find first Isle with no item
    return nullptr;
}

void Map::dropItemBFS()
{
    // TODO: Drop AMAZONITE according to rules
    // Use std::cout << "[BFS Drop] " << "AMAZONITE dropped on Isle: " << targetNode->isle->getName() << std::endl;
    // Use std::cout << "[BFS Drop] " << "No eligible Isle found for AMAZONITE drop." << std::endl;
}

void Map::displayMap()
{
    std::cout << "[World Map]" << std::endl;
    display(root, 0, 0);
}

int Map::getDepth(MapNode *node)
{
    // TODO: Return node depth if found, else
    MapNode *current = root;
    std::queue<MapNode *> q;
    q.push(current);
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
        if (current->isle->getName() == node->isle->getName())
        {
            return current->height;
        }
    }
    return -1;
}

// Function to calculate the depth of a specific node in the AVL tree
int Map::getIsleDepth(Isle *isle)
{
    // TODO: Return node depth by isle if found, else
    MapNode *current = root;
    std::queue<MapNode *> q;
    q.push(current);
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
        if (current->isle->getName() == isle->getName())
        {
            return current->height;
        }
    }
    return -1;
}

int Map::getDepth()
{
    // TODO: Return max|total depth of tree
    return getDepth(root);
}

void Map::populateWithItems()
{
    // TODO: Distribute fist GOLDIUM than EINSTEINIUM
}

Isle *Map::findIsle(Isle isle)
{
    // TODO: Find isle by value
    return nullptr;
}

Isle *Map::findIsle(std::string name)
{
    // TODO: Find isle by name
    MapNode *current = root;
    std::queue<MapNode *> q;
    q.push(current);
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
        if (current->isle->getName() == name)
        {
            return current->isle;
        }
    }
    return nullptr;
}

MapNode *Map::findNode(Isle isle)
{
    // TODO: Find node by value
    return nullptr;
}

MapNode *Map::findNode(std::string name)
{
    // TODO: Find node by name
    MapNode *current = root;
    std::queue<MapNode *> q;
    q.push(current);
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
        if (current->isle->getName() == name)
        {
            return current;
        }
    }
    return nullptr;
}

void Map::display(MapNode *current, int depth, int state)
{
    // SOURCE:

    if (current->left)
        display(current->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("   ┌───");
    else if (state == 2) // right
        printf("   └───");

    std::cout << "[" << *current->isle << "] - (" << current->height << ")\n"
              << std::endl;

    if (current->right)
        display(current->right, depth + 1, 2);
}

void Map::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output level by level
}

void Map::writeIslesToFile(const std::string &filename)
{
    // TODO: Write Isles to output file in alphabetical order
    // Use std::cout << "[Output] " << "Isles have been written to " << filename << " in in alphabetical order." << std::endl;
}
