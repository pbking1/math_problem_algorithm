#include<iostream>
using namespace std;
class Matrix
{
public:
	Matrix();
	virtual ~Matrix();
public:
	void M_Add(int m,int n,double *a,double *b,double *c);
	void M_Sub(int m,int n,double *a,double *b,double *c);
	void M_Tra(int m,int n,double *a,double *c);
	void M_Mul(double r,int m,int n,double *a,double *c);
	void M_Mul(int m,int s,int n,double *a,double *b,double *c);
	bool M_Inv(int n,double *a,double *c);
    
};



Matrix::Matrix()
{
    
}

Matrix::~Matrix()
{
    
}

void Matrix::M_Add(int m,int n,double *a,double *b,double *c)		//matrix add
{
	for(int i=0;i<m*n;i++)
		c[i]=a[i]+b[i];
}

void Matrix::M_Sub(int m,int n,double *a,double *b,double *c)		//matrix sub
{
	for(int i=0;i<m*n;i++)
		c[i]=a[i]-b[i];
}
void Matrix::M_Tra(int m,int n,double *a,double *c)					//matric 转置
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			c[j*m+i]=a[i*n+j];
	}
}

void Matrix::M_Mul(double r,int m,int n,double *a,double *c)		//matrix mul number
{
	for(int i=0;i<m*n;i++)
        c[i]=r*a[i];
}

void Matrix::M_Mul(int m,int s,int n,double *a,double *b,double *c)	//matrix mul
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			c[i*n+j]=0;
			for(int k=0;k<s;k++)
			{
				c[i*n+j]=c[i*n+j]+a[i*s+k]*b[k*n+j];
			}
		}
	}
}
bool Matrix::M_Inv(int n,double *a,double *c)
{
	
	double at;
	double bt;
	double am;
	int i,j,k;
	int tt;
	int N=2*n;
	double *p=new double[n*N];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			p[N*i+j]=a[n*i+j];
		}
		for(j=n;j<N;j++)
		{
			if(i==j-n)
				p[N*i+j]=1;
			else
				p[N*i+j]=0;
		}
	}
	
	for(k=0;k<n;k++)			//solve
	{
		at=fabs(p[N*k+k]);
		tt=k;
		for(j=k+1;j<n;j++)
		{
			bt=fabs(p[N*j+k]);
			if(at<bt)
			{
				at=bt;
				tt=j;
			}
		}
		if(tt!=k)
			for(j=k;j<N;j++)
			{
				am=p[N*k+j];
				p[N*k+j]=p[N*tt+j];
				p[N*tt+j]=am;
			}
        if(at<0.0001)
        {
            //this matrix 不可逆
            return false;
        }
        am=1/p[N*k+k];
        for(j=k;j<N;j++)
        {
            p[N*k+j]=p[N*k+j]*am;
        }
        
        for(i=0;i<n;i++)
        {
            if(k!=i)
            {
                am=p[N*i+k];
                for(j=0;j<N;j++)
                {
                    p[N*i+j]=p[N*i+j]-p[N*k+j]*am;
                }
            }
        }
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			c[n*i+j]=p[N*i+(j+n)];
    
    delete []p;
    
    
    return true;
}
