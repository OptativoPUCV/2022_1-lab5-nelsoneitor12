#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
   TreeMap *new=(TreeMap*) malloc(sizeof(TreeNode));
    new->root=NULL;
    new->current=NULL;
    new->lower_than=lower_than;
    return new;
}


void insertTreeMap(TreeMap * trklee, void* key, void * value) {
    TreeNode *aux= trklee->root;
    TreeNode *nodo=createTreeNode (key, value);
    if(searchTreeMap(trklee, key)==NULL){
        while (aux!=NULL)
        {
            if(trklee->lower_than(aux->pair->key, key)){
                if(aux->right==NULL)
                {
                    aux->right=nodo;
                    nodo->parent=aux;
                    trklee->current=nodo;
                    return;
                }
                else{
                    trklee->current=aux->right;
                    aux=trklee->current;
                }
            
            }
            else
            {
                 if(aux->left==NULL)
                {
                    aux->left=nodo;
                    nodo->parent=aux;
                    trklee->current=nodo;
                    return;
                }
                else{
                    trklee->current=aux->left;
                    aux=trklee->current;
                }
            
            }
        }
    }
}

TreeNode * minimum(TreeNode * x){
    TreeNode *aux=x;
    while(aux!=NULL){
        if(aux->left==NULL) return aux;
        aux=aux->left;
    }
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    //TreeMap *aux=node;
    if(node->right==NULL && node->left==NULL){
        if (node->parent->left==node) node->parent->left=NULL;
        else node->parent->right=NULL;
        tree->current=node->parent;
    }else if(node->right==NULL){
        if (node->parent->left==node) node->parent->left=node->left;
        else node->parent->right=node->left;
        node->left->parent=node->parent;
        tree->current=node->left;
    }
    else if(node->left==NULL){
        if (node->parent->left==node) node->parent->left=node->right;
        else node->parent->right=node->right;
        node->right->parent=node->parent;
        tree->current=node->right;
    }
    else{
        TreeNode *aux=minimum(node->right);
        node->pair=aux->pair;
        removeNode(tree,aux);
        tree->current=node;
    }
    
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
   TreeNode *aux = tree->root;
   while (aux != NULL)
    {
        if(tree->lower_than(key, aux->pair->key)==1)
        {
            aux = aux->left;
        }
        else if(tree->lower_than(aux->pair->key, key))
        {
            aux = aux->right; 
        }
        else{
            tree->current=aux;
            return aux->pair;
        }
    }

    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    while (tree!=NULL)
    {
        tree->current=minimum(tree->root);
        return tree->current->pair;
    }
    
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    while (tree!=NULL && tree->current!=NULL)
    {
        if(tree->current->right!=NULL){   
            TreeNode *aux=minimum(tree->current->right);
            printf("%d\n" ,aux->pair);
            return aux->pair;
        }
        else{
            while (tree->current!=NULL)
            {
                TreeNode *aux=tree->current->parent;
                if(tree->lower_than(tree->current->pair->key, aux->pair->key)){
                    return aux->pair;
                }
                else aux=aux->parent;
            }
            
        }
        return NULL;
    }
    return NULL;
}
