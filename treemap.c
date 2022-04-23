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
    TreeNode *aux=node;
    while (tree!=NULL)
    {
        if(aux->left==NULL && aux->right==NULL){
            if(is_equal(tree, aux->parent->left->pair->key, aux->pair->key)){ 
                aux->parent->left=NULL;
                tree->current=aux->parent;
                return;
            }
            else{
                 aux->parent->right=NULL;
                 tree->current=aux->parent;
                 return;
            }
            
        }    
        else if(aux->left==NULL || aux->right==NULL)
        {
            if (aux->left==NULL)
            {
                if(is_equal(tree, aux->parent->right->pair->key, aux->pair->key)) aux->parent->right=aux->right;
                else aux->parent->left=aux->right;
                aux->right->parent=aux->parent;
                tree->current=aux->right;
                return;
            }
            else{
                if(is_equal(tree, aux->parent->right->pair->key, aux->pair->key)) aux->parent->right=aux->left;
                else aux->parent->left=aux->left;
                aux->left->parent=aux->parent;
                tree->current=aux->left;
                return;
            }
            
        }
        else{
            aux=minimum(aux->right);
            node->left=aux->left;
            node->pair= aux->pair;
            node->parent=aux->parent;
            node->right= aux->right;
            removeNode(tree, aux);
            tree->current=node;
            return;
        }

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
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
