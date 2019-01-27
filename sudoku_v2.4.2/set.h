#include<iostream>
#include<cstdio>
#include<cmath>
#include<random>
#include<algorithm>
#include<chrono>
#include<string>
#include<cstdlib>
static int table[9][9]={0};//静态全局变量
static int board[9][9]={0};
static int trial[9][9]={0};
bool judge(int n,int i,int j)//判断是否有重复数字
{
    int m,k;
    bool t=true;
    for(m=0;m<9&&m!=j;m++)
    {
        if(table[i][m]==n)
            t=false;
    }
    if(t)
    {
        for(m=0;m<9&&m!=i;m++)
        {
            if(table[m][j]==n)
            t=false;
        }
        if(t)
        {
            for(m=i-i%3;m<=i-i%3+2;m++)
            {
                for(k=j-j%3;k<=j-j%3+2;k++)
                {
                    if(m==i&&k==j)
                    continue;
                    if(table[m][k]==n)
                        t=false;
                }
            }
        }
    }
    return t;
}
/*void printmap()//输出数独
{
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            std::cout<<table[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}*/
void init(int a[])//初始化第一行
{
    int i;
    for(i=0;i<9;i++)
        a[i]=i+1;//初始化第一行
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//调用系统时间作为种子
    shuffle(a,a+8,std::default_random_engine(seed));//将第一行顺序打乱
}

bool checkfull()//检查是否填满
{
    int i,j;
    for(i=1;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(table[i][j]==0)
                return false;
        }
    }
    return true;
}
void generatelines(int n)//最低效回溯法生成数独2-8行
{
    if(checkfull())
        {
            //printmap();
            return;
        }
    for(int i=1; i<10;i++)
    {
        table[n/9][n%9]=i;
        //std::cout<<table[(int)(n/9)][n%9];
        if(judge(i,n/9,n%9))
        {
            generatelines(n+1);
            if(checkfull())
                break;
        }
    }
    if(!checkfull())
        table[n/9][n%9]=0;
    return;
}


static int cnt=0;

void sudokusolve(int n=0)//求解数独并返回是否有唯一解
{
    if(checkfull())
        {
            //printmap();
            cnt++;
            return;
        }

    for(int i=1; i<10;i++)
    {
        if(trial[n/9][n%9]!=0)
            trial[n/9][n%9]=i;
        //std::cout<<table[(int)(n/9)][n%9];
        if(judge(i,n/9,n%9))
        {
            sudokusolve(n+1);
        }
    }
    trial[n/9][n%9]=0;
    return;
}

bool only()
{
    if(cnt==1)
        return true;
    return false;
}

void Show(int n,int board[9][9],int sudoku[9][9])//挖空产生数独题目
{
	time_t seed;
	srand(time(&seed));
	int i,j;
	for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            board[i][j]=sudoku[i][j];
        }
    }
    i=0;
	while(i<n)
        {
            int m=rand()%9,n=rand()%9;
            board[m][n]=0;
            i++;
		}
	}

void sudokugenerate()//产生数独终盘
{

    init(table[0]);//将第一行打乱初始化
    generatelines(9);
    do
    {
        Show(70,trial,table);
        sudokusolve(0);
    }while(!only());
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(trial[i][j]!=0)
            {
                board[i][j]=trial[i][j];
            }
        }
    }

}

/*int main()
{
    //初始化
    system("title sudoku");
    system("mode con cols=63 lines=32");

    //生成数独终盘
    sudokugenerate();
    //选择数度难度
    std::cout<<"Please input 1,2,3 to select the level:"<<std::endl;
    int n;
    std::cin>>n;
    //挖空并判断生成的题目是否有唯一解
    int d;
    switch(n)
    {
        case 1: d=55;
                break;
        case 2: d=60;
                break;
        case 3: d=65;
                break;
    }

    //输出生成的数独题目
    std::cout<<std::endl;
    sudokusolve(board);
    if(only())
    {
        int i,j;
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                if(board[i][j]==0)
                    std::cout<<"  ";
                else
                    std::cout<<board[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
    else{
        sudokugenerate();
    }
    std::cout<<std::endl;
    std::cout<<"Enter \"answer\" to check the answer."<<std::endl;

    std::string a;
    std::cin>>a;
    if(a=="answer")
    {
        std::cout<<std::endl;
        printmap();
    }


    return 0;
}*/
