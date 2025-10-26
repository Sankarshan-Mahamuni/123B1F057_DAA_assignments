#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

class Item {
public:
    string name;
    int weight;
    int utility;
    bool perishable;

    Item(string n, int w, int u, bool p)
        : name(n), weight(w), utility(u), perishable(p) {}
};


class ReliefTruckOptimizer {
private:
    int capacity;                       // Maximum weight truck can carry
    vector<Item> items;                 // All available items
    vector<vector<int>> dp;             // DP table for 0/1 Knapsack

public:
    ReliefTruckOptimizer(int W, const vector<Item>& itemsList)
        : capacity(W), items(itemsList) {
        dp.assign(items.size() + 1, vector<int>(W + 1, 0));
    }

    // Sort items: prioritize perishable items, then by utility/weight ratio
    void sortItems() {
        sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
            if (a.perishable != b.perishable)
                return a.perishable > b.perishable; // perishable first
            double ratioA = (double)a.utility / a.weight;
            double ratioB = (double)b.utility / b.weight;
            return ratioA > ratioB;
        });
    }

    void computeOptimalSelection() {
        int N = items.size();
        for (int i = 1; i <= N; ++i) {
            for (int w = 0; w <= capacity; ++w) {
                if (items[i - 1].weight <= w) {
                    dp[i][w] = max(dp[i - 1][w],
                                   dp[i - 1][w - items[i - 1].weight] + items[i - 1].utility);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
    }

    vector<int> getChosenItems() {
        int w = capacity;
        vector<int> chosen;
        for (int i = items.size(); i >= 1; --i) {
            if (dp[i][w] != dp[i - 1][w]) {
                chosen.push_back(i - 1);
                w -= items[i - 1].weight;
            }
        }
        return chosen;
    }

    // Display final result
    void displayResult() {
        int N = items.size();
        computeOptimalSelection();
        vector<int> chosen = getChosenItems();

        cout << "\n========== RELIEF TRUCK OPTIMIZATION ==========\n";
        cout << "Truck Capacity: " << capacity << " kg\n";
        cout << "------------------------------------------------\n";
        cout << left << setw(15) << "Item" 
             << setw(10) << "Weight"
             << setw(10) << "Utility"
             << setw(12) << "Perishable" << "\n";
        cout << "------------------------------------------------\n";
        for (const auto& it : items) {
            cout << left << setw(15) << it.name
                 << setw(10) << it.weight
                 << setw(10) << it.utility
                 << setw(12) << (it.perishable ? "Yes" : "No") << "\n";
        }

        cout << "\n--- Selected Items ---\n";
        int totalWt = 0;
        for (int idx : chosen) {
            cout << "  • " << items[idx].name << " (Wt: " << items[idx].weight
                 << "kg, Utility: " << items[idx].utility
                 << (items[idx].perishable ? ", Perishable" : "") << ")\n";
            totalWt += items[idx].weight;
        }

        cout << "\nTotal Weight Loaded: " << totalWt << " kg\n";
        cout << "Maximum Utility Achieved: " << dp[N][capacity] << "\n";
        cout << "===============================================\n";
    }
};


int main() {
    int capacity = 50;
    vector<Item> items = {
        {"Medicine", 10, 60, true},
        {"Food", 20, 100, true},
        {"Blankets", 30, 120, false},
        {"Water", 15, 50, true},
        {"Tents", 25, 80, false}
    };

    ReliefTruckOptimizer optimizer(capacity, items);
    optimizer.sortItems();
    optimizer.displayResult();

    return 0;
}
