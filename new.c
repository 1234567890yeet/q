#include<stdio.h>
#include<stdlib.h>
typedef struct link{
	struct link* right;
	struct link* left;
	int data;
} link;
void insert(link*root,int d){
	if(root==NULL){
		link*node=(link*)malloc(sizeof(link));
		node->right=NULL
		node->left=NULL;
		node->data=d;
		root=node;
	}
	else if(d<root->data){
		insert(root->right,d);
	}
	else{
		insert(root->right,d);
	}
}
void create(link*root){
	int n,d;
	printf("Enter number of elements: ");
	scanf("%d",&n);
	while(n--){
		printf("Enter the nummber to insert ");
		scanf("%d",&d);
		insert(root,d);
	}
}
void print(link*root){
	if(root==NULL){
		printf("wertyui");
		return;
	}
	printf("wertyui");
	printf("%d ,",root->data);
	printf("wertyui");
	print(root->right);
	printf("wertyui");
	print(root->left);
}
void main(){
	link*head=NULL;
	printf("%d",head);
	create(head);
	printf("%d",head);
	insert(head,5);
	printf("%d",head);
	print(head);	
}