//采用重复平方的方法计算所有顶点对之间的最短路径

#include <stdio.h>
#include <limits.h>

/*#define N 9
int matrix[N][N]={{0      ,4      ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,8      ,INT_MAX},
                  {4      ,0      ,8      ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,11     ,INT_MAX},
                  {INT_MAX,8      ,0      ,7      ,INT_MAX,4      ,INT_MAX,INT_MAX,2      },
                  {INT_MAX,INT_MAX,7      ,0      ,9      ,14     ,INT_MAX,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,INT_MAX,9      ,0      ,10     ,INT_MAX,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,4      ,14     ,10     ,0      ,2      ,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,2      ,0      ,1      ,6      },
                  {8      ,11     ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,1      ,0      ,7      },
                  {INT_MAX,INT_MAX,2      ,INT_MAX,INT_MAX,INT_MAX,6      ,7      ,0      }
                 };
*/



#define N 5
int matrix[N][N]={{0      ,10     ,INT_MAX,INT_MAX,5      },
                  {INT_MAX,0      ,1      ,INT_MAX,2      },
                  {INT_MAX,INT_MAX,0      ,4      ,INT_MAX},
                  {7      ,INT_MAX,6      ,0      ,INT_MAX},
                  {INT_MAX,3      ,9      ,2      ,0      },
                 };

int add_infinite_support(int a,int b);
void repeating_squaing(int L[N][N] );
void extend_graph(int L[N][N], int L2[N][N]);
void print(int array[][N]);
void copyArray(int a[N][N],int b[N][N]);
int main(){
	repeating_squaing(matrix);
	return 0;
}

void repeating_squaing(int L[N][N] )
{
	int L2[N][N];
	int i=0;
	for(i=0;i<N;i++){
		extend_graph(L,L2);
		copyArray(L,L2);//将数组L2的内容拷贝到L中
		printf("\n");
		print(L2);
		printf("\n");
	}
	//print(L2);

	return;
}

/**
L是迭代前的矩阵，L2是迭代后的矩阵
**/
void extend_graph(int L[N][N], int L2[N][N]){
	int i,j,k;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			L2[i][j]=INT_MAX;//初始化为最大值
			for(k=0;k<N;k++){
				if( add_infinite_support(L[i][k],matrix[k][j]) < L2[i][j]){
					L2[i][j]=add_infinite_support(L[i][k],matrix[k][j]);
				}

			}
		}
	}
}

/**对加数为无穷大的情况进行处理，如果加数为无穷大，结果也返回无穷大**/
int add_infinite_support(int a,int b){
	if(a==INT_MAX || b==INT_MAX){
		return INT_MAX;
	}else{
		return a+b;
	}

}

void print(int array[][N])
{
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d ",array[i][j] );
		}
		printf("\n");
	}

}

//将数组b的内容复制到a中
void copyArray(int a[N][N],int b[N][N]){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			a[i][j]=b[i][j];
		}
	}
}