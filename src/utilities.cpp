#include "methods.h"

std::vector<Item> readItemsFromFile(const std::string& filename) 
{
    std::vector<Item> items;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return items;
    }

    std::string line;
    // Skip the header if it exists
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Item item;
        std::string temp;

        // Parse the CSV line
        if (std::getline(ss, temp, ',')) item.age = std::stoi(temp);
        if (std::getline(ss, temp, ',')) item.type = std::stoi(temp);
        if (std::getline(ss, temp, ',')) item.origin = std::stoi(temp);
        if (std::getline(ss, temp, ',')) item.rarityScore = std::stod(temp);

        items.push_back(item);
    }

    file.close();
    return items;
}

void writeItemsToFile(const std::string& filename, const std::vector<Item>& items) 
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    // Write header
    file << "Age,Type,Origin,RarityScore\n";

    // Write data
    for (const auto& item : items) {
        file << item.age << ","
             << item.type << ","
             << item.origin << ","
             << item.rarityScore << "\n";
    }

    file.close();
}
