#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}node ;
node *createNode(int data){
    node *p=(node *)malloc(sizeof(node));
    p->data=data;
    p->left=NULL;
    p->right=NULL;
    return p;
}
node *insert(node *root,int data ){
    if(root==NULL){
        return createNode(data);
    }
    if(data>root->data){
        root->right=insert(root->right,data);
    }
    else if(data < root->data){
        root->left=insert(root->left,data);
    }
    return root;
}
void inOrder_traversal(node *root){
    if(root!=NULL){
        inOrder_traversal(root->left);
        printf("%d ",root->data);
        inOrder_traversal(root->right);
    }
}
int p=1;
int req;
int getkthlargest(node *root,int k){
    if(root!=NULL){
        getkthlargest(root->right,k);
        if(p==k){
            p++;
            req=root->data;
        }
        else{
            p++;
        }
        getkthlargest(root->left,k);
    }
    return req;
}
int main(){
    node *root=NULL;
    while(1){
        int opt;
        printf("\nenter\n\t\t 1) to insert\n\t\t 2) to print\n\t\t 3) to find kth largest element\n");
        scanf("%d",&opt);

        if(opt==1){
            int n;
            printf("enter data to insert :");
            scanf("%d",&n);

            root=insert(root,n);
        }
        else if(opt==2){
            printf("\ninorder traversal :");
            inOrder_traversal(root);
        }
        else if(opt==3){
            int k;
            printf("enter k to get kth largest element from binary tree :");
            scanf("%d",&k);
             int y=getkthlargest(root,k);
             req=0;
             p=1;
            printf("\n%d-th largest element from bianry tree is : %d",k,y);
        }
    }
 return 0;
}