//Muhammed Didin 2243384
// I need 100 for AA :)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include"Project_lib/bst.h"
#include"Project_Lib/avltree.h"
struct BST *read_ip_data_BST(struct BST *,char *);
struct AVL *read_ip_data_AVL(struct AVL *,char *);
int print_menu();
//main that menages the program
int main(){
	char filename[20],search_url[100],*founded;
	int selection = 0;
	double time_spent = 0.0;
	time_t startavl,startbst,endavl,endbst;
	clock_t begin,end;
	printf("Enter the filename: ");
	scanf("%s",filename);
	fflush(stdin);
	while(selection != 8){
		struct AVL *avl = NULL;
		struct BST *bst = NULL;
		
		bst = read_ip_data_BST(bst,filename);
		avl = read_ip_data_AVL(avl,filename);
		selection = print_menu();
		fflush(stdin);
		switch(selection){
			case 1:
				AVLprint(avl);
				break;
			case 2:
				BSTprint(bst);
				break;
			case 3:
				printf("Please enter the page: ");//You need to write the full URL
				scanf("%s",search_url);
				founded = search_url_AVL(avl,search_url);
				if(founded == NULL ){
					printf("Could not founded!\n");
				}
				else{
					printf("IP adresses for %s: %s",search_url,founded);
				}
				break;
			case 4:
				printf("Please enter the page: ");
				scanf("%s",search_url);
				founded = search_url_BST(bst,search_url);
				if(founded == NULL){
					printf("Could not founded!\n");
				}
				else{
					printf("IP adresses for %s: %s",search_url,founded);
				}
				break;
			case 5:
				printf("Please enter the IP: ");
				scanf("%s",search_url);
				founded = search_ip_AVL(avl,search_url);
				if(founded){
					printf("URL adresses for %s: %s",search_url,founded);
				}
				else{
					printf("Could not Founded!\n");
				}
				break;
			case 6:
				printf("Enter the IP: ");
				scanf("%s",search_url);
				founded = search_ip_BST(bst,search_url);
				if(founded){
					printf("URL adresses for %s: %s",search_url,founded);
				}
				else{
					printf("Could not founded!\n");
				}
				
				break;
			case 7:
//Dear hocam, these methods below are actually working. But you will see 0.00 in the output
//It is just because functions work too fast and program cannot count. 
				begin = clock();
				avl = read_ip_data_AVL(avl,filename);
				end = clock();
				time_spent = (double)(end - begin)*1000.0 / CLOCKS_PER_SEC;
				printf("Run time of AVL tree read ip function: %.2lf",time_spent);
				
				begin = clock();
				bst = read_ip_data_BST(bst,filename);
				end = clock();
				time_spent = (double)(end - begin)*1000.0 / CLOCKS_PER_SEC;
				printf("\nRun time of BST tree read ip function: %.2lf",time_spent);
				
				begin = clock();
				founded = search_ip_AVL(avl,search_url);
				end = clock();
				time_spent = (double)(end - begin)*1000.0 / CLOCKS_PER_SEC;
				printf("\nRun time of AVL tree search function: %.2lf",time_spent);
				
				begin = clock();
				founded = search_ip_BST(bst,search_url);
				end = clock();
				time_spent = (double)(end - begin)*1000.0 / CLOCKS_PER_SEC;
				printf("\nRun time of BST tree search function: %.2lf",time_spent);
				break;
			case 8:
				printf("GoodBye!\n");
				exit(0);
				break;
			default:
				printf("Wrong choose!\n");
			
		}
	
	}

	return 0;
}
//Function that read data from file to BST Tree
struct BST *read_ip_data_BST(struct BST *bst,char filename[20]){
	FILE *file;
	file=fopen(filename,"r+");
	char website[100];
	char ip[100];

	if(file == NULL){
		printf("File operation error!\n");
	}
	else{
		while(!feof(file)){
			fscanf(file,"%s",website);
			fscanf(file," > ");
			fscanf(file,"%s",ip);
			fscanf(file,"\n");
			bst = insert_page_BST(bst,website,ip);
			}
		fclose(file);
		return bst;
	}
}
//function that reads data from file to AVL Tree
struct AVL *read_ip_data_AVL(struct AVL *avl,char filename[20]){
	FILE *file;
	file=fopen("URL.txt","r");
	char website[100];
	char ip[100];

	if(file == NULL){
		printf("File operation error!\n");
	}
	else{
		while(!feof(file)){
			fscanf(file,"%s",website);
			fscanf(file," > ");
			fscanf(file,"%s",ip);
			fscanf(file,"\n");
			avl = insert_page_AVL(avl,website,ip);
			}
		fclose(file);
		return avl;
	}
}
//Function that prints menu
int print_menu(){
	int selection;
	printf("\nIndexing Websites\n");
	printf("--------MENU--------\n");
	printf("1) Display the full index in AVL Tree\n");
	printf("2) Display the full index in BST Tree\n");
	printf("3) Search for a URL From AVL Tree\n");
	printf("4) Search for a URL From BST Tree\n");
	printf("5) Search for an IP Adresses From AVL Tree\n");
	printf("6) Search for an IP Adresses From BST Tree\n");
	printf("7) Comparison of Run Time\n");
	printf("8) Exit\nYour Selection: ");
	scanf("%d",&selection);
	fflush(stdin);
	return selection;
}
