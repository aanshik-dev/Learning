//heap sort 
#include <stdio.h>
#include <stdlib.h>
void heapify(int arr[],int n,int i){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n && arr[left]>arr[largest]){
        largest=left;
    }
    if(right<n && arr[right]>arr[largest]){
        largest=right;
    }
    if(largest!=i){
        int t=arr[largest];
        arr[largest]=arr[i];
        arr[i]=t;

        heapify(arr,n,largest);
    }

}
void heapsort(int arr[],int n){
    for(int i=n/2-1;i>=0;i--){
        heapify(arr,n,i);
    }
    for(int i=n-1;i>=0;i--){
        int t=arr[0];
        arr[0]=arr[i];
        arr[i]=t;
        heapify(arr,i,0);
    }
}

void traverse(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}   
int main(){
    int arr[]={12,31,41,2,11,14,78};
    int size=sizeof(arr)/sizeof(int);
    printf("\n BEORE :");
    traverse(arr,size);
    
    heapsort(arr,size);
    printf("\n AFTER :");
    traverse(arr,size);

 return 0;
}