/*
 * 代码说明
 * 代码由 筱锋xiao_lfeng 编写
 * 其开发者由此互联网ICP备案作者编写：粤ICP备2022014822号
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MaxSize 100

typedef char ElemType;
typedef struct Node {
    ElemType data;
    struct Node* lchild, * rchild;
} TreeNode;

void CreateBTree(TreeNode *& bt,const char* str) {
    TreeNode * St[MaxSize], * p = nullptr;
    int j = 0, k, top = -1;
    char ch;
    bt = nullptr;
    while ((ch = str[j]) != '\0') {
        switch (ch) {
            case '(':
                top++;
                St[top] = p;
                k = 1;
                break;
            case ')':
                top--;
                break;
            case ',':
                k = 2;
                break;
            default:
                p = (TreeNode*)malloc(sizeof(TreeNode));
                p->data = ch;
                p->lchild = p->rchild = nullptr;
                if (bt == nullptr) bt = p;
                else {
                    switch (k) {
                        case 1:
                            St[top]->lchild = p;
                            break;
                        case 2:
                            St[top]->rchild = p;
                            break;
                    }
                }
        }
        j++;
    }
}

int BTHeight(TreeNode* bt) {
    if (bt == nullptr)
        return 0;
    int h1 = BTHeight(bt->lchild);
    int h2 = BTHeight(bt->rchild);
    return (h1 > h2) ? (h1 + 1) : (h2 + 1);
}

int NodeCount(TreeNode* bt) {
    if (bt == nullptr)
        return 0;
    int n1 = NodeCount(bt->lchild);
    int n2 = NodeCount(bt->rchild);
    return 1 + n1 + n2;
}

int LeafCount(TreeNode* bt) {
    if (bt == nullptr)
        return 0;
    if (bt->lchild == nullptr && bt->rchild == nullptr)
        return 1;
    int a = LeafCount(bt->lchild);
    int b = LeafCount(bt->rchild);
    return a + b;
}

// 退出前销毁二叉树
void DestroyBTree(TreeNode*& bt) {
    if (bt != nullptr) {
        DestroyBTree(bt->lchild);
        DestroyBTree(bt->rchild);
        free(bt);
        bt = nullptr;
    }
}


void PreOrder(TreeNode* bt) {
    if (bt != nullptr) {
        printf("%c", bt->data);
        PreOrder(bt->lchild);
        PreOrder(bt->rchild);
    }
}

void InOrder(TreeNode* bt) {
    if (bt != nullptr) {
        InOrder(bt->lchild);
        printf("%c", bt->data);
        InOrder(bt->rchild);
    }
}

void PostOrder(TreeNode* bt) {
    if (bt != nullptr) {
        PostOrder(bt->lchild);
        PostOrder(bt->rchild);
        printf("%c", bt->data);
    }
}

int main() {
    TreeNode* bt;
    char str[100];
    printf("请输入建立二叉链表的序列：\n");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  // 去除fgets读取的换行符
    CreateBTree(bt, str);
    printf("bt的先序遍历:");
    PreOrder(bt);
    printf("\n");
    printf("bt的中序遍历:");
    InOrder(bt);
    printf("\n");
    printf("bt的后序遍历:");
    PostOrder(bt);
    printf("\n");
    printf("bt的高度:%d\n", BTHeight(bt));
    printf("bt的结点数:%d\n", NodeCount(bt));
    printf("bt的叶子结点数:%d\n", LeafCount(bt));
    DestroyBTree(bt);
    system("pause");
    return 0;
}
