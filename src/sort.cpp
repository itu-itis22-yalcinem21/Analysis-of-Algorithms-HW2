#include "methods.h"

std::vector<Item> countingSort(std::vector<Item>& items, const std::string& attribute, bool ascending) {
    // Determine the range based on the attribute
    int maxValue = 0;

    if (attribute == "age") {
        maxValue = getMax(items, "age");
    } else if (attribute == "type") {
        maxValue = getMax(items, "type");
    } else if (attribute == "origin") {
        maxValue = getMax(items, "origin");
    } else {
        std::cerr << "Counting sort currently supports sorting by 'age', 'type', or 'origin' only." << std::endl;
        return items;
    }

    // Create count array and output array
    std::vector<int> count(maxValue + 1, 0);
    std::vector<Item> output(items.size());

    // Count occurrences of the attribute's value
    for (const auto& item : items) {
        if (attribute == "age") {
            count[item.age]++;
        } else if (attribute == "type") {
            count[item.type]++;
        } else if (attribute == "origin") {
            count[item.origin]++;
        }
    }

    // Update count array for sorting order
    if (ascending) { // Ascending order
        for (size_t i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }
    } else { // Descending order
        for (int i = count.size() - 2; i >= 0; --i) {
            count[i] += count[i + 1];
        }
    }

    // Build the output array
    for (int i = items.size() - 1; i >= 0; --i) {
        const Item& item = items[i];
        int key = (attribute == "age") ? item.age : (attribute == "type") ? item.type : item.origin;

        output[count[key] - 1] = item;
        count[key]--;
    }

    return output;
}


// Function to heapify a subtree rooted with node i in the array of items
void heapify(std::vector<Item>& items, int n, int i, bool descending) {
    int root = i;             // Initialize root
    int left = 2 * i + 1;     // Left child index
    int right = 2 * i + 2;    // Right child index

    // Compare left child with root
    if (left < n &&
        ((descending && items[left].rarityScore < items[root].rarityScore) ||
         (!descending && items[left].rarityScore > items[root].rarityScore))) {
        root = left;
    }

    // Compare right child with the current root
    if (right < n &&
        ((descending && items[right].rarityScore < items[root].rarityScore) ||
         (!descending && items[right].rarityScore > items[root].rarityScore))) {
        root = right;
    }

    // If the root is not the largest (or smallest), swap and continue heapifying
    if (root != i) {
        std::swap(items[i], items[root]);
        heapify(items, n, root, descending);
    }
}




// Function to perform heap sort on rarityScore scores of items
std::vector<Item> heapSortByRarity(std::vector<Item>& items, bool descending) {
    int n = items.size();

    // Build the heap (min-heap for descending, max-heap for ascending)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(items, n, i, descending);
    }

    // Extract elements from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move the current root (lowest/highest) to the end
        std::swap(items[0], items[i]);

        // Call heapify on the reduced heap
        heapify(items, i, 0, descending);
    }

    return items;
}



