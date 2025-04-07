#include "methods.h"
#include <chrono>

void measureSortingTime(const std::string& fileName, const std::string& sizeLabel) {
    std::cout << "Measuring sorting times for " << sizeLabel << " file: " << fileName << std::endl;

    // Read items from the file
    std::vector<Item> items = readItemsFromFile(fileName);
    if (items.empty()) {
        std::cerr << "Failed to read items from file: " << fileName << std::endl;
        return;
    }

    // Sort in ascending order and measure time
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Item> sortedAsc = countingSort(items, "age", true);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort in ascending order: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Measure time to sort an already sorted vector (ascending)
    start = std::chrono::high_resolution_clock::now();
    countingSort(sortedAsc, "age", true);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort an already sorted vector (ascending): "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Measure time to sort a reverse sorted vector (descending)
    auto reverseSorted = countingSort(sortedAsc, "age", false);
    start = std::chrono::high_resolution_clock::now();
    countingSort(reverseSorted, "age", true);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort a reverse sorted vector: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    std::cout << "-------------------------------------------" << std::endl;
}

void measureHeapSortTime(const std::string& fileName, const std::string& sizeLabel, int ageWindow) {
    std::cout << "Measuring heap sort times for " << sizeLabel << " file: " << fileName << std::endl;

    // Read items from the file
    std::vector<Item> items = readItemsFromFile(fileName);
    if (items.empty()) {
        std::cerr << "Failed to read items from file: " << fileName << std::endl;
        return;
    }

    // Calculate rarity scores
    std::vector<Item> itemsWithRarity = countingSort(items, "age", true); // Ensure items are sorted by age
    calculateRarityScores(itemsWithRarity, ageWindow);

    // Sort by rarity (ascending) and measure time
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Item> sortedAsc = heapSortByRarity(itemsWithRarity, true); // Ascending order
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort in ascending order: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Measure time to sort an already sorted vector (ascending)
    start = std::chrono::high_resolution_clock::now();
    heapSortByRarity(sortedAsc, true); // Ascending order
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort an already sorted vector (ascending): "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Measure time to sort a reverse sorted vector (descending)
    auto reverseSorted = heapSortByRarity(itemsWithRarity, false); // Descending order
    start = std::chrono::high_resolution_clock::now();
    heapSortByRarity(reverseSorted, true); // Sort back to ascending
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort a reverse sorted vector: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    std::cout << "-------------------------------------------" << std::endl;
}


int main() {
    std::string inputFile = "data/items_l.csv";

    // Start measuring total time
    auto totalStart = std::chrono::high_resolution_clock::now();

    // Step 1: Read items from file
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Item> items = readItemsFromFile(inputFile);
    auto end = std::chrono::high_resolution_clock::now();
    if (items.empty()) {
        std::cerr << "Failed to read items from file: " << inputFile << std::endl;
        return 1;
    }
    std::cout << "Time to read items from file: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Step 2: Sort items by age using counting sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<Item> sorted = countingSort(items, "age", true);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort items by age: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Step 3: Write sorted items to a file
    start = std::chrono::high_resolution_clock::now();
    writeItemsToFile("data/items_l_sorted.csv", sorted);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to write sorted items to file: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Step 4: Calculate rarity scores
    int ageWindow = 50;
    start = std::chrono::high_resolution_clock::now();
    calculateRarityScores(sorted, ageWindow);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to calculate rarity scores: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Step 5: Write items with rarity scores to a file
    start = std::chrono::high_resolution_clock::now();
    writeItemsToFile("data/items_l_rarity.csv", sorted);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to write items with rarity scores to file: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Step 6: Sort items by rarity scores using heap sort
    start = std::chrono::high_resolution_clock::now();
    sorted = heapSortByRarity(sorted, true);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to sort items by rarity scores: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // Step 7: Write rarity-sorted items to a file
    start = std::chrono::high_resolution_clock::now();
    writeItemsToFile("data/items_l_rarity_sorted.csv", sorted);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to write rarity-sorted items to file: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms" << std::endl;

    // End measuring total time
    auto totalEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Total execution time: "
              << std::chrono::duration<double, std::milli>(totalEnd - totalStart).count()
              << " ms" << std::endl;

    return 0;
}

