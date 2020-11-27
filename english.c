#include<stdio.h>
#include<string.h>
#include<memory.h>
#include<stdlib.h>

struct dictionary {
	char english[20];
	char korean[20];
	char form[20];
	int check;   // 1, 0 으로 체크
};

void add(int number,struct dictionary* dict)
{
	char eng[20];
	char kor[20];
	char pom[20];
	printf("영어 입력 : ");
	scanf("%s",eng);
	strcpy(dict[number].english, eng);
	printf("한글뜻 입력 : ");
	scanf("%s",kor);
	strcpy(dict[number].korean, kor);
	printf("품사 입력 : ");
	scanf("%s",pom);
	strcpy(dict[number].form, pom);
	dict[number].check=0;
}

void sub(int number,struct dictionary *dict)
{
	char delete[20];
	printf("삭제하고 싶은 영단어 입력 : ");
	scanf("%s",delete);
	for (int i=0; i<number;i++){
		if (strcmp(dict[i].english, delete) == 0){
			for (int j=i; j<number; j++){
				memcpy(&dict[j],&dict[j+1],sizeof(dict));
			}
		}
	}
}
	
void wordlist(int number,struct dictionary *dict)
{
	for(int i=0; i<number; i++){
		printf("%s-",dict[i].english);
		printf("%s:",dict[i].korean);
		printf("%d\n",dict[i].check);
	}
}

int determining(int number,struct dictionary *dict)
{
	return dict[number].check == 1? 1: 0;
}

void changetocheck(int number ,struct dictionary *dict, int (*func)(int, struct dictionary* ))
{	
	char temp[20];
	int i;
	int index= number;
	printf("체크표시 여부를 바꿀 단어 영어로 쓰기 : ");
	scanf("%s",temp);
	for( i=0;i<number;i++){
		if (strcmp(dict[i].english,temp)==0){
			  number=i;
			  if (func(number, dict)==1)
				  dict[number].check=0;
			  else 
				  dict[number].check=1;
		}
	}
	number = index;
}

void printcheckedlist(int number, struct dictionary *dict,int (*func)(int, struct dictionary* ))
{
	int i;
	int index=number;
	for (i=0;i<number;i++){
		number=i;
		if (func(number,dict)==1){
			printf("%s-",dict[number].english);
			printf("%s\n",dict[number].korean);
		}
	}
	number=index;
}

void searchword(int number, struct dictionary *dict)
{
	char finding[20];
	printf("찾고 싶은 영단어 입력 : ");
	scanf("%s",finding);
	for (int i=0;i<number;i++){
		if(strcmp(dict[i].english,finding)==0){
			printf("%s-",dict[i].english);
			printf("%s-",dict[i].korean);
			printf("%s\n",dict[i].form);
		}
	}
}
void partofspeech(int number,struct dictionary *dict)
{
	char finding[20];
	printf("출력할 영단어들의 품사 : ");
	scanf("%s",finding);
	for (int i=0;i<number;i++){
		if ( strcmp(dict[i].form, finding)==0){
			printf("%s-",dict[i].english);
			printf("%s\n",dict[i].korean);
		}
	}
}

int main(void)
{
	int menu;
	int number=0;
	struct dictionary dict[20];
	int end=0;
	while(1){
		printf("============\n");
		printf("0. 단어장 불러오기\n");
		printf("1. 단어 추가\n");
		printf("2. 단어 삭제\n");
		printf("3. 추가했던 단어들의 리스트 출력\n");
		printf("4. 단어 체크표시를 하는 기능\n");
		printf("5. 체크된 단어들 리스트 출력\n");
		printf("6. 단어 검색(품사까지 출력)\n");
		printf("7. 품사별 출력\n");
		printf("8. 단어장(txt file)에 저장\n"); 
		printf("9. 종료\n");
		printf("============\n");
		printf("input menu : ");
		scanf("%d",&menu);
		switch(menu)
		{
			case 0:

			case 1:
				add(number,dict);
				number++;
				break;			
			case 2:
				sub(number, dict);
				number--;
				break;
			case 3:
				wordlist(number, dict);
				break;
			case 4:
				changetocheck( number, dict, determining);
				break;
			case 5:
				printcheckedlist(number, dict ,determining);
				break;
			case 6:
				searchword(number,dict);
				break;
			case 7:
				partofspeech(number,dict);
				break;
			case 9:
				printf("end\n");
				end=1;
				break;
		}
		if (end ==1)
			break;
	}
	return 0;
}

