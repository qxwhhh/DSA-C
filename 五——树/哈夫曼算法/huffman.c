#include <stdio.h>
#include <stdlib.h>

// 定义哈夫曼树的节点
typedef struct Node {
    char symbol; // 符号
    unsigned freq; // 频率
    struct Node *left, *right; // 左右子树指针
} Node;

// 定义最小堆的节点，用于构建哈夫曼树
typedef struct MinHeap {
    Node* nodes[100]; // 假设最多处理100个字符
    int size;
    int capacity;
} MinHeap;

// 定义哈希表的节点，用于存储字符与其编码的映射
typedef struct HashNode {
    char symbol;
    char* code;
    struct HashNode* next;
} HashNode;

// 定义哈希表
typedef struct HashTable {
    HashNode* nodes[256]; // 假设ASCII字符集
} HashTable;

Node* createNode(char symbol, unsigned freq) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->symbol = symbol;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void minHeapInit(MinHeap* heap) {
    heap->size = 0;
    heap->capacity = 100; // 假设最多100个字符
}

void minHeapInsert(MinHeap* heap, Node* node) {
    if (heap->size >= heap->capacity) return; // 堆已满

    // 从底部开始，将新节点插入到正确的位置
    int i = heap->size;
    heap->size++;
    heap->nodes[i] = node;

    // 上滤过程
    while (i != 0 && heap->nodes[i]->freq < heap->nodes[(i - 1) / 2]->freq) {
        swap(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node* minHeapExtractMin(MinHeap* heap) {
    if (heap->size <= 0) return NULL;

    Node* minNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];
    
    // 下滤过程
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int smallest = left;
        if (right < heap->size && heap->nodes[right]->freq < heap->nodes[left]->freq) {
            smallest = right;
        }
        if (heap->nodes[i]->freq < heap->nodes[smallest]->freq) {
            break;
        } else {
            swap(&heap->nodes[i], &heap->nodes[smallest]);
            i = smallest;
        }
    }

    return minNode;
}

Node* buildHuffmanTree(char* data, int dataSize) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeapInit(minHeap);

    // 计算每个字符的频率
    // ... (此处省略频率计算代码)

    // 使用频率构建最小堆
    // ... (此处省略构建最小堆的代码)

    // 构建哈夫曼树
    while (minHeap->size > 1) {
        Node* left = minHeapExtractMin(minHeap);
        Node* right = minHeapExtractMin(minHeap);
        Node* parent = createNode(' ', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        minHeapInsert(minHeap, parent);
    }

    Node* huffmanTreeRoot = minHeapExtractMin(minHeap);
    free(minHeap); // 释放最小堆内存
    return huffmanTreeRoot;
}

void assignCodes(Node* root, char* code, HashTable* table) {
    if (!root) return;
    if (root->left == NULL && root->right == NULL) {
        table->nodes[root->symbol] = (HashNode*)malloc(sizeof(HashNode));
        table->nodes[root->symbol]->symbol = root->symbol;
        table->nodes[root->symbol]->code = strdup(code);
        table->nodes[root->symbol]->next = NULL;
        return;
    }
    assignCodes(root->left, code + "0", table);
    assignCodes(root->right, code + "1", table);
}

void huffmanEncode(char* data, int dataSize, HashTable* table) {
    // 假设已经构建了哈夫曼树并分配了编码
    for (int i = 0; i < dataSize; i++) {
        printf("%s", table->nodes[(unsigned char)data[i]]->code);
    }
    printf("\n");
}

void huffmanDecode(char* encodedData, int encodedSize, Node* root) {
    Node* current = root;
    for (int i = 0; i < encodedSize; i++) {
        if (encodedData[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == NULL && current->right == NULL) {
            putchar(current->symbol);
            current = root;
        }
    }
    putchar('\n');
}

void userInterface() {
    char data[100];
    printf("Enter text for Huffman coding: ");
    fgets(data, 100, stdin);

    // 构建哈夫曼树并分配编码
    Node* root = buildHuffmanTree(data, strlen(data));

    // 构建哈希表
    HashTable table;
    for (int i = 0; i < 256; i++) {
        table.nodes[i] = NULL;
    }
    assignCodes(root, "", &table);

    // 编码
    printf("Encoded data: ");
    huffmanEncode(data, strlen(data), &table);

    // 解码
    char* encodedData = "编码后的二进制字符串";
    printf("Decoded data: ");
    huffmanDecode(encodedData, strlen(encodedData), root);

    // 清理内存
    free(root);
    for (int i = 0; i < 256; i++) {
        HashNode* node = table.nodes[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp->code);
            free(temp);
        }
    }
}

int main() {
    userInterface();
    return 0;
}
