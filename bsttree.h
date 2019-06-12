// C program to demonstrate insert operation in binary search tree 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
struct BST 
{ 
    char website[100];
	char ip[100]; 
    struct BST *left, *right; 
}; 
   
// A utility function to create a new BST node 
struct BST *BSTnewNode(char item[100],char ip[100]) 
{ 
    struct BST *temp =  (struct BST *)malloc(sizeof(struct BST)); 
    strcpy(temp->website,item); 
    strcpy(temp->ip,ip);
    temp->left = temp->right = NULL; 
    return temp; 
} 
   
// A utility function to do inorder traversal of BST 
void BSTprint(struct BST *root) 
{ 
    if (root != NULL) 
    { 
        BSTprint(root->left); 
        printf("%s > %s \n", root->website,root->ip); 
        BSTprint(root->right); 
    } 
} 
   
/* A utility function to insert a new node with given website in BST */
struct BST* insert_page_BST(struct BST* node, char website[100],char ip[100]) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return BSTnewNode(website,ip); 
  
    /* Otherwise, recur down the tree */
    if (website < node->website) 
        node->left  = insert_page_BST(node->left, website,ip); 
    else if (website > node->website) 
        node->right = insert_page_BST(node->right, website,ip);    
  
    /* return the (unchanged) node pointer */
    return node; 
}

char *search_url_BST(struct BST* page, char* pageName)
{
    char *i;

    if (page != NULL)
    {
        i = search_url_BST(page->left, pageName);
        if( !strcmp( page->website, pageName ) )
            return page->ip;
        if( i ) return i;

        i = search_url_BST(page->right, pageName);
        if( i ) return i;
    }
    return NULL;
}

char *search_ip_BST(struct BST* page, char* ip)
{
    char *i;

    if (page != NULL)
    {
        i = search_ip_BST(page->left, ip);
        if( !strcmp( page->ip, ip ) )
            return page->website;
        if( i ) return i;

        i = search_ip_BST(page->right, ip);
        if( i ) return i;
    }
    return NULL;
}
