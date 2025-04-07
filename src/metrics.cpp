#include "methods.h"

int getMax(std::vector<Item>& items, const std::string& attribute) {
    int maxValue = 0;

    if (attribute == "age") {
        for (const auto& item : items) {
            if (item.age > maxValue) {
                maxValue = item.age;
            }
        }
    } else if (attribute == "type") {
        for (const auto& item : items) {
            if (item.type > maxValue) {
                maxValue = item.type;
            }
        }
    } else if (attribute == "origin") {
        for (const auto& item : items) {
            if (item.origin > maxValue) {
                maxValue = item.origin;
            }
        }
    } else {
        std::cerr << "Invalid attribute: " << attribute << ". Supported attributes are: age, type, origin." << std::endl;
    }

    return maxValue;
}

// min = age - ageWindow
// max = age + ageWindow
// rarityScore = (1 - probability) * (1 + item.age/ageMax)
void calculateRarityScores(std::vector<Item>& items, int ageWindow) {
    if (items.empty()) {
        std::cerr << "The items vector is empty. Cannot calculate rarity scores." << std::endl;
        return;
    }

    // Determine the maximum age (first in descending, last in ascending)
    int maxAge = items.front().age > items.back().age ? items.front().age : items.back().age;

    // Iterate through the items
    for (size_t i = 0; i < items.size(); ++i) {
        int ageMin = items[i].age - ageWindow;
        int ageMax = items[i].age + ageWindow;

        // Find left boundary
        size_t left = i;
        while (left > 0 && items[left - 1].age <= ageMax && items[left - 1].age >= ageMin) {
            --left;
        }

        // Find right boundary
        size_t right = i;
        while (right < items.size() - 1 && items[right + 1].age <= ageMax && items[right + 1].age >= ageMin) {
            ++right;
        }

        // Count total and similar items in the window [left, right]
        int countTotal = right - left + 1; // Includes the current item
        int countSimilar = 0;

        for (size_t j = left; j <= right; ++j) {
            if (items[j].type == items[i].type && items[j].origin == items[i].origin) {
                countSimilar++; // Include the current item in countSimilar
            }
        }

        // Calculate probability P
        double probability = (countTotal > 1) ? static_cast<double>(countSimilar) / countTotal : 0.0;

        // Calculate the rarity score R using the formula
        items[i].rarityScore = (1 - probability) * (1 + static_cast<double>(items[i].age) / maxAge);
    }
}





