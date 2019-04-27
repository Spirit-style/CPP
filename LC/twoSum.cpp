#include <stdio.h>
#include <vector>
using namespace std;
// 给定 nums = [2, 7, 11, 15], target = 9

// 因为 nums[0] + nums[1] = 2 + 7 = 9
// 所以返回 [0, 1]
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector[int] a(2);
        int i,j;
        for( i=0;i<nums.size;++i){
            for( j=0;j<nums.size;++j){
                if(j!=i&&nums[i]+nums[j]==target){
                    a[0]=i;
                    a[1]=j;
                    break;
                }
            }
            if(a[0]!=0){
                break;
            }
        }
        return a;
    }
    }
};