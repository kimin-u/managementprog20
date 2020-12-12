#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct node{
	char english[20];
	char korean[20];
	char form[20];
	int check;
	int wrongcount;
	struct node* next;
} node_t;

int cnt=0; 

void menu();
node_t*  add(node_t* list_head,node_t*(*func)(node_t*,char*));
void print_list(node_t* list_head);
void printwrong(node_t* list_head);
node_t* search_eng(node_t* list_head, char* english);
void sub(node_t** list_head, node_t*(*func)(node_t* , char*));
node_t* removeall(node_t* list_head);
void changecheck(node_t* list_head, node_t*(*func)(node_t*,char*));
void printchecklist(node_t* list_head);
void printsearch(node_t* list_head, node_t*(*func)(node_t*,char*));
void printform(node_t* list_head);
void savefile(node_t* list_head);
void openfile(node_t** list_head);
void minitest(node_t* list_head);
void retest(node_t* list_head);

int main(void)
{
	node_t* list_head=NULL;
	int select;

remenu:
	while (1){
		menu();
		printf("기능을 선택하세요 : ");
		scanf("%d",&select);
		if (select>13 || select<0){
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
				list_head = removeall(list_head);
				printf("전체 삭제 완료\n");
				break;
			case 4:
				print_list(list_head);
				break;
			case 5:
				printwrong(list_head);
				break;
			case 6:
				changecheck(list_head, search_eng);
				break;
			case 7:
				printchecklist(list_head);
				break;
			case 8:
				printsearch(list_head, search_eng);
				break;
			case 9:
				printform(list_head);
				break;
			case 10:
				minitest(list_head);
				break;
			case 11:
				retest(list_head);
				break;
			case 12:
				savefile(list_head);
				break;
			case 13:
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
	printf("3. 단어 모두 삭제\n");
	printf("4. 저장된 단어들 출력\n");
	printf("5. 틀린적 있는 단어들 출력\n");
	printf("6. 단어 체크표시 여부를 바꾸기\n");
	printf("7. 체크표시된 단어 출력\n");
	printf("8. 단어 검색\n");
	printf("9. 품사별 출력\n");
	printf("10. 미니테스트 시작\n");
	printf("11. 재시험 (틀린적 있는 단어만) \n");
	printf("12. 단어장에 저장\n");
	printf("13. 종료\n");
	printf("===========\n");
	return;
}

node_t* add(node_t* list_head, node_t*(*func)(node_t*,char*))
{
	node_t* new_node;
	node_t* tmp;
	node_t* prev=NULL;
	node_t* seek=list_head;;
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
	new_node->wrongcount = 0;
	while (seek!=NULL){
		if (strcmp(seek->english,new_node->english)>0)
			break;
		prev=seek;
		seek = seek->next;
	}
	new_node->next = seek;
	if (prev!=NULL)
		prev-> next = new_node;
	else 
		list_head = new_node;
	cnt++;
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
void printwrong(node_t* list_head)
{
	while (list_head != NULL){
		if (list_head->wrongcount>=1){
			printf("%s - ", list_head-> english);
			printf("%s ", list_head -> korean);
			printf("(틀린 횟수 : %d)\n",list_head->wrongcount);
		}
		list_head = list_head -> next;
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
		cnt--;
		return;
	}
	while (seek){
		if(seek==tmp){
			prev->next= seek->next;
			free(seek);
			printf("삭제 완료\n");
			cnt--;
			return;
		}
		prev=seek;
		seek= seek->next;
	}
}

node_t* removeall(node_t* list_head)
{
	if (list_head ==NULL){
		return NULL;
	}
	node_t* tmp=list_head;
	list_head=list_head->next;
	while (list_head!=NULL){
		free(tmp);
		tmp=list_head;
		list_head=list_head->next;
	}
	free(tmp);
	cnt=0;
	return NULL;
}

void changecheck(node_t* list_head, node_t*(*func)(node_t*, char*))
{
	node_t* tmp;
	char eng[20];
	printf("체크표시를 바꿀 영단어 : ");
	scanf("%s",eng);

	tmp=func(list_head,eng);
	if (tmp == NULL){
		printf("없는 단어입니다.\n");
		return;
	}

	if (tmp->check == 0){
		printf("%s 체크표시를 하겠습니다.\n", eng);
		tmp->check =1;
		return;
	}	
	else {
		printf("%s 체크표시를 지우겠습니다.\n",eng);
		tmp->check =0;
		return;
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
		fprintf(fp,"%s %s %s %d %d\n",tmp->english,tmp->korean,tmp->form,tmp->check, tmp->wrongcount);
		list_head=list_head->next;
		free(tmp);
	}
	fclose(fp);
	printf("저장을 완료했습니다.\n");
}

void openfile(node_t** list_head)
{
	(*list_head) = removeall(*list_head);
	node_t* new_node;
	FILE* fp = fopen("dictionary.txt","r+");
	if (fp==NULL){
		printf("파일을 열 수 없습니다.\n");
		return ;
	}
	while(!feof(fp)){
		new_node = (node_t*) malloc (sizeof(node_t));
		fscanf(fp,"%s %s %s %d %d\n",new_node->english,new_node->korean, new_node->form, &new_node->check, &new_node->wrongcount);
		if (*list_head  == NULL)
			*list_head = new_node;
		else {
			node_t* tmp  = *list_head;
			while (tmp->next != NULL)
				tmp = tmp ->next;
			tmp -> next = new_node;
		}
		cnt++;
	}
	fclose(fp);
	printf("파일을 불러왔습니다.\n");
}

void minitest(node_t* list_head)
{
	node_t* tmp=list_head;
	srand(time(NULL));
	int i, sub_i;
	char answer[20];
	int score=0;
	if (cnt<=4){
		int list[cnt];
		for (i=0; i<cnt; i++){
			list[i] = rand()%cnt;
			for (sub_i=0;sub_i<i;sub_i++){
				if(list[i] == list[sub_i]){
					i--;
					break;
				}
			}
		}
		for (i=0;i<cnt;i++){
			for(int j=0; j<list[i];j++){
				list_head= list_head->next;
			}
			printf("%s의 한글 뜻은 ? ",list_head->english);
			scanf("%s",answer);
			if (strcmp(list_head->korean, answer) ==0){
				printf("정답\n");
				score++;
			}
			else {
				printf("오답\n");
				list_head->check=1;
				list_head->wrongcount+=1;
				printf("정답 : %s\n",list_head->korean);
			}
			list_head=tmp;
		}
	}

	else {
		int list[5];
		for (i=0;i<5;i++){
			list[i] = rand()%cnt;
			for(sub_i=0;sub_i<i;sub_i++){
				if (list[i] == list[sub_i]){
					i--;
					break;
				}
			}
		}
		for (i=0; i<5;i++){
			for(int j=0; j<list[i];j++){
				list_head=list_head->next;
			}		
			printf("%s의 한글 뜻은 ? ",list_head->english);
			scanf("%s",answer);
			if (strcmp(list_head->korean, answer) ==0){
				printf("정답\n");
				score++;
			}
			else {
				printf("오답\n");
				list_head->check = 1;
				list_head->wrongcount+=1;
				printf("정답 : %s\n",list_head->korean);
			}
			list_head=tmp;
		}
	}
	
	printf("점수 : %d\n",score);
	return;
}

void retest(node_t* list_head)
{
	srand(time(NULL));
	node_t* tmp = list_head;
	int i, sub_i;
	int list[cnt];
	char answer[20];
	for (i = 0 ; i<cnt; i++){
		list[i] = rand()%cnt;
		for (sub_i=0; sub_i<i; sub_i++){
			if ( list[i] == list[sub_i]){
				i--;
				break;
			}
		}
	}
	for( i=0; i<cnt;i++){
		for ( int j =0; j<list[i]; j++){
			list_head = list_head->next;
		}
		if ((list_head->wrongcount)>=1){
			printf("%s의 한글 뜻은 ? ",list_head -> english);
			scanf("%s",answer);
			if (strcmp(list_head->korean, answer)==0){
				printf("정답\n");
				list_head->wrongcount -= 1;
			}
			else{
				printf("오답\n");
				list_head->wrongcount += 1;
				printf("정답 : %s\n",list_head->korean);
			}
		}
		list_head=tmp;
	}
	return ;
}


