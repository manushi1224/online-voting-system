#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "read_database.c"

void register_voter()
{
	system("CLS");
	printf("--------------------------------------------------------------\n");
	printf("			REGISTER VOTER ID		\n");
	printf("--------------------------------------------------------------\n\n");
	FILE *fp;
	fp=fopen("voters.txt","a");
	if(fp==NULL){
		printf("FILE IS NOT OPENED!");
		return;
	}
	//struct node *v;
	//v=voter;
	printf( "enter your details:\n");
	printf("Enter your name:\n");
	fflush(stdin);
	gets(v_name);
	printf("enter your aadhar ID:");
	fflush(stdin);
	gets(aadhar_c);
	printf("enter your birthdate:(In dd/mm/yy format)");
	scanf("%d/%d/%d",&dd,&mm,&yy);
	sprintf(b_date,"%d/%d/%d",dd,mm,yy);
	//gets(b_date);
	v_age=age(yy);
	if(v_age>=18){
		voter=(struct node*)malloc(sizeof(struct node));
		voter->name=strdup(v_name);
		voter->aadhar=strdup(aadhar_c);
		voter->birth_date=strdup(b_date);
		voter->next=NULL;
		//fp=fopen("voters.txt","a");
		fprintf(fp,"%s	%s	%s\n",voter->name,voter->aadhar,voter->birth_date);
		printf("YOUR VOTER ID IS CREATED SUCCESSFULLY!!\n\n");
		fclose(fp);
	}
	else{
		printf("YOU ARE NOT ELLIGIBLE!\n");
	}	
}

void login(){
	printf("------------------------------------------------------------\n");
	printf("			LOGIN PORTAL		\n");
	printf("------------------------------------------------------------\n\n");
	read_database_v();
	char svoter[100];
	int flag=0;
	p=ptr;
	printf("Enter your name:\n");
	fflush(stdin);
	gets(v_name);
	printf("Enter your aadhar:");
	fflush(stdin);
	gets(aadhar_c);
	//printf("enter your birthdate:");
	printf("enter your birthdate:(In dd/mm/yy format)");
	scanf("%d/%d/%d",&dd,&mm,&yy);
	sprintf(b_date,"%d/%d/%d",dd,mm,yy);
	fflush(stdin);
	//gets(b_date);
	sprintf(svoter,"%s	%s	%s\n",v_name,aadhar_c,b_date);
	
	//printf("%d",p);
	//puts(svoter);
	if(p==NULL){
		printf("List is empty!");
	}
	while(p!=NULL){
		//strcpy(p->voter_det,svoter);
		if(strcmp(p->voter_det,svoter)==0)
		{
			//sleep(1000);
			printf("LOGIN SUCCESSFULL!!\n");
			flag==1;
		}
		p=p->next;
	}
	if(flag==0){
			printf("INVALID CREDENTIALS!!\n\nPLEASE ENTER CORRECT NAME/AADHAR/BIRTH DATE.\n\n");
			login();
	}
}

void reg_candidate()
{
	system("CLS");
	printf("--------------------------------------------------------------\n");
	printf("			REGISTER CANDIDATE		\n");
	printf("--------------------------------------------------------------\n\n");
	FILE *fp=fopen("candidates.txt","r");
	if(fp==NULL){
		printf("FILE IS NOT OPENED!");
		return;
	}
	int i=1;
	char chr;
	chr=fgetc(fp);
	while(chr!=EOF)
	{
		if(chr=='\n')
		{
			i=i+1;
		}
		chr=getc(fp);
	}
	fclose(fp);
	printf("Candidate No: %d\n",i);
	printf("Enter your name:");
	fflush(stdin);
	gets(c_name);
	printf("Enter your party's name:'");
	fflush(stdin);
	gets(p_name);
	printf("The sign is:");
	fflush(stdin);
	gets(c_sign);
	vote=0;
	cand=(struct node*)malloc(sizeof(struct node));
	cand->cand_no=i;
	cand->name=strdup(c_name);
	cand->sign=strdup(c_sign);
	cand->party_name=strdup(p_name);
	cand->votes=vote;
	cand->next=NULL;
	fp=fopen("candidates.txt","a");
	fprintf(fp,"%d		%s		%s		%s		%d\n",cand->cand_no,cand->name,cand->sign,cand->party_name,cand->votes);
	printf("CANDIDATE IS ADDED SUCCESSFULLY!!\n\n");
	fclose(fp);
}

void display_candidates(){
	read_database_c();
	r=ptr;
	if(r==NULL)
	{
		printf("list is empty");
	}
	else
	{
		printf("---------------------------------------------------------------------\n");
		printf("	No ||	Candidate's Name  ||  	Sign 	|| Party Name ||   Votes   \n");
		printf("---------------------------------------------------------------------\n");
		do
		{
    		printf("	%s",r->voter_det);
    		r=r->next;
		}while(r!=NULL);
	}
}

void vote_cand()
{
	int choice,len,c_no;
	char ch[100],str[100],c_n[100],c_s[100],c_p[100],vote_str[100];
	read_database_c();
	//printf("%d",count);
	//int a[count-1]=0;
	display_candidates();
	printf("Please enter your choice");
	scanf("%d",&choice);
	FILE *fp,*fq;
	fq=fopen("candidates.txt","r");
	fp=fopen("candidates_temp.txt","w");
	sprintf(ch,"%d",choice);
	strcpy(str,ch);
	len=strlen(str);
	r=ptr;
	if(r==NULL){
		printf("File is empty!");
	}
	else{
		//rewind(fp);
		while(r!=NULL){
			fscanf(fq,"%d		%s		%s		%s		%d\n",&c_no,c_n,c_s,c_p,&count_vote);
			//printf("%d",fseek(fp,0,SEEK_CUR));
			if(strncmp(str,r->voter_det,len)==0){
				//printf("%d",count_vote);
				count_vote++;
			//	printf("%d",count_vote);
				sprintf(vote_str,"%d		%s		%s		%s		%d\n",c_no,c_n,c_s,c_p,count_vote);
				strcpy(r->voter_det,vote_str);
				printf("%s",r->voter_det);
				fputs(r->voter_det,fp);
				//fprintf(fp,"%d		%s		%s		%s		%d\n",c_no,c_n,c_s,c_p,count_vote);
			}
			else{
				//printf("%s",r->voter_det);
				fputs(r->voter_det,fp);
				//fprintf(fp,"%d		%s		%s		%s		%d\n",c_no,c_n,c_s,c_p,count_vote);
			}
			r=r->next;
		}
	}
	fclose(fp);
	fclose(fq);
/*	if(remove("candidates.txt")==0){
		printf("deleted");
	}*/
	remove("candidates.txt");
	rename("candidates_temp.txt","candidates.txt");
	system("CLS");
}

void winner(){
	int choice,len,c_no,count2=0;
	char ch[100],str[100],c_n[100],c_s[100],c_p[100],vote_str[100];
	int i=0;
	read_database_c();
	int a[count-1];
	FILE *fp;
	fp=fopen("candidates.txt","r");
	r=ptr;
	if(r==NULL){
		printf("File is empty!");
	}
	else{
		while(r!=NULL){
			fscanf(fp,"%d		%s		%s		%s		%d\n",&c_no,c_n,c_s,c_p,&count_vote);
			//printf("%d   \n",count_vote);
			a[i]=count_vote;
			i++;
			r=r->next;
		}
		int max=a[0];
		for(i=0;i<(count-1);i++){
			if(a[i]==max){
				count2++;
			}
			else if(a[i]>max){
				max=a[i];
			}
		}
		//printf("%d is the max votes!",max);
		char str[100];
		sprintf(str,"%d",max);
		strcat(str,"\n");
		r=ptr;
		rewind(fp);
		while(r!=NULL){
			fscanf(fp,"%d		%s		%s		%s		%d\n",&c_no,c_n,c_s,c_p,&count_vote);
			if(strstr(r->voter_det,str) && count_vote==max){
				printf("\n%s is the winner with %d votes!!\n\n",c_n,max);
				printf("CONGRATULATIONS!!!\n");
			}
			r=r->next;
		}
	}
	fclose(fp);
	//system("CLS");
}

void admin(){
	printf("-----------------------------------------------\n");
	printf("		WELCOME TO ADMIN PANEL\n");
	printf("-----------------------------------------------\n");
	int t;
	while(t!=5){
		printf("ENTER TASK NO TO BE PERFORMED:\n");
		printf("1.Vote\n");
		printf("2.Register Candidate\n");
		printf("3.Declare Winner\n");
		printf("4.Display Candidates\n");
		scanf("%d",&t);
		switch(t)
		{
			case 1:
				system("CLS");
				vote_cand();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 2:
				system("CLS");
				reg_candidate();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 3:
				system("CLS");
				winner();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 4:
				system("CLS");
				display_candidates();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 5:
				main();
				break;
			default:
				printf("INVALID CHOICE!");		
		}
	}
}

void users(){
	printf("------------------------------------------------\n");
	printf("		WELCOME TO USER PANEL\n");
	printf("------------------------------------------------\n");
	int t;
	while(t!=4){
		printf("ENTER TASK NO TO BE PERFORMED:\n");
		printf("1.Register for Voter ID\n");
		printf("2.Login\n");
		printf("3.Vote\n");
		scanf("%d",&t);
		switch(t)
		{
			case 1:
				system("CLS");
				register_voter();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 2:
				system("CLS");
				login();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 3:
				system("CLS");
				vote_cand();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 4:
				main();
				break;
			default:
				printf("INVALID CHOICE!\n");
		}
	}
}

int main()
{
	int choice;
	printf("-----------------------------------------------------------\n");
	printf("		WELCOME TO ONLINE VOTING SYSTEM		\n");
	printf("-----------------------------------------------------------\n\n");
	while(choice!=7){
		//system("CLS");
		printf("Please select an option:\n");
		printf("1.Admin\n");
		printf("2.User\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				system("CLS");
				admin();
				printf("Press any key to continue!\n");
				getch();
				break;
			case 2:
				system("CLS");
				users();
				printf("Press any key to continue!\n");
				getch();
				break;
		}
	}
	return 0;
}
