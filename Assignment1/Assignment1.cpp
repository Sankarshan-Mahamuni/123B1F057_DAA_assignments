#include<iostream>
#include<vector>
#include<chrono>
using namespace std;


class CustomerOrder{
    public:
    string orderId;
    long long timestamp;
    // Default constructor required for containers that default-initialize elements
    CustomerOrder(): orderId(""), timestamp(0) {}

    CustomerOrder(string id, long long time): orderId(id),timestamp(time){}

};

// Merge tow sorted halves
void merge(vector<CustomerOrder> & arr, int left,int mid, int right){
    int n1= mid -left +1;
    int n2= right -mid;
    vector<CustomerOrder> leftArr(n1);
    vector<CustomerOrder> rightArr(n2);
    for (int i=0;i<n1;i++)
        leftArr[i]=arr[left+i];
    for (int j=0;j<n2;j++){
        rightArr[j] =arr[mid+1+j];
    }

    int i=0,j=0,k=left;
    while (i<n1 && j<n2 ){
        if (leftArr[i].timestamp <= rightArr[j].timestamp)
            arr[k++]=leftArr[i++];
        else
            arr[k++]=rightArr[j++];
    }
    while (i<n1) arr[k++] = leftArr[i++];
    while (j<n2) arr[k++] = rightArr[j++];
}


// Mergesort 
void mergeSort ( vector<CustomerOrder> &orders,int left,int right){
    if (orders.empty()) return;
    if (left<right){
        int mid = left + (right -left) / 2;
        mergeSort(orders,left,mid);
        mergeSort(orders,mid+1,right);
        merge(orders,left,mid,right);
    }
}


vector<CustomerOrder> sampleData(){
    return {
        {"O01", 1700000100000LL},
        {"O02", 1699999999000LL},
        {"O03", 1700000200000LL},
        {"O04", 1699999950000LL},
        {"O05", 1700000300000LL},
        {"O06", 1700000000000LL},
        {"O07", 1699999900000LL},
        {"O08", 1700000500000LL},
        {"O09", 1699999850000LL},
        {"O10", 1700000400000LL},
        {"O11", 1700000000000LL}
    };
}

int main(){
    vector<CustomerOrder> orders = sampleData();
    cout << " ------------------- cutomer orders ---------------\n\n";
    for (const auto & c:orders)
        cout<< "Order id :"<< c.orderId << " |Timestamps :"<<c.timestamp << endl;

    auto start = chrono::high_resolution_clock::now();
mergeSort(orders, 0, orders.size() - 1);
auto end = chrono::high_resolution_clock::now();
chrono::duration<double, milli> timeTaken = end - start;

cout << "\n ------------------- sorted orders ---------------\n\n";
for (const auto & c : orders)
    cout << "Order id :" << c.orderId << " | Timestamps :" << c.timestamp << endl;

cout << "\nTime Taken: " << timeTaken.count() << " ms\n";
    return 0;

}