#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                 
#include<ctype.h>                   
#include<dos.h>                    \
#include<time.h>
char catagories[][15]={"Samsung","Apple","Nokia","Sony","LG","HTC"};
void returnfunc(void);
void mainmenu(void);
void addbrands(void);
void deletebrands(void);
void editbrands(void); 
void searchbrands(void);
void viewbrands(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void Password();
void loaderanim();
FILE *fp,*ft,*fs;
int s;
char findstaff;
char password[10]="pass";
struct meroDate
{
int mm,dd,yy;
};
struct staff
{
int id;
char stname[20];
char name[20];
char available[20];
int qty;
int price;
int count;
char *cat;
struct meroDate issued;
struct meroDate duedate;
};
struct staff a;
int main()
{
Password();
getch();
return 0;
}
void mainmenu()
{
int i;
printf("\n\t\t\t\tMAIN MENU\n ");
printf("\t\t\\******************************************************************************************\\n");
printf("\n\n<1> Add Mobile Record   ");
printf("\n\n<2> Delete Mobile Record");
printf("\n\n<3> Search Mobile Record");
printf("\n\n<4> View Mobile list");
printf("\n\n<5> Edit Mobile Record");
printf("\n\n<6> Close The Application");
t();
printf("\nEnter your choice:");
switch(getch())
{
case '1':
addbrands();
break;
case '2':
deletebrands();
break;
case '3':
searchbrands();
break;
case '4':
viewbrands();
break;
case '5':
editbrands();
break;
case '6':
exit(0);
default:
{
printf("\aWrong Entry!!Please re-entered correct option");
if(getch())
mainmenu();
}
}
}
void addbrands(void)    
{
int i;
printf("\n\nSELECT BRANDS");
printf("\n<1> Samsung");
printf("\n<2> Apple");
printf("\n<3> Nokia");
printf("\n<4> Sony");
printf("\n<5> LG");
printf("\n<6> HTC");
printf("\n<7> Back to main menu");
printf("\n\nEnter your choice:");
scanf("%d",&s);
if(s==7)
mainmenu() ;
fp=fopen("stf.dat","ab+");
if(getdata()==1)
{
a.cat=catagories[s-1];
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
printf("\n\nThe record is sucessfully saved");
printf("\nSave any more?(Y / N):");
if(getch()=='n')
mainmenu();
else
addbrands();
}
}
void deletebrands()    
{
int d;
char another='y';
while(another=='y')  
{
printf("\n\nEnter the Mobile ID to  delete:");
scanf("%d",&d);
fp=fopen("stf.dat","rb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
printf("\n\nThe Mobile record is available");
printf("\nStaff name is %s",a.name);
findstaff='t';
}
}
if(findstaff!='t')
{
printf("\nNo record is found modify the search");
if(getch())
mainmenu();
}
if(findstaff=='t' )
{
printf("\n\nDo you want to delete it?(Y/N):");
if(getch()=='y')
{
ft=fopen("test.dat","wb+");  
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id!=d)
{
fseek(ft,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,ft); 
}                              
}
fclose(ft);
fclose(fp);
remove("stf.dat");
rename("test.dat","stf.dat"); 
fp=fopen("stf.dat","rb+");    
if(findstaff=='t')
{
printf("\n\nThe record is sucessfully deleted");
printf("\n\tDelete another record?(Y/N)");
}
}
else
mainmenu();
fflush(stdin);
another=getch();
}
}
mainmenu();
}
void searchbrands()
{
int d;
printf("\n\n\t************************************search mobiles*************************************");
printf("\n1. Search By ID");
printf("\n2. Search By Name");
printf("\nEnter Your Choice");
fp=fopen("stf.dat","rb+"); 
rewind(fp);   
switch(getch())
{
case '1':
{
printf("\n************************************mobile id*************************************");
printf("\nEnter the Mobile id:");
scanf("%d",&d);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
Sleep(2);
printf("\nThe Mobile is available\n");
printf("\nID:%d",a.id);
printf("\nBrand:%s",a.cat);
printf("\nName:%s",a.name);
printf("\nAvailability:%s ",a.available);
printf("\nQuantity:%i ",a.qty);
printf("\nPrice:%i ",a.price);
findstaff='t';
}
}
if(findstaff!='t')  
{
printf("\aNo Record Found");
}
printf("\nTry another search?(Y/N)");
if(getch()=='y')
searchbrands();
else
mainmenu();
break;
}
case '2':
{
char s[15];
printf("\n************************************search mobile by name*************************************");
printf("\n\nEnter Mobile Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0) 
{
	printf("\nID:%d",a.id);
	printf("\nName:%s",a.name);
		printf("\nAvailability:%s",a.available);
	printf("\nQuantity:%i",a.qty);
	printf("\nPrice:%i",a.price);
	getch();
	d+=6;
}
}
if(d==0)
printf("\aNo Record Found");
printf("\nTry another search?(Y/N)");
if(getch()=='y')
	searchbrands();
else
	mainmenu();
break;
}
default :
getch();
searchbrands();
}
fclose(fp);
}
void viewbrands(void)  
{
int i=0,j;
system("cls");
printf("************************************mobile list*************************************");
printf(" BRAND\tID\tBRANDNAME\tAVAILABILITY\tQUANTITY\tPRICE \n");
j=4;
fp=fopen("stf.dat","rb");
while(fread(&a,sizeof(a),1,fp)==1)
{
printf("%s\t",a.cat);
printf("%d\t",a.id);
printf("%s\t",a.name);
printf("%s\t",a.available);
printf("%i\t",a.qty);
printf("%i\t",a.price);
printf("\n\n");
j++;
}
fclose(fp);
returnfunc();
}
void editbrands(void)  
{
int c=0;
int d,e;
printf("\n****************************Edit Mobile Section ***************************");
char another='y';
while(another=='y')
{
printf("\n\nEnter Mobile Id to be edited:");
scanf("%d",&d);
fp=fopen("stf.dat","rb+");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(checkid(d)==0)
{
printf("\nThe Mobile is availble");
printf("\nThe Mobile ID:%d",a.id);
printf("\nEnter new name:");
scanf("%s",a.name);
printf("\nEnter new Availability Status:");
scanf("%s",a.available);
printf("\nEnter new Quantity:");
scanf("%i",&a.qty);
printf("\nEnter new Price:");
scanf("%i",&a.price);
printf("\nThe record is modified");
fseek(fp,ftell(fp)-sizeof(a),0);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
c=1;
}
if(c==0)
{
printf("No record found");
}
}
printf("\nModify another Record?(Y/N)");
fflush(stdin);
another=getch() ;
}
returnfunc();
}
void returnfunc(void)
{
{
printf("\n\nPress ENTER to return to main menu");
}
a:
if(getch()==13) 
mainmenu();
else
goto a;
}
int getdata()
{
int t;
printf("\nEnter the Information Below");
printf("\nBrand:");
printf("%s",catagories[s-1]);
printf("MBL ID:\t");
scanf("%d",&t);
if(checkid(t) == 0)
{
printf("\aThe id already exists\a");
getch();
mainmenu();
return 0;
}
a.id=t;
printf("\nModel Name:");
scanf("%s",a.name);
printf("\nAvailability:");
scanf("%s",a.available);
printf("\nQuantity:");
scanf("%i",&a.qty);
printf("\nPrice:");
scanf("%i",&a.price);
return 1;
}
int checkid(int t)  
{
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
if(a.id==t)
return 0;  
return 1; 
}
int t(void) 
{
time_t t;
time(&t);
printf("\nDate and time:%s\n",ctime(&t));
return 0 ;
}
void Password(void) 
{
char ch,pass[10];
int i=0,j;
	printf("\t\t\t\tWELCOME\n\t\t\t\t  To \n\t\t   *******************mobile store management system**********************\n");
	printf("\t \n\n\n Enter Password:");
while(ch!=13)
{
ch=getch();
if(ch!=13 && ch!=8){
putch('*');
pass[i] = ch;
i++;
}
}
pass[i] = '\0';
if(strcmp(pass,password)==0)
{
printf("\n\n\n\t\tPassword matched!!");
printf("\n\n\tPress any key to countinue.....:");
getch();
mainmenu();
}
else
{
printf("\n\n\n\t\t\aWarning!! \n\t   Incorrect Password");
getch();
Password();
}
}
