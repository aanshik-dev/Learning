#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}node ;

node *createNode(int data){
    node *p=(node *)malloc(sizeof(node));
    p->left=NULL;
    p->right=NULL;
    p->data=data;
    return p;
}

void insert(node **root,int data){
    node *p=createNode(data);
    if(*root==NULL){
        *root=p;
        return;
    }
    node *queue[100];
    int front=0;
    int rare=0;
    queue[rare++]=*root;
    while(front < rare){
        node *temp=queue[front++];
        if(temp->left==NULL){
            temp->left=p;
            return;
        }
        else{
            queue[rare++]=temp->left;
        }

        if(temp->right==NULL){
            temp->right=p;
            return;
        }
        else{
            queue[rare++]=temp->right;
        }
    }
}
int n=0;

void heaping(int arr[],int n,int i){
    int smallest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n && arr[left]<arr[smallest]){
        smallest=left;
    }
    if(right<n && arr[right]<arr[smallest]){
        smallest=right;
    }
    if(smallest!=i){
        int t=arr[smallest];
        arr[smallest]=arr[i];
        arr[i]=t;

        heaping(arr,n,smallest);
    }
}
void min_heap(int arr[],int n){
    for(int i=n/2-1;i>=0;i--){
        heaping(arr,n,i);
    }
}
void delete(int arr[]){
    n=n-1;
    arr[0]=arr[n];
    heaping(arr,n,0);
}
void traverse(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
} 
void inOrder_traversal(node *root){
    if(root!=NULL){
        inOrder_traversal(root->left);
        printf("%d ",root->data);
        inOrder_traversal(root->right);
    }
}
int main(){
    int arr[100];
    node *root=NULL;
    while(1){
        int opt;
        printf("\nENTER :\n\t\t 1) TO INSERT\n\t\t  2) GET_MIN\n\t\t  3) EXTRACT_MIN \n\t\t4) level traversal \n\t\t5) inorder_traversal \n\t\t6) to exit\n");
        scanf("%d",&opt);

        if(opt==1){
            printf("enter data to insert :");
            scanf("%d",&arr[n]);
            n++;
            min_heap(arr,n);

            root=NULL;
            for(int i=0;i<n;i++){
                insert(&root,arr[i]);
            }

            printf("\nafter insertion :");
            traverse(arr,n);
        }
        else if(opt==2){
            printf("minimum is : %d",arr[0]);
        }
        else if(opt==3){
            delete(arr);
            printf("\nafter deletion :");

            root=NULL;
            for(int i=0;i<n;i++){
                insert(&root,arr[i]);
            }

            traverse(arr,n);
        }
        else if(opt==4){
            printf("\nLevel traversal :");
            traverse(arr,n);
        }
        else if(opt==5){
            printf("\ninOrder traversal :");
            inOrder_traversal(root);
        }
        else if(opt==6){
            printf("thank you !! ");
            break;
        }
        else{
            printf("\nwrong input !!\n");
        }
    }

 return 0;
}