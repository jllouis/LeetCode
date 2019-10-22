//
// Created by jlouis on 10/9/2019.
//

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class NumArray {
private:
    vector<int> nums;
public:
    NumArray(vector<int>& nums) {
        this->nums = vector<int>(nums.begin(), nums.end());
    }

    void update(int i, int val) {
        nums[i] = val;
    }

    int sumRange(int i, int j) {
        return accumulate(nums.begin()+i, nums.begin()+j+1, 0);
//    int sum = 0;
//    for (; i <= j; ++i)
//        sum += nums[i];
//
//    return sum;
    }
};

int main() {

    vector<int> list {0,1,2,3,4,5,6,7,8,9};
    auto myNumArray = NumArray(list);
    cout << "Sum[3,7]: " << myNumArray.sumRange(3, 7) << endl;
    cout << "Update(5,0)" << endl;
    myNumArray.update(5, 0);
    cout << "Sum[3,7]: " << myNumArray.sumRange(3, 7) << endl;
}