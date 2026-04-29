#include <iostream>
#include <vector>
#include <string>
#include <regex> // 正規表現用

// --- 1. ソート (クイックソート) ---
void quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++; j--;
        }
    }
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

// --- 2. 探索 (二分探索) ---
int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// --- 3. スタック (自作) ---
struct StackNode {
    int data;
    StackNode* next;
};
struct MyStack {
    StackNode* topNode = nullptr;
    void push(int val) { topNode = new StackNode{val, topNode}; }
    int pop() {
        if (!topNode) return -1;
        int val = topNode->data;
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
        return val;
    }
};

// --- 4. 木構造 (二分探索木) ---
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode* insertTree(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertTree(root->left, val);
    else root->right = insertTree(root->right, val);
    return root;
}
void inOrder(TreeNode* root) {
    if (!root) return;
    inOrder(root->left);
    std::cout << root->val << " ";
    inOrder(root->right);
}

// --- 5. ハノイの塔 ---
void hanoi(int n, char from, char to, char work) {
    if (n == 0) return;
    hanoi(n - 1, from, work, to);
    std::cout << "円盤" << n << ": " << from << " -> " << to << "\n";
    hanoi(n - 1, work, to, from);
}

// ==========================================
// メイン関数
// ==========================================
int main() {
    std::cout << "--- 1 & 2: Sort & Search ---\n";
    int nums[] = {34, 7, 23, 32, 5, 62};
    int n = sizeof(nums) / sizeof(nums[0]);
    quickSort(nums, 0, n - 1);
    std::cout << "Sorted: ";
    for(int x : nums) std::cout << x << " ";
    std::cout << "\nSearch 23: Index " << binarySearch(nums, n, 23) << "\n\n";

    std::cout << "--- 3: Stack ---\n";
    MyStack s;
    s.push(10); s.push(20);
    std::cout << "Popped: " << s.pop() << "\n\n";

    std::cout << "--- 4: Tree (In-order) ---\n";
    TreeNode* root = nullptr;
    root = insertTree(root, 50);
    insertTree(root, 30);
    insertTree(root, 70);
    inOrder(root);
    std::cout << "\n\n";

    std::cout << "--- 5: Regular Expression (std::regex) ---\n";
    std::string email = "user@example.com";
    std::regex pattern(R"([a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,})");
    if (std::regex_match(email, pattern)) {
        std::cout << email << " は有効なメール形式です。\n\n";
    }

    std::cout << "--- 6: Hanoi (3 Disks) ---\n";
    hanoi(3, 'A', 'C', 'B');

    return 0;
}
