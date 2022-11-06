/*
//二分查找
二分查找，只需求中间值，一点点逼近 left,right

-------旋转数组中查找一个数--------
旋转数组只有一部分数是排序的，能起到的作用是其中的一半,
核心是判断哪一半是正常排序的
1:若中间值小于尾巴数字，右侧是排序的;
2：若中间值大于尾巴数字，左侧是排序的;
若target落入排序的一侧，则用排序的二分查找
若target落入未完全排序的一侧，则逐步缩进left和right即可


具体实现的思考：旋转数组适合while循环，二分查找可用循环和递归
数组查找区间：left和right边界
while循环（left 小于 right）
 */

#include <vector>
using namespace  std;
class Solution {
public:
    bool binarySearch(const vector<int>& nums, int begin, int end, int target) {
        // assert(...);

        int l = begin, r = end;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                return true;
            }

            if (target < nums[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return false;
    }

    bool binarySearch_recursion(const vector<int>& nums, int l, int r, const int& target) {
        // assert(...);
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                return true;
            }
            if (target < nums[mid]) {
                return binarySearch_recursion(nums,l,mid,target);
            } else {
                return binarySearch_recursion(nums,mid,r,target);
            }
        }
        return false;
    }


    bool search(vector<int>& nums, int target) {
        int len = nums.size();

        if (nums.empty()) {
            return false;
        }

        int l = 0, r = len - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] == target) {
                return true;
            }

            if (nums[l] < nums[mid]) {
                if (nums[l] <= target && target <= nums[mid]) {
                    return binarySearch(nums, l, mid, target);
                } else {
                    l = mid + 1;
                }

            } else if (nums[mid] < nums[r]) {
                if (nums[mid] <= target && target <= nums[r]) {
                    return binarySearch(nums, mid, r, target);
                } else {
                    r = mid - 1;
                }

            } else if (nums[mid] == nums[l]) {
                l++;

            } else if (nums[mid] == nums[r]) {
                r--;

            }
        }

        return false;

    }
};
