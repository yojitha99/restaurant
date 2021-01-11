#include<stdio.h>
#include<conio.h>
void admin();
void admincontrols();
void createmenu();
void updateitem();
void deleteitem();
void additem();
void customer();
void header();
void displaymenu();
int searchitem(char []);
struct item{
	int id;
	char name[100];
	int cost;
}rec;
char usname[6]="mrecw";
char pass[6]="mrecw";
int f=0;
struct item dl={0};
void main()
{
	char role[100];
	int r=0;
	clrscr();
	header();
	printf("\nEnter 1 to login as admin\n");
	printf("Enter 2 to login as customer\n");
	scanf("%d",&r);
	if(r==1){
		admin();
	}
	else {
		customer();
	}
getch();
}
void admin()
{
char u[100];
	char p[100];
	int c=1;
	printf("Enter username and password");
	while(c<=3){
	printf("\nUsername:");
	scanf("%s",u);
	printf("Password:");
	scanf("%s",p);


		if(strcmp(u,usname)==0 && strcmp(pass,p)==0)
		{
			textcolor(GREEN);
			cprintf("Logged in successfully\n");
			admincontrols();
			break;
		}
		else{
			textcolor(RED);
			cprintf("Incorrect username or password.Please try again");
		}
		c+=1;

	}

	if(c==3)
	{
		textcolor(RED);
		cprintf("Logging in failed\n");
	}
	getch();
}

void admincontrols()
{
	int choice=0;
	char itn[100];
	long int t=0;
	while(1){
		textcolor(YELLOW);
		cprintf("\nEnter your choice\n");
		printf("\n1.Create menu\n2.Update an item\n3.Delete an item\n4.Add a new item\n5.search for an item\n6.display menu\n7.exit\n");
		scanf("%d",&choice);
		switch(choice)
		{

			case 1:createmenu();
			break;
			case 2:updateitem();
			break;
			case 3:deleteitem();
			break;
			case 4:additem();
			break;
			case 5:printf("Enter the name of the item you want to search : ");
					scanf("%s",itn);
					t=searchitem(itn);
					if(t==-1)
						printf("Item not found\n");

			break;
			case 6:displaymenu();
			break;
			case 7:exit(0);
			break;
		}
	}
	getch();
}
void customer()
{
		int x,n=1;
		int z=0;
		float disc;
		long int tc=0;
		float total;
		char in[100];
		while(n==1){
			printf("Enter the item name : ");
			scanf("%s",in);
			printf("Enter quantity : ");
			scanf("%d",&x);
			z=searchitem(in);
			if(z==-1)
			{
				textcolor(RED);
				printf("Item is not available.");
			}
			else
				tc+=z*x;
			printf("Do you want to take more items(1 or 0) : ");
			scanf("%d",&n);
		}
		printf("\n\nYour total bill = %ld\n",tc);
		disc=tc/10;
		printf("Discount        = %.2f\n",disc);
		printf("--------------------------\n");
		total=tc-disc;
		printf("PAYABLE AMOUNT  = %.2f\n",total);
		printf("\n--------------------------");
		textcolor(YELLOW);
		cprintf("\n\nTHANK YOU!VISIT AGAIN!!\n");
		getch();
}
void createmenu()
{
	FILE *fp;	int num=0;
	fp=fopen("menu.txt","w+");
	if(fp==NULL)
	{
		printf("FILE IS NOT CREATED");
	}
	else{
		textcolor(GREEN);
		cprintf("One file created successfully\n");
		}

}
void updateitem()
{
	FILE *fp;
	int q;
	fp=fopen("menu.txt","r+");
	printf("Enter the item i'd you want to update : ");
	scanf("%d",&q);
	while(fread(&rec,sizeof(rec),1,fp)) {

		if(q==rec.id ){
			printf("Enter the new cost and name :");
			scanf("%d %s",&rec.cost,rec.name);
			printf("Item id = %d\nItem name = %s\nItem cost = %d\n",rec.id,rec.name,rec.cost);
			fseek(fp,ftell(fp)-sizeof(rec),0);
			fwrite(&rec,sizeof(rec),1,fp);
		}
	}

	fclose(fp);
	getch();
}
void deleteitem()
{
	FILE *fp;
	int x=0;
	int deltemp=0;
	struct item rec1={-1,"",-1};
	fp=fopen("menu.txt","r+");
	if(fp==NULL)
	{
		textcolor(RED);
		cprintf("FILE IS NOT OPENED");
		exit(0);
	}
	printf("ENTER UR ID TO BE DELETED:");
	scanf("%d",&x);
	while(fread(&rec,sizeof(rec),1,fp))
	{
		if(rec.id==x)
		{
			f=1;
			textcolor(GREEN);
			cprintf("\n\t\t\tONE RECORD IS DELETED SUCCESSFULLY\n");
			printf("\nID :%d",rec.id);
			printf("\nITEM NAME :%s",rec.name);
			printf("\nCOST:%d",rec.cost);
			printf("\n\n");
			getch();
			fseek(fp,ftell(fp)-sizeof(rec),0);
			fwrite(&rec1,sizeof(rec),1,fp);
		}
	}
	if(f==0){
		textcolor(RED);
		cprintf("NO ITEMS TO BE DELETED");
	}

	fclose(fp);
	getch();
}
void additem()
{
	FILE *fp;
	fp=fopen("menu.txt","a");
	printf("Enter the item name\n");
	scanf("%s",rec.name);
	printf("Enter the item id\n");
	scanf("%d",&rec.id);
	printf("Enter the item cost\n");
	scanf("%d",&rec.cost);
	fwrite(&rec,sizeof(rec),1,fp);
	fclose(fp);
}
int searchitem(char s[])
{
	FILE *fp;
	fp=fopen("menu.txt","r");

	while(fread(&rec,sizeof(rec),1,fp)) {

		if(strcmp(rec.name,s)==0 ) {
			printf("Item id = %d\nItem name = %s\nItem cost = %d\n",rec.id,rec.name,rec.cost);
			return (rec.cost);
		}
	}
	fclose(fp);
	return -1;
	getch();
}
void header()
{
	clrscr();
	gotoxy(20,5);
	textcolor(GREEN);
	cprintf("**********************************");
	gotoxy(25,6);
	textcolor(WHITE);
	cprintf("RESTAURANT BILLING SYSTEM");
	gotoxy(20,7);
	textcolor(GREEN);
	cprintf("**********************************");
}
void displaymenu()
{
	FILE *fp;
	fp=fopen("menu.txt","r");
	if(fp==NULL)
	{
		textcolor(RED);
		cprintf("MENU IS NOT OPENED");
		exit(0);
	}
	while(fread(&rec,sizeof(rec),1,fp))
	{
		f=1;
		if(rec.id!=-1){
		printf("\nID :%d",rec.id);
		printf("\nITEM NAME :%s",rec.name);
		printf("\nITEM COST :%d",rec.cost);
		printf("\n\n");
		}
	}
	if(f==0){
		textcolor(RED);
		cprintf("\n\n\t\t\tNO ITEMS IN THE MENU");
	}
	fclose(fp);
	getch();
}