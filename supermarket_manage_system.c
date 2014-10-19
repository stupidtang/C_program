//第二次设计实验，超市商品管理系统
//by fion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GOOD_INFO_FILE	"e:\\goodinfo.txt" 
#define FAILURE 0xFFFFFFFF
#define SUCCESS !0xFFFFFFFF
#define	MAX 100

struct GoodInfo{
    char     good_id[30];
	char     good_name[30];
	char     good_price[10];
	char     good_discount[10];
	int      good_amount;
	int      good_remain;
}*Goods[MAX];

int Count=0;

int  info_init()      //--------------------------->该函数用于初始化，读入文本数据 
{
	FILE *pFile = NULL;
	
	pFile = fopen(GOOD_INFO_FILE, "r");
	if(!pFile)
	{
		printf("商品信息初始化失败！\n");
		return FAILURE;
	}
	else
		printf("商品信息初始化成功！\n");

	while(!feof(pFile))
        {
	         Goods[Count]=(struct GoodInfo *)malloc(sizeof(struct GoodInfo ));
			 fscanf(pFile,"%s",Goods[Count]->good_id);
             fscanf(pFile,"\t%s",Goods[Count]->good_name);
             fscanf(pFile,"\t%s",Goods[Count]->good_price);
             fscanf(pFile,"\t%s",Goods[Count]->good_discount);
             fscanf(pFile,"\t%d",&Goods[Count]->good_amount);
             fscanf(pFile,"\t%d\n",&Goods[Count]->good_remain);
			 Count++;
	    }
	fclose(pFile);
	return SUCCESS;
}

int  info_search(char Name[30])     //--------------------------->该函数用于查找商品信息
{
	int i;

	for (i=0;i<Count;i++)
	if (strcmp(Name,(*Goods[i]).good_name)==0)             
			return i;
	return -1;
}

int info_flush()     //----------------------------------->该函数用于将商品信息录入到文本中
{
    int i=0;
	FILE *qFile=NULL;

	qFile=fopen(GOOD_INFO_FILE,"w");
    
	for(;i<Count;i++)
	   {
		   fprintf(qFile,"%s",Goods[i]->good_id);
		   fprintf(qFile,"\t%s",Goods[i]->good_name);
		   fprintf(qFile,"\t%s",Goods[i]->good_price);
		   fprintf(qFile,"\t%s",Goods[i]->good_discount);
		   fprintf(qFile,"\t%d",Goods[i]->good_amount);
		   fprintf(qFile,"\t%d\n",Goods[i]->good_remain);
        }
	
	fclose(qFile);
	return;
}

void freeGoodInfo()          //------------------------------->该函数用于释放空间
{
	int i;
	for (i=0;i<Count;i++)
		free(Goods[i]);                           
}

int  info_change(char Name[30])     //-------------------------------->该函数用于修改商品信息
{
	int i,index;
	char id[30];
	char name[30];
	char price[10];
	char discount[10];
	int amount;
	int remain;

	printf("下面请输入商品的新信息\n");
	printf("新商品的id:");scanf("%s",id);
	printf("新商品的名称:");scanf("%s",name);
	printf("新商品的价格:");scanf("%s",price);
	printf("新商品的折扣:");scanf("%s",discount);
	printf("新商品的总数:");scanf("%d",&amount);
	printf("新商品的剩余量:");scanf("%d",&remain);
	
	index=info_search(Name);
	
	if (index!=-1)
	{
		strcpy((*Goods[index]).good_id,id);
		strcpy((*Goods[index]).good_name,name);
		strcpy((*Goods[index]).good_price,price);
		strcpy((*Goods[index]).good_discount,discount);
		(*Goods[index]).good_amount=amount;
		(*Goods[index]).good_remain=remain;
		printf("商品信息修改成功！\n");
		printf("\n");
		return;
	}
	printf("您要修改的商品不存在！\n");
}


int  info_dele(char Name[30])     //------------------------------>该函数用于删除某个商品信息
{
	int i,index;
	
	index=info_search(Name);
	
	for (i=index;i<Count-1;i++)
	{
		strcpy((*Goods[i]).good_id,(*Goods[i+1]).good_id);
		strcpy((*Goods[i]).good_name,(*Goods[i+1]).good_name);
		strcpy((*Goods[i]).good_price,(*Goods[i+1]).good_price);
		strcpy((*Goods[i]).good_discount,(*Goods[i+1]).good_discount);
		(*Goods[i]).good_amount=(*Goods[i+1]).good_amount;
		(*Goods[i]).good_remain=(*Goods[i+1]).good_remain;
	}
	Count--;
	
	free(Goods[Count]);

	printf("商品信息删除成功！\n");
	printf("\n");
}





int info_insert(int index)     //--------------------------------->该函数用于插入商品信息
{
	int i;
	char id[30];
	char name[30];
	char price[10];
	char discount[10];
	int amount;
	int remain;

	printf("下面请输入插入商品的信息\n");
	printf("插入商品的id:");
	scanf("%s",id);
    printf("插入商品的名称:");
	scanf("%s",name);
	printf("插入商品的价格:");
	scanf("%s",price);
	printf("插入商品的折扣:");
	scanf("%s",discount);
	printf("插入商品的总数:");
	scanf("%d",&amount);
	printf("插入商品的剩余量:");
	scanf("%d",&remain);

	Goods[index]=(struct GoodInfo *)malloc(sizeof(struct GoodInfo ));

	strcpy((*Goods[index]).good_id,id);
	strcpy((*Goods[index]).good_name,name);
	strcpy((*Goods[index]).good_price,price);
	strcpy((*Goods[index]).good_discount,discount);
	(*Goods[index]).good_amount=amount;
	(*Goods[index]).good_remain=remain;
	
	Count++;

	printf("商品信息插入成功！\n");
	printf("\n");
}

int info_output(void)     //--------------------------------->该函数用于输出所有商品信息
{
	int i;
	
	printf("\n");
	printf("----------------All Goods-----------------\n");
	
	for(i=0;i<Count;i++)
	{
	         printf("%s",Goods[i]->good_id);
             printf("\t%s",Goods[i]->good_name);
             printf("\t%s",Goods[i]->good_price);
             printf("\t%s",Goods[i]->good_discount);
             printf("\t%d",Goods[i]->good_amount);
             printf("\t%d\n",Goods[i]->good_remain);
	}
	
	printf("------------------------------------------\n");
	printf("所有商品信息输出成功！\n");
	printf("\n");
}

int info_output2(int i)    //--------------------------------->该函数用于输出单个商品信息
{
	if(i==-1){
	    printf("您要查找的商品不存在！");
	}
	
	printf("%s",Goods[i]->good_id);
	printf("\t%s",Goods[i]->good_name);
	printf("\t%s",Goods[i]->good_price);
	printf("\t%s",Goods[i]->good_discount);
	printf("\t%d",Goods[i]->good_amount);
	printf("\t%d\n",Goods[i]->good_remain);
	printf("商品信息输出成功！\n");
	printf("\n");
}



int main(void)        //----------------------------->主函数，显示菜单，并根据用户的选择进行处理
{
    int m;
	char name[30];

	info_init();

	while(1){
	            printf("超市管理系统\n");
				printf("**************************\n");
				printf("1、初始化商品信息。\n");
				printf("2、商品信息的修改：\n");
				printf("3、删除某个商品信息：\n");
				printf("4、查找商品信息：\n");
				printf("5、插入某个商品信息：\n");
				printf("6、查看所有商品信息：\n");
				printf("7、保存并退出系统\n");
				printf("**************************\n");
				printf("请输入您的选择：\n");
				scanf("%d",&m);

				switch(m){
				    case 1:fflush(stdin);
						   Count=0;
						   info_init();
						   printf("商品信息初始化成功！\n");
						   printf("\n");
						   break;
				
					case 2:printf("请输入您要修改的商品名称：");
						   scanf("%s",name);
						   info_change(name);
						   break;
					
					case 3:printf("请输入您要删除的商品名称:");
				           scanf("%s",name);
				           info_dele(name);
				           break;
					
					case 4:printf("请输入您要查找的商品名称：");
						   scanf("%s",name);
						   info_output2(info_search(name));
						   break;
                    
					case 5:info_insert(Count);
						   break;
					
					case 6:info_output();
						   break;
					
					case 7:info_flush();
						   freeGoodInfo();
						   printf("信息已保存！\n已成功退出系统！\n");
						   exit(0);
				         }	
	       }
}

