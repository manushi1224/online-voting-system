#include<stdio.h>
#include<stdlib.h>
struct node{
	char *name;
	char *aadhar;
	char *birth_date;
	char *voter_det;
	char *sign;
	int votes;
	char *party_name;
	int cand_no; 
	struct node *next;
}*head=NULL,*voter,*cand,*p,*ptr,*r;
char v_name[100],aadhar_c[100],b_date[100],c_name[100],c_sign[100],p_name[100];
int vote,count,count_vote=0,dd,mm,yy,v_age;
void read_database_v(){
	ptr=NULL;
	struct node *last;
	last=ptr;
	char str[100];
	int filempty=0;
	FILE *fp=fopen("voters.txt","r");
	fseek(fp,0,SEEK_END);
	int len=(int)ftell(fp);
	if(len<=0){
		filempty=1;
		printf("File empty");
	}
	if(filempty==0){
		rewind(fp);//sets the file position to the beginning of the file for the stream pointed to by stream
		while(fgets(str,sizeof(str),fp)){	
			struct node *node;
			node=(struct node*)malloc(sizeof(struct node));
			node->voter_det=strdup(str);
			node->next=NULL;	
			if(feof(fp)){
				break;
			}
			if(last==NULL){
				last=ptr=node;
			}
			else{
				last=last->next=node;
			}
		}
		fclose(fp);
	}
}
void read_database_c(){
	ptr=NULL;
	count=0;
	struct node *last;
	last=ptr;
	char str[100];
	int	filempty=0;
	FILE *fp=fopen("candidates.txt","r");
	fseek(fp,0,SEEK_END);
	int len=(int)ftell(fp);
	if(len<=0){
		filempty=1;
		printf("File empty");
	}
	if(filempty==0){
		rewind(fp);//sets the file position to the beginning of the file for the stream pointed to by stream
		while(fgets(str,sizeof(str),fp)){	
			struct node *node;
			node=(struct node*)malloc(sizeof(struct node));
			node->voter_det=strdup(str);
			node->next=NULL;	
			if(feof(fp)){
				break;
			}
			if(last==NULL){
				last=ptr=node;
			}
			else{
				last=last->next=node;
			}
			count++;
		}
		fclose(fp);
		//printf("%s",last->voter_det);
	}
}
int age(int year){
	return (2022-year);
}
