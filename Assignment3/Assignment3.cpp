/*
Scenario: Emergency Relief Supply Distribution
A devastating flood has hit multiple villages in a remote area, and the government, along

with NGOs, is organizing an emergency relief operation. A rescue team has a limited-
capacity boat that can carry a maximum weight of W kilograms. The boat must transport

critical supplies, including food, medicine, and drinking water, from a relief center to the
affected villages.
Each type of relief item has:
● A weight (wi) in kilograms.
● Utility value (vi) indicating its importance (e.g., medicine has higher value than food).
● Some items can be divided into smaller portions (e.g., food and water), while others must
be taken as a whole (e.g., medical kits).
As the logistics manager, you must:
1. Implement the Fractional Knapsack algorithm to maximize the total utility value of the
supplies transported.
2. Prioritize high-value items while considering weight constraints.
3. Allow partial selection of divisible items (e.g., carrying a fraction of food packets).
4. Ensure that the boat carries the most critical supplies given its weight limit W.
*/



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

class Item {
    public:
    string name;
    double weight;
    double utility;
    bool divisible;
    Item(string n ,double w, double u, bool d)
        : name (n),weight(w),utility(u),divisible(d){}
    double utilityPerKg() const{
        return utility / weight ;
    }
};

int main(){
    int n ;
    cout<< " -- Emergency Relief supply Loading -- \n";
    cout<< " Enter the number of relief items:";
    cin>>n;
    cin.ignore(); // consume line 

    if (n<=0){
        cout<< "No items to load . Exiting  \n ";
        return 0;
    }

    vector<Item> items;
    for (int i=0;i<n;++i){
        cout<< "\n Item #"<<(i+1) << "\n";
        string name ;
        double weight ,utility;
        int divisibleFlag;
        cout<< "Name :";
        getline(cin,name);
        cout<< " Weight (kg) :";
        cin>>weight;
        if (weight<=0){
            cout<<"Invalid weight. Must be > 0. Exiting \n";
            return 0;
        }
        cout << "Utility Value: ";
        cin >> utility;
        if (utility < 0) {
            cout << "Invalid utility. Must be >= 0. Exiting.\n";
            return 0;
        }
        cout << "Divisible ? ( 1= yes ,0 = no)";
        cin>>divisibleFlag;
        cin.ignore();
        items.emplace_back(name,weight,utility,divisibleFlag ==1);
    }
    double capacity ;
    cout<<" Enter the boat capacity (kg) ";
    cin>> capacity;
    if (capacity<=0){
        cout<< "Boat capacity must be > 0 . Exiting . \n ";
        return 0;
    }
    auto start = chrono :: high_resolution_clock::now();
    // sort items by utility per kg in descending order 
    sort(items.begin(),items.end(),[](const Item &a,const Item&b){
        return a.utilityPerKg() > b.utilityPerKg();
    });

    double totalUtility=0;
    double remainingCapacity =capacity;
    cout<< "Items loaded on boat \n";
    for (const auto & item : items ){
        if (remainingCapacity<=0) break;
        if (item.divisible){
            double takenWeight  = min(item.weight,remainingCapacity);
            double takenUtility= item.utilityPerKg()* takenWeight;
            totalUtility += takenUtility;
            remainingCapacity-=takenWeight;
            printf( " -%s : %.2f kg, Utility: %.2f \n",item.name.c_str(),takenWeight,takenUtility);
        }else{
            if (item.weight<=remainingCapacity){
                totalUtility +=item.utility;
                remainingCapacity -= item.weight;
                printf("- %s: %.2f kg, Utility : %.2f \n",item.name.c_str(),item.weight,item.utility);
            }
        }
    }
    printf("\n Total utility carried : %.2f \n",totalUtility);
    auto end =chrono :: high_resolution_clock :: now();
    chrono :: duration<double, milli> timeTaken = end -start;
    printf("Execution time : %.3f ms \n",timeTaken.count()) ;
    return 0;



}

