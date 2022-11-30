#include<stdio.h>
#include<stdlib.h>
struct bst
{
    int data;
    struct bst * left;
    struct bst * right;
};
void inorder(struct bst * root){
    if (root ==NULL)
        return;
    inorder(root->left);
    printf("%d\t",root->data);
    inorder(root->right);
}
void preorder(struct bst * root){
    if (root ==NULL)
        return;
    printf("%d\t",root->data);
    preorder(root->left);
    preorder(root->right);
}
void postorder(struct bst * root){
    if (root ==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d\t",root->data);
}
void insert(int e,struct bst * root){
    if(root==NULL){
        struct bst * new=(struct bst *)malloc(sizeof(struct bst));
        new->data=e;
        root->right=NULL;
        root->left=NULL;
        root=new;
    }
    else if(root->data<e)
        insert(e,root->right);
    else if(root->data>e)
        insert(e,root->left);
}
struct bst * Fmin(struct bst * root){
    while (root&&root->left !=NULL)
    {
        root=root->left;
    }
    return root;
}
struct bst * delete(struct bst * root,int k){
    if(root==NULL)
        return;
    else if (root->data<k)
        delete(root->right,k);
    else if (root->data>k)
        delete(root->left,k);
    else{
        if(root->left==NULL){
            struct bst*temp=root;
            root=root->right;
            free(temp);
        }
        else if (root->right==NULL){
            struct bst*temp=root;
            root=root->left;
            free(temp);
        }
        struct bst* temp=Fmin(root->right);
        root->data=temp->data;
        root->right=delete(root->right,temp->data);
    }
    return root;
}
struct node* createTree(struct node * root){
    char k;
    if(k=='\n'){
        return;
    }
    else{
        insert(root,(int) k);
        createTree(root);
    }
}
void main(){

}