#include <stdio.h>
#define ROWS 68

#define IMPL5

#ifdef IMPL5
typedef unsigned __int128 mytype;
#else
typedef unsigned long long int mytype;
#endif

#if defined(IMPL1) || defined(IMPL2)
mytype range_mult(int a, int b)
{
    mytype res = 1;
    
    if ((a<=0)||(a>b)) return 1;
    
    for (mytype i=a;i<=b;i++) res*=i;
    
    return res;
}

mytype factorial(int n)
{
    if (n<2) return 1;
    
    return range_mult(2,n);
}
#endif

#ifdef IMPL1
mytype n_choose_k(int n, int k)
{
    return factorial(n)/(factorial(n-k)*factorial(k));
}
#endif




#ifdef IMPL2
mytype n_choose_k(int n, int k)
{
    return range_mult(k+1,n)/factorial(n-k);
}

#endif

#ifdef IMPL3

mytype n_choose_k(int n, int k)
{
    mytype result = 1;
    int fact_den = n-k;
    
    if ((n<=0) || (k<=0) || (k>=n)) return 1;
    if (k==1) return n;
    
    
    for (int q=n;q>k;q--)
    {
        if ((fact_den>1) && ((q%fact_den)==0)) result *= q / (fact_den--);
        else result*=q;
    }
    
    for (int q=fact_den;q>1;q--) result /= q;
    
    return result;
}
#endif

#if defined(IMPL4) || defined(IMPL5)
mytype n_choose_k(int n, int k)
{
    mytype result = 1;
    int found = 0;
    int fact_den[n-k-1];
    int j=0;
    
    if ((n<=0) || (k<=0) || (k>=n)) return 1;
    if (k==1) return n;
    
    for (int i = 2;i<=n-k;i++)
    {
        fact_den[j++] = i;
    }   
    
    for (int q=n;q>k;q--)
    {
        found = 0;
        for (int j=0;j<n-k-1;j++)
        {
            if (found>0) continue;
            if ((fact_den[j]>0) && (q%fact_den[j]==0))
            {
                found = fact_den[j];
                fact_den[j] = 0;
            }
        }
        
        result *= (found==0?q:(q/found));
    }
    
    for (int j=0;j<n-k-1;j++)
    {
        if (fact_den[j] > 0) result/=fact_den[j];
    } 
    
    return result;
}

#endif

int main()
{
    
    int r,c,l;
    
    for (r=ROWS-1;r>=0;r--)
    {
        for (l=r;l<ROWS;l++) printf("  ");
        
        for (c=0;c<=r;c++)
        {
            printf("%llu    ",n_choose_k(r,c));
        }
        
        printf("\n");
    }
    

    return 0;
}
