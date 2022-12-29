#include<stdio.h>
#include<math.h>
int main(){
    const int n=20;
    int i,f=1;
    double m=1,x,ans=0;
    scanf("%lf",&x);
    for (i=1;i<=n;i=i+2){
        ans+=f*pow(x,i)/m;
        m=m*(i+1)*(i+2);
        f=-f;
    }
    printf("sin(x)=%.2f",ans);
}