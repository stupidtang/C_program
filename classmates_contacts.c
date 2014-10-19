//第一次设计实验，同学录管理系统
//by fion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STU_INFO_FILE	"c:\\classmates_info_file.txt" //定义文本信息存储路径，可自己修改 
#define FAILURE 0xFFFFFFFF
#define SUCCESS !0xFFFFFFFF
#define	MAX_STU_COUNT 60
#define TRUE	 1
#define	FALSE	0

char		Name[MAX_STU_COUNT][10+1];	//存放姓名，最长为10个字符； 
char		Email[MAX_STU_COUNT][20+1]; //存放Email，最长为20个字符； 
long long int		StudentNumber[MAX_STU_COUNT]; //学号过长，即便unsigned int也不够存储，采用64位整型。在VC中定义64位整型也可采用__int64关键字，在输入/输出时也可以采用%I64d控制符；
long long int		MobilePhoneNumber[MAX_STU_COUNT]; //同上 
long long int		QQNumber[MAX_STU_COUNT]; //同上
int			CurrentStudentCount = 0;

int AddStuInfoFromFile()                     //此函数用于从文本文件中读入学生信息数据，并放到上面的全局数组中
{
	int tmpi;
	char student_number_char[13 + 1];
	char mobile_phone_number_char[11 + 1];	
	char qq_number_char[10 + 1];	
	FILE * pFile = NULL;
	
	pFile = fopen(STU_INFO_FILE, "r");
	if(!pFile)
	{
		printf("AddStuInfoFromFile: File Open Failed!\n");
		return FAILURE;
	}
	else
		printf("AddStuInfoFromFile: File Open Succeeded!\n");
	
	memset(StudentNumber,0,8);
	memset(MobilePhoneNumber,0,8);
	memset(QQNumber,0,8);
	memset(Name,0,MAX_STU_COUNT * (10 + 1));
	memset(Email,0,MAX_STU_COUNT * (20 + 1));	
	
	while(!feof(pFile))
	{		
		fscanf(pFile,"%s",student_number_char);
		fscanf(pFile,"\t%s",Name[CurrentStudentCount]);
		fscanf(pFile,"\t%s",mobile_phone_number_char);
		fscanf(pFile,"\t%s",Email[CurrentStudentCount]);
		fscanf(pFile,"\t%s\n",qq_number_char);
		StudentNumber[CurrentStudentCount] = _atoi64(student_number_char);
		MobilePhoneNumber[CurrentStudentCount] = _atoi64(mobile_phone_number_char);		
		QQNumber[CurrentStudentCount] = _atoi64(qq_number_char);		
		CurrentStudentCount++;
	}
	
	fclose(pFile);
	return SUCCESS;
}

void Output(int index)		//此函数用于将指定序号的同学录信息打印到屏幕
{
	//------------------------在下面编写output()的代码--------------------------
	printf("%lld  %s\t%lld  %s\t%lld\n",StudentNumber[index],Name[index],MobilePhoneNumber[index],Email[index],QQNumber[index]);
}

void OutputAll()			//将全部同学录信息打印到屏幕
{
	//------------------------在下面编写outputAll()的代码-----------------------
	int i;
	for (i=0;i<CurrentStudentCount;i++)
	{
			printf("%lld  %s\t%lld  %s\t%lld\n",StudentNumber[i],Name[i],MobilePhoneNumber[i],Email[i],QQNumber[i]);
	}
	printf("\n");
}

int Find(long long int mobile_phone_number, long long int qq_number)	//根据手机号和QQ号查找学生基本信息
{
	//------------------------在下面编写find()的代码--------------------------
    int i;

	for (i=0;i<CurrentStudentCount;i++)
	{
		if( MobilePhoneNumber[i]==mobile_phone_number||QQNumber[i]==qq_number )
	    
		{
			return i;
			break;
		}
	}
}

int Insert(
		   unsigned int 	index,
		   char			name[10+1],
		   char			email[20+1],
		   long long int 		student_number,
		   long long int		mobile_phone_number,
		   long long int 		qq_number
		   )										//将一条新增学生信息插入到指定序号之后
{
	//------------------------在下面编写insert()的代码------------------------
	int i,j;
	int b=CurrentStudentCount;
	
    for (i=index;i<=CurrentStudentCount;i++)
	{
	    for (j=0;j<11;j++)
			Name[b+1][j] = Name[b][j];
		for (j=0;j<21;j++) 
            Email[b+1][j]=Email[b][j];  
		StudentNumber[b+1]=StudentNumber[b]; 
        MobilePhoneNumber[b+1]=MobilePhoneNumber[b]; 
        QQNumber[b+1]=QQNumber[b];
		b--;
	}

	for (j=0;j<11;j++)
		Name[index][j]=name[j];
	for (j=0;j<21;j++)
		Email[index][j]=email[j];
	StudentNumber[index]=student_number;
    MobilePhoneNumber[index]=mobile_phone_number;
	QQNumber[index]=qq_number;

	CurrentStudentCount++;
    printf("\n");
}

int Delete(unsigned int index)		//将指定序号的学生信息删除
{
	//------------------------在下面编写delete()的代码--------------------------
	unsigned int i,j;

	for (i=index;i<=CurrentStudentCount;i++)
	{
	    for (j = 0; j < 11; j++)
			Name[i][j] = Name[i+1][j];
		for (j=0;j<11;j++) 
            Email[i][j]=Email[i+1][j];  
		StudentNumber[i]=StudentNumber[i+1]; 
        MobilePhoneNumber[i]=MobilePhoneNumber[i+1]; 
        QQNumber[i]=QQNumber[i+1];  
	
	}

	CurrentStudentCount--;
}

int main(void)		//主函数，从文件读入数据，显示菜单，并根据用户的选择进行处理
{
	//------------------------在下面编写main()的代码-----------------------------
	int AddStuInfoFromFile();  
	void Output(int index);
	void OutputAll();
	int Find(long long int mobile_phone_number, long long int qq_number);
	int Insert(
		   unsigned int 	index,
		   char			name[10+1],
		   char			email[20+1],
		   long long int 		student_number,
		   long long int		mobile_phone_number,
		   long long int 		qq_number
		   )	;
	int Delete(unsigned int index);


	unsigned int b;
	int a,c,d;
	long long int i,j;
	long long int mobile_phone_number,
		          qq_number,
		          index;
    char name[11],
		 email[21];

	long long int	 student_number;
	
	AddStuInfoFromFile();  
	
	for(;;){

	printf("欢迎使用同学录管理系统\n菜单选项：\n1、查询 \n2、插入 \n3、删除 \n4、输出(全体通讯录) \n5、退出");
	printf("\n请输入你要选择的服务的数字代码\n\n");
	scanf("%d",&a);

	switch(a){

	case 1:printf("请输入你所要查询人的手机号码和QQ号码\n(中间用“/”分隔，若不知其中一个号码填0)\n\n");
		   scanf("%lld/%lld",&i,&j);

		   Output( Find(i,j) );
		
		   break;
	
   case 2:printf("请输入你要添加的信息 （序号/名字/邮箱/学号/手机号码/QQ号码）\n ");
	      scanf("%d %s %s %lld",&d,&name,&email,&student_number);
		  scanf("%lld %lld",&mobile_phone_number,&qq_number);
	
	      Insert(d-1,name,email,student_number,mobile_phone_number,qq_number);
		  break;

	case 3:printf("请输入要删除信息的序号\n");
		   scanf("%ud",&b);
		   Delete(b-1);
		   break;
	
	case 4:OutputAll();
		   break;
	
	case 5:exit(0);
		   break;
	
	}
	}
}

