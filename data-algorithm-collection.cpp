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
//  --- 4.キュー (自作) ---
// ノードの定義
struct Node {
    int data;
    Node* next;
};
struct MyQueue {
    Node* front = nullptr; // 先頭（取り出し口）
    Node* rear = nullptr;  // 末尾（入り口）

    // データを入れる (Enqueue)
    void enqueue(int val) {
        Node* newNode = new Node{val, nullptr};
        if (rear == nullptr) {
            // キューが空の場合
            front = rear = newNode;
        } else {
            // 末尾に追加して、末尾ポインタを更新
            rear->next = newNode;
            rear = newNode;
        }
        std::cout << val << " をエンキューしました。\n";
    }

    // データを取り出す (Dequeue)
    int dequeue() {
        if (front == nullptr) {
            std::cout << "エラー: キューが空です。\n";
            return -1;
        }
        
        Node* temp = front;
        int val = temp->data;
        front = front->next;

        // 最後の一つを取り出した場合、rearもnullptrにする
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp; // メモリ解放
        return val;
    }

    // 中身の確認
    void display() {
        Node* curr = front;
        std::cout << "Queue: [ ";
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "]\n";
    }
};

// --- 5. 木構造 (二分探索木) ---
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

// --- 6. ハノイの塔 ---
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

    std::cout << "--- 4: Queue ---\n";
    MyQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();

    std::cout << "デキュー: " << q.dequeue() << "\n";
    q.display();
    
    std::cout << "--- 5: Tree (In-order) ---\n";
    TreeNode* root = nullptr;
    root = insertTree(root, 50);
    insertTree(root, 30);
    insertTree(root, 70);
    inOrder(root);
    std::cout << "\n\n";

    std::cout << "--- 6: Regular Expression (std::regex) ---\n";
    //正規表現
    std::string email = "user@example.com";
    std::regex pattern(R"([a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,})");
    if (std::regex_match(email, pattern)) {
        std::cout << email << " は有効なメール形式です。\n\n";
    }

    std::cout << "--- 7: Hanoi (3 Disks) ---\n";
    hanoi(3, 'A', 'C', 'B');

    return 0;
}
