
#include <QApplication>
#include <QDebug>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;
/*
 * 1:快速排序
 * 2：Top-K
 * 3：字符频次排序
 * 4: 最小的K个数
 * 5：合并k个链表
 * 6：单调栈
 * 7：双端队列
 * 8:DFS\
 * ：接雨水？
 * ：动态规划-矩阵  回溯法
 * ：凸包
 * ：路径规划
*/


//--------快速排序1-----------

void printnums(vector<int>& nums){
   for(auto d : nums)
       std::cout << d <<" ";
    std::cout << std::endl;
}
void Quick_sort(vector<int>& nums,int l,int r){
    if(l + 1 >= r)
        return;
    int first = l;
    int last = r-1;
    int key = nums[first];
    while(first < last){
        while(first < last && nums[last]>=key)
            last--;
        nums[first] = nums[last];
        //printnums(nums);

        while(first < last && nums[first]<=key)
            first++;
        nums[last] = nums[first];
        //printnums(nums);
    }
    nums[first] = key;
    std::cout << "-----" << std::endl;
    //printnums(nums);

    Quick_sort(nums,l,first-1);
    Quick_sort(nums,first+1,r);
}

void testQuick_sort()
{
    vector<int> vDatas = {3,4,7,2,1,9,15,12};
    Quick_sort(vDatas,0,8);
    for(auto i : vDatas)
        qDebug() << i;
}
//--------快速排序2-----------
int partition(vector<int>& nums,int l,int r){
    if(l == r)
        return l;
    int first = l;
    int last = r;
    int key = nums[first];
    while(first < last){
        while(first < last && nums[last]>=key)
            last--;
        nums[first] = nums[last];
        //printnums(nums);

        while(first < last && nums[first]<=key)
            first++;
        nums[last] = nums[first];
        //printnums(nums);
    }
    nums[first] = key;
    return first;
}

void quick_sort(vector<int>& nums,int l,int r)
{
    if(l >= r)
        return;
    int index = partition( nums,l,r);
    quick_sort(nums,l,index-1);
    quick_sort(nums,index+1,r);
}

//--------TopK-------------O(n)
vector<int> find_most_frequent_K_nums(vector<int> vData,int K){
    std::unordered_map<int,int> key_count;
    int maxCount = 0;
    for(auto i : vData){
        maxCount = std::max(maxCount, ++key_count[i]);
    }
    vector<int> vEmpty{};
    vector<vector<int>> temp(maxCount,vEmpty);
    for(auto item : key_count){
        cout << item.second << " - " << item.first << endl;
        temp[item.second-1].push_back(item.first);
    }
    vector<int> result;
    for(int i = temp.size()-1;i >= 0;i--){
        if(temp[i].size()==0) continue;
        for(int j = 0;j<temp[i].size() && result.size()< K;j++)
            result.push_back(temp[i][j]);
        if(result.size()==K)
            return result;
    }
    return result;
}

static bool compare(pair<char,int> a,pair<char,int> b){
    return a.second > b.second;
}
//字符频次排序
vector<char> sort_char_by_frequent(const vector<char>& data) {
    unordered_map<char,int> map_count;
    for(auto c : data) {
        map_count[c]++;
    }
    std::vector<pair<char,int>> datas;
    for(auto pair : map_count)
        datas.push_back(pair);

    std::sort(datas.begin(),datas.end(),compare);
}
//桶排序O（n）的方式字符频次排序
//sort无法对map进排序，只能放vector中
vector<char> sort_char_by_frequent_V2(const vector<char>& data) {
    int max_count = 0;
    unordered_map<char,int> map_count;
    for(auto c : data) {
        map_count[c]++;
        max_count = std::max(max_count,map_count[c]);
    }
    vector<vector<char>> all_datas(max_count,vector<char>());
    for(auto pair : map_count){
        all_datas[pair.second].push_back(pair.first);
    }
    return vector<char>();
}

//最小的K个数    
//思路分析：快排，找前K个，或者partition只找到k即可
void get_min_k_numbers(const vector<int>& datas,int K){
    //排序 std::sort
    //mutilset<int,greater<int>>  begin()最大
    multiset<int,greater<int>> muiti_set;
    for(auto data : datas){
        if(muiti_set.size() < K)
            muiti_set.insert(data);
        else {
            auto itor = muiti_set.begin();
            if(*itor > data) {
                muiti_set.erase(itor);
                muiti_set.insert(data);
            }
        }
    }

    for(auto it : muiti_set)
        cout << it << endl;
}


void get_min_k_numbers_V2(const vector<int>& datas,int K){
    //默认从小到大排列
    multiset<int> muiti_set;
    for(auto data : datas){
        if(muiti_set.size() < K)
            muiti_set.insert(data);
        else {
            auto itor_last = --muiti_set.end();
            if(*itor_last > data) {
                muiti_set.erase(itor_last);
                muiti_set.insert(data);
            }
        }
    }
    cout << endl;
    for(auto it : muiti_set)
        cout << it << endl;
    cout << endl;
}


void get_min_k_numbers_V3(const vector<int>& datas,int K){
    //默认从小到大排列
    multiset<int> muiti_set;
    for(auto data : datas){
        if(muiti_set.size() < K)
            muiti_set.insert(data);
        else {
            std::multiset<int>::reverse_iterator itor_last = muiti_set.rbegin();
            if(*itor_last > data) {
                muiti_set.erase(*itor_last);
                muiti_set.insert(data);
            }
        }
    }
    cout << endl;
    for(auto it : muiti_set)
        cout << it << endl;
    cout << endl;
}


//---mergeKList---------------
//
struct Node {
    Node* next_;
    int data_;
    Node(int data){
        data_ = data;
        next_ = nullptr;
    }
};

//!! 最大的关键是要建立一个结构体！operator()
struct cmp{
    bool operator()(Node* f1,Node* f2){
        return f1->data_ > f2->data_;
    }
};

Node* createNode(const vector<int>& vdata){
    Node* first = nullptr,*current = nullptr;
    for(auto n : vdata){
        if(first == nullptr){
            first = new Node(n);
            current = first;
        } else {
            current->next_ = new Node(n);
            current = current->next_;
        }
    }
    return first;
}
// 5：合并k个链表
Node* mergeKList(const vector<Node*>& vecNode) {
    Node* first = nullptr,*current = nullptr;
    priority_queue<Node*,vector<Node*>,cmp>  priority_queue;
    //initial queue;
    for(auto node : vecNode)
        if(node!=nullptr)
            priority_queue.push(node);

    while (priority_queue.size()>0){
        Node* top_node =  priority_queue.top();
        priority_queue.pop();
        if(top_node==nullptr)
            continue;
        if(first == nullptr){
            first = new Node(top_node->data_);
            current = first;
        } else {
            current->next_ = new Node(top_node->data_);
            current = current->next_ ;
        }
            
        if(top_node->next_!=nullptr)
            priority_queue.push(top_node->next_);
    }
    return first;
}

// 6：单调栈
// 温度的数组，计算每一天距离升温间隔多少天
void getDailyTemperture(vector<int> vData){
    vector<int> results(vData.size(),0);
    stack<int> indices;
    for(int i = 0; i < vData.size(); ++i){  
        while (indices.size() > 0){ 
            int top = indices.top();
            if(vData[top]<vData[i]){
                results[top] = i - top;
                indices.pop();
            } else {
                break;
            }
        }
        indices.push(i);
    }
    //{73,74,75,71,69,72,76,73};
    while (indices.size()>0){   
        int nIndex = indices.top();
        results[nIndex] = 0;
        indices.pop();
    }
    for(auto n : results)
        std::cout << n << std::endl;
}



// 7：双端队列

// DFS

//--------main()-----------
int main(int argc, char *argv[])
{
    //quick_sort
    if(0){
        vector<int> vDatas = {3,4,7,2,1,9,15,12};
        quick_sort(vDatas,0,7);
        printnums(vDatas);

        vector<int> vDatas2 = {3,4,7,2,1,9,15,12};
        Quick_sort(vDatas2,0,8);
        printnums(vDatas2);
    }
    if(0){
        vector<int> vDatas3 = {1,7,1,5,1,4,3,2,1,9,3,2,15,12};
        vector<int> result = find_most_frequent_K_nums(vDatas3,4);
        printnums(result);
    }

    if(0){
        vector<int> vDatas3 = {1,7,1,5,1,4,3,2,1,9,3,2,15,12};
        get_min_k_numbers(vDatas3,5);
        get_min_k_numbers_V2(vDatas3,5);
    }
    if(0){
           // 5：合并k个链表
        vector<int> v1{3,8,9};
        vector<int> v2{1,6,7,12};
        vector<int> v3{0,4,5,10};
        Node* node1 = createNode(v1);
        Node* node2 = createNode(v2);
        Node* node3 = createNode(v3);
        vector<Node*> vecNode;
        vecNode.push_back(node1);
        vecNode.push_back(node2);
        vecNode.push_back(node3);
        Node*  result = mergeKList(vecNode);
        while (result!=nullptr)
        {
            cout << result->data_ << endl;
            result = result->next_;
        }
    }

    vector<int> vDatas = {73,74,75,71,69,72,76,73};
    getDailyTemperture(vDatas);
}


/*
void swapVec(vector<int>& vData,int i1, int i2)
{
    int temp = vData[i1];
    vData[i1] = vData[i2];
    vData[i2] = temp;
}

int partion(vector<int>& vData,int l,int r)
{
    if(l == r)
        return l;
    //int mid = (l + r)/2;
    int target = vData[l];

    while(l < r) {
        while(target <= vData[r] && l < r)
            r--;
        while(target >= vData[l] && l < r)
            l++;

        if(r == l)
        {
            vData[l] = target;
            return l;
        }
        swapVec(vData,l,r);
    }
}
void quickSort(vector<int>& vDatas,int l,int r)
{
    if(l==r)
        return;
    int index = partion(vDatas,l,r);
    quickSort(vDatas,l,index);
    quickSort(vDatas,index,r);
}
*/



//#include<iostream>
//using namespace std;

//void QuickSort(int arr[], int left, int right)
//{
//    int l = left;// 左下标
//    int r = right;// 右下标
//    int pivot = arr[(left + right) / 2];// 找到中间的值

//    // 将比pivot小的值放在其左边，比pivot大的值放在其右边
//    while (l < r){
//        // 在pivot左边寻找，直至找到大于等于pivot的值才退出
//        while (arr[l] < pivot){
//            l += 1;// 将l右移一位
//        }

//        // 在pivot右边寻找，直至找到小于等于pivot的值才退出
//        while (arr[r] > pivot){
//            r -= 1;// 将r左移一位
//        }

//        if (l >= r){
//            // 左右下标重合，寻找完毕，退出循环
//            break;
//        }

//        // 交换元素
//        int temp = arr[l];
//        arr[l] = arr[r];
//        arr[r] = temp;

//        // 如果交换完后，发现arr[l]==pivot，此时应将r左移一位
//        if (arr[l] == pivot){
//            r -= 1;
//        }
//        // 如果交换完后，发现arr[r]==pivot，此时应将l右移一位
//        if (arr[r] == pivot){
//            l += 1;
//        }
//    }

//    // 如果l==r，要把这两个下标错开，否则会出现无限递归，导致栈溢出的情况
//    if (l == r){
//        l += 1;
//        r -= 1;
//    }

//    // 向左递归
//    if (left < r){
//        QuickSort(arr, left, r);
//    }

//    // 向右递归
//    if (right > l){
//        QuickSort(arr, l, right);
//    }
//}

//#include <QDebug>
//int main(int argc, char *argv[])
//{
//    int vDatas[8] = {3,4,7,2,1,9,12,15};
//    //vector<int> vDatas{3,4,7,2,1,9,12,15};
//    QuickSort(vDatas,0,7);
//    for(auto i : vDatas)
//        qDebug() << i;

////    QApplication a(argc, argv);
////    Dialog w;
////    w.show();

////    return a.exec();
//}
