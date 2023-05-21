/*
 * ����˵��
 * ������ ���xiao_lfeng ��д
 * �俪�����ɴ˻�����ICP�������߱�д����ICP��2022014822��
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

// �˳�ǰ���ٶ�����
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
    printf("�����뽨��������������У�\n");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  // ȥ��fgets��ȡ�Ļ��з�
    CreateBTree(bt, str);
    printf("bt���������:");
    PreOrder(bt);
    printf("\n");
    printf("bt���������:");
    InOrder(bt);
    printf("\n");
    printf("bt�ĺ������:");
    PostOrder(bt);
    printf("\n");
    printf("bt�ĸ߶�:%d\n", BTHeight(bt));
    printf("bt�Ľ����:%d\n", NodeCount(bt));
    printf("bt��Ҷ�ӽ����:%d\n", LeafCount(bt));
    DestroyBTree(bt);
    system("pause");
    return 0;
}
