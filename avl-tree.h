
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
// An AVL tree node 
struct AVL 
{ 
    char website[100]; 
    char ip[100];
    struct AVL *left; 
    struct AVL *right; 
    int height; 
}; 
  
// A utility function to get maximum of two integers 
int max(int a, int b); 
  
// A utility function to get the height of the tree 
int height(struct AVL *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct AVL* AVLTreenewNode(char website[100],char ip[100]) 
{ 
    struct AVL* node = (struct AVL*) 
                        malloc(sizeof(struct AVL)); 
    strcpy(node->website,website); 
    strcpy(node->ip,ip);
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct AVL *rightRotate(struct AVL *y) 
{ 
    struct AVL *x = y->left; 
    struct AVL *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct AVL *leftRotate(struct AVL *x) 
{ 
    struct AVL *y = x->right; 
    struct AVL *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(struct AVL *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct AVL* insert_page_AVL(struct AVL* node, char website[100],char id[100]) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(AVLTreenewNode(website,id)); 
  
    if (website < node->website) 
        node->left  = insert_page_AVL(node->left, website,id); 
    else if (website > node->website) 
        node->right = insert_page_AVL(node->right, website,id); 
    else // Equal keys are not allowed in BST 
        ;
		//return node;
		 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && website < node->left->website) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && website > node->right->website) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && website > node->left->website) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && website < node->right->website) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
  
// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void AVLprint(struct AVL *root) 
{ 
    if(root != NULL) 
    { 
        printf("%s > %s\n", root->website,root->ip); 
        AVLprint(root->left); 
        AVLprint(root->right); 
    } 
}
char *search_url_AVL(struct AVL* page, char* pageName)
{
    char *i;

    if (page != NULL)
    {
        i = search_url_AVL(page->left, pageName);
        if( !strcmp( page->website, pageName ) )
            return page->ip;
        if( i ) return i;

        i = search_url_AVL(page->right, pageName);
        if( i ) return i;
    }
    return NULL;
}

char *search_ip_AVL(struct AVL* page, char* ip)
{
    char *i;

    if (page != NULL)
    {
        i = search_ip_AVL(page->left, ip);
        if( !strcmp( page->ip, ip ) )
            return page->website;
        if( i ) return i;

        i = search_ip_AVL(page->right, ip);
        if( i ) return i;
    }
    return NULL;
}
