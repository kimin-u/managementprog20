#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	char english[20];
	char korean[20];
	char form[20];
	int check;
	struct node* next;
} node_t;

void menu();
node_t*  add(node_t* list_head,node_t*(*func)(node_t*,char*));
void print_list(node_t* list_head);
node_t* search_eng(node_t* list_head, char* english);
void sub(node_t** list_head, node_t*(*func)(node_t* , char*));
void changecheck(node_t* list_head, node_t*(*func)(node_t*,char*));
void printchecklist(node_t* list_head);
void printsearch(node_t* list_head, node_t*(*func)(node_t*,char*));
void printform(node_t* list_head);
void savefile(node_t* list_head);
void openfile(node_t** list_head);

int main(void)
{
	node_t* list_head=NULL;
	int select;

remenu:
	while (1){
		menu();
		printf("기능을 선택하세요 : ");
		scanf("%d",&select);
		if (select>=10 || select<0){
			printf("잘못 입력하셨습니다.\n");
			goto remenu;
		}
		switch (select){
			case 0:
				openfile(&list_head);
				break;
			case 1:
				list_head = add(list_head,search_eng);
				break;
			case 2:
				sub(&list_head,search_eng);
				break;
			case 3:
				print_list(list_head);
				break;
			case 4:
				changecheck(list_head, search_eng);
				break;
			case 5:
				printchecklist(list_head);
				break;
			case 6:
				printsearch(list_head, search_eng);
				break;
			case 7:
				printform(list_head);
				break;
			case 8:
				savefile(list_head);
				break;
			case 9:
				printf("단어장을 종료합니다.\n");
				return 0;
		}
	}
}

void menu()
{
	printf("============\n");
	printf("0. 단어장 불러오기\n");
	printf("1. 단어 추가\n");
	printf("2. 단어 삭제\n");
	printf("3. 저장된 단어들 출력\n");
	printf("4. 단어 체크표시 여부를 바꾸기\n");
	printf("5. 체크표시된 단어 출력\n");
	printf("6. 단어 검색\n");
	printf("7. 품사별 출력\n");
	printf("8. 단어장에 저장\n");
	printf("9. 종료\n");
	printf("===========\n");
	return;
}

node_t* add(node_t* list_head, node_t*(*func)(node_t*,char*))
{
	node_t* new_node;
	node_t* tmp;
	char eng[20];
	char kor[20];
	char pom[20];
	int chk;
	printf("영어 입력 : ");
	scanf("%s",eng);
	
	tmp=func(list_head,eng);
	if (tmp!=NULL){
		printf("이미 존재합니다.\n");
		return list_head;
	}
	else{
		printf("뜻 입력 : ");
		scanf("%s",kor);
		printf("품사 입력 : ");
		scanf("%s",pom);
		printf("체크표시 여부(0 or 1) : ");
		scanf("%d",&chk);
	}
	new_node = (node_t*) malloc (sizeof(node_t));
	strcpy(new_node->english,eng);
	strcpy(new_node->korean,kor);
	strcpy(new_node->form,pom);
	new_node->check = chk;

	new_node->next = list_head;
	list_head = new_node;
	return list_head;
}

void print_list(node_t* list_head)
{
	while (list_head != NULL){
		printf("%s - ", list_head -> english);
		printf("%s : ", list_head -> korean);
		printf("%d\n", list_head -> check);
		list_head = list_head ->next;
	}
}

node_t* search_eng(node_t* list_head,char* eng)
{
	while(list_head != NULL){
		if (strcmp(list_head->english, eng) == 0)
			return list_head;
		list_head = list_head ->next;
	}
	return list_head;
}

void sub(node_t** list_head, node_t*(*func)(node_t*,char*))
{
	node_t* prev=NULL;
	node_t* seek = *list_head;
	node_t* tmp;
	char eng[20];
	printf("삭제하고 싶은 영단어 : ");
	scanf("%s", eng);
	
	tmp=func(*list_head,eng);
	
	if (tmp == NULL){
		printf("존재하지 않는 단어입니다.\n");
		return;
	}

	if ((*list_head) == tmp){
		(*list_head) = tmp->next;
		free(seek);
		printf("삭제 완료\n");
		return;
	}
	while (seek){
		if(seek==tmp){
			prev->next= seek->next;
			free(seek);
			printf("삭제 완료\n");
			return;
		}
		prev=seek;
		seek= seek->next;
	}
}


void changecheck(node_t* list_head, node_t*(*func)(node_t*, char*))
{
	node_t* tmp;
	char eng[20];
	printf("체크표시를 바꿀 영단어 : ");
	scanf("%s",eng);

	tmp=func(list_head,eng);

	if (tmp->check == 0){
		printf("%s 체크표시를 하겠습니다.\n", eng);
		tmp->check =1;
	}	
	else {
		printf("%s 체크표시를 지우겠습니다.\n",eng);
		tmp->check =0;
	}
}

void printchecklist(node_t* list_head)
{
	printf("체크표시한 단어들의 리스트입니다.\n");
	while(list_head!=NULL){
		if (list_head->check==1){
			printf("%s - ",list_head->english);
			printf("%s\n",list_head->korean);
		}
		list_head=list_head->next;
	}
}

void printsearch(node_t* list_head, node_t*(*func)(node_t*,char*))
{
	node_t* tmp;
	char eng[20];
	printf("뜻을 알고싶은 영단어 입력 : ");
	scanf("%s", eng); 
	 
	tmp=func(list_head,eng);
	printf("%s - ",tmp->english);
	printf("%s - ",tmp->korean);
	printf("%s\n",tmp->form);
	
	int choice;
qst:
	if (tmp->check ==0){
		printf("체크표시 하겠습니까? (예 : 1, 아니오 : 0 입력) : ");
		scanf("%d",&choice);
	}
	else
		return;

	if (choice ==0)
		return;
	else if (choice ==1){
		if(tmp->check ==0){
			printf("체크표시 했습니다.\n");
			tmp->check =1;
			return;
		}
		else{
			printf("이미 체크표시되어 있습니다.\n");
			return;
		}
	}
	else{
		printf("잘못 입력하셨습니다.\n");
		goto qst;
	}
}
void printform(node_t* list_head)
{
	char fom[20];
	node_t* tmp= list_head;
	printf("출력하고 싶은 품사 : ");
	scanf("%s",fom);
	printf("--%s--\n",fom);
	while (tmp!=NULL){
		if (strcmp(tmp->form,fom)==0){
			printf("%s - ",tmp->english);
			printf("%s\n",tmp->korean);
		}
		tmp = tmp->next;
	}
}

void savefile(node_t* list_head)
{
	node_t* tmp;
	FILE* fp= fopen("dictionary.txt", "w+");
	while(list_head!=NULL){
		tmp=list_head;
		fprintf(fp,"%s %s %s %d\n",tmp->english,tmp->korean,tmp->form,tmp->check);
		list_head=list_head->next;
		free(tmp);
	}
	fclose(fp);
	printf("저장을 완료했습니다.\n");
}

void openfile(node_t** list_head)
{
	node_t* new_node;
	FILE* fp = fopen("dictionary.txt","r+");
	if (fp==NULL){
		printf("파일을 열 수 없습니다.\n");
		return ;
	}
	while(1){
		new_node = (node_t*) malloc (sizeof(node_t));
		if (feof(fp)!=0)
			break;
		fscanf(fp,"%s %s %s %d\n",new_node->english,new_node->korean, new_node->form, &new_node->check);
		new_node->next=*list_head;
		*list_head=new_node;
	}
	fclose(fp);
	printf("파일을 불러왔습니다.\n");
}
