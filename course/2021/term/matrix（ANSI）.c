#include<stdio.h>
#include<math.h>
#define matrix_num 5
#define row 10
#define column 10
void input(int *p,int m,int n){
    int i,j;
    for(i=0;i<m;i++){
        for (j=0;j<n;j++){
            scanf("%d",&*p);
            p++;
        }
        p+=10-n;
    }
}
void output(int *p,int m,int n){
    int i,j;
    for(i=0;i<m;i++){
        for (j=0;j<n;j++){
            printf("%d\t",*p);
            p++;
        }
        printf("\n");
        p+=10-n;
    }
}
void add(int *px,int *py,int TEMP[row][column],int r,int c){
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){					 
                TEMP[i][j]=*(px+i*column+j) + *(py+i*column+j); 
		}
	}
}
void multi(int *px,int *py,int TEMP[row][column],int r,int c,int rc){
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
            TEMP[i][j]=0;
			for(int k=0;k<rc;k++){					 
                TEMP[i][j]+=*(px+i*column+k) * *(py+k*column+j); 
			}
		}
	}
}
int determinant(int matrix[row][column],int order)
{
    int laplace_expansion(int matrix[row][column],int r,int c,int order);
    int result = 0,sign = 1,cofactor,i;
    
    if(order == 1)
        result = matrix[0][0];
    else
    	for(i = 0;i < order;i ++)
        {
            cofactor = laplace_expansion(matrix,i,0,order);
            result += sign * matrix[i][0] * cofactor;
            sign *= -1;
        }
 
    return result;
}
int laplace_expansion(int matrix[row][column],int r,int c,int order)
{
    int result = 0,cofactor[row][column],original_i,original_j,i,j;
    
    for(i = 0;i < order;i ++)
        for(j = 0;j < order;j ++)
        {
            original_i = i;
            original_j = j;
            if(i == r || j == c);
            else
            {
                if(i > r)
                    i --;
                if(j > c)
                    j --;
                cofactor[i][j] = matrix[original_i][original_j];
                i = original_i;
                j = original_j;
            }
        }
    if(order >= 2)
        result = determinant(cofactor,order - 1);
    
    return result;
}
int cofactor(int matrix[row][column],int order,int r,int c)
{
    int result = 0,cofactor[row][column];
    int original_i,original_j,i,j;
    
    for(i = 0;i < order;i ++)
        for(j = 0;j < order;j ++)
        {
            original_i = i;
            original_j = j;
            if(i == r || j == c);
            else
            {
                if(i > r)
                    i --;
                if(j > c)
                    j --;
                cofactor[i][j] = matrix[original_i][original_j];
                i = original_i;
                j = original_j;
            }
        }
    if(order >= 2)
        result = determinant(cofactor,order - 1);
    
    return result;
}

int adjugate_matrix(int matrix[row][column],int order,int r,int c)
{
    int result = 0;

    if(order == 1 && r == 0 && c == 0)
        result = 1;
    else
        result = pow(-1,r + c) * cofactor(matrix,order,c,r);
    
    return result;
}
int inverse_matrix(int matrix[row][column],int order,int r,int c)
{
    int result = 0;
    
    result = adjugate_matrix(matrix,order,r,c) / determinant(matrix,order);
    
    return result;
}

int main(){
    int A[row][column],B[row][column],C[row][column],D[row][column],E[row][column],TEMP[row][column]/*????????????*/;
    int *px,*py;/*????????*/
    int i,j,c,r,ans,order;
    char op;/*??????*/
    int m0=0,n0=0,m1=0,n1=0,m[matrix_num+1],n[matrix_num+1];/*m????????n??????,0-4??????A-E,5??TEMP*/
    char name,name0;/*name????????*/
    printf("????????????????????????????????????????????????????????\n");
    printf("1.????????????\n");
    printf("2.????????\n");
    printf("3.????????\n");
    printf("4.??????????\n");
    printf("5.????????\n");
    printf("6.????????\n");
    printf("7.??????????\n");
    printf("@.????????????\n");
    printf("?.??????????????\n");
    printf("#.????\n");
    printf("????????????????");
while (op!='#')
{    
    op=getchar();
    getchar();
    switch (op)
    {
    case '1':
        {
            printf("??????\"1.????????????\"\n");
            printf("??????????[??????(A??B??C??D??E)] [????*????]??????????????????<????????>??????<????>????:\n");
            scanf("%c %d*%d",&name,&m0,&n0);
            getchar();
            printf("%c??%d*%d??????\n",name,m0,n0);
            printf("??????????????????????:\n");
            switch (name)
            {
            case 'A':
                px=&A[0][0];m[0]=m0;n[0]=n0;
                break;
            case 'B':
                px=&B[0][0];m[1]=m0;n[1]=n0;
                break;
            case 'C':
                px=&C[0][0];m[2]=m0;n[2]=n0;
                break;
            case 'D':
                px=&D[0][0];m[3]=m0;n[3]=n0;
                break;
            case 'E':
                px=&E[0][0];m[4]=m0;n[4]=n0;
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            input(px,m0,n0);
            printf("??????????????%c??\n",name);
            getchar();
            printf("??????????????????????");
        }
        break;
    case '2':
        {
            printf("??????\"2.????????\"\n");
            printf("????????????????????????[??????]+[??????]??????\n");
            scanf("%c+%c",&name,&name0);
            getchar();
            switch (name)
            {
            case 'A':
                px=&A[0][0];m0=m[0];n0=n[0];
                break;
            case 'B':
                px=&B[0][0];m0=m[1];n0=n[1];
                break;
            case 'C':
                px=&C[0][0];m0=m[2];n0=n[2];
                break;
            case 'D':
                px=&D[0][0];m0=m[3];n0=n[3];
                break;
            case 'E':
                px=&E[0][0];m0=m[4];n0=n[4];
                break;
            case 'T':
                px=&TEMP[0][0];m0=m[5];n0=n[5];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            switch (name0)
            {
            case 'A':
                py=&A[0][0];m1=m[0];n1=n[0];
                break;
            case 'B':
                py=&B[0][0];m1=m[1];n1=n[1];
                break;
            case 'C':
                py=&C[0][0];m1=m[2];n1=n[2];
                break;
            case 'D':
                py=&D[0][0];m1=m[3];n1=n[3];
                break;
            case 'E':
                py=&E[0][0];m1=m[4];n1=n[4];
                break;
            case 'T':
                py=&TEMP[0][0];m1=m[5];n1=n[5];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            if (m0!=m1 || n0!=n1) printf("????????????????\n");
            else {
                m[5]=m0,n[5]=n1;
                add(px,py,TEMP,m0,n0);
                printf("??????????????TEMP??????\n");
                px=&TEMP[0][0];m0=m[5];n0=n[5];
                printf("TEMP??%d*%d??????\n",m0,n0);
                output(px,m0,n0);
            }
            printf("??????????????????????");
        }
        break;
    case '3':
        {
            printf("??????\"3.????????\"\n");
            printf("????????????????????????[??????]*[??????]??????\n");
            scanf("%c*%c",&name,&name0);
            getchar();
            switch (name)
            {
            case 'A':
                px=&A[0][0];m0=m[0];n0=n[0];
                break;
            case 'B':
                px=&B[0][0];m0=m[1];n0=n[1];
                break;
            case 'C':
                px=&C[0][0];m0=m[2];n0=n[2];
                break;
            case 'D':
                px=&D[0][0];m0=m[3];n0=n[3];
                break;
            case 'E':
                px=&E[0][0];m0=m[4];n0=n[4];
                break;
            case 'T':
                px=&TEMP[0][0];m0=m[5];n0=n[5];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            switch (name0)
            {
            case 'A':
                py=&A[0][0];m1=m[0];n1=n[0];
                break;
            case 'B':
                py=&B[0][0];m1=m[1];n1=n[1];
                break;
            case 'C':
                py=&C[0][0];m1=m[2];n1=n[2];
                break;
            case 'D':
                py=&D[0][0];m1=m[3];n1=n[3];
                break;
            case 'E':
                py=&E[0][0];m1=m[4];n1=n[4];
                break;
            case 'T':
                py=&TEMP[0][0];m1=m[5];n1=n[5];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            if (n0!=m1) printf("????????????????\n");
            else {
                m[5]=m0,n[5]=n1;
                multi(px,py,TEMP,m0,n1,n0);
                printf("??????????????TEMP??????\n");
                px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP??%d*%d??????\n",m0,n0);
            output(px,m0,n0);
            }
            printf("??????????????????????");
        }
        break;
    case '4':
        {
            printf("??????\"4.??????????\"\n");
            printf("??????[??????(A??B??C??D??E)]??<????>????:\n");
            scanf("%c",&name);
            getchar();
            switch (name)
            {
            case 'A':
                px=&A[0][0];m0=m[0];n0=n[0];
                break;
            case 'B':
                px=&B[0][0];m0=m[1];n0=n[1];
                break;
            case 'C':
                px=&C[0][0];m0=m[2];n0=n[2];
                break;
            case 'D':
                px=&D[0][0];m0=m[3];n0=n[3];
                break;
            case 'E':
                px=&E[0][0];m0=m[4];n0=n[4];
                break;
            case 'T':
                px=&TEMP[0][0];m0=m[5];n0=n[5];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            m[5]=n0;n[5]=m0;
            for (i=0;i<m0;i++){
                for (j=0;j<n0;j++){
                    TEMP[j][i]=*(px+i*column+j);
                }
            }
            printf("??????????????TEMP??????\n");
            px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP??%d*%d??????\n",m0,n0);
            output(px,m0,n0);
            printf("??????????????????????");
        }
        break;
    case '5':
        {
            printf("??????\"5.????????\"\n");
            printf("??????[??????(A??B??C??D??E)]??<????>????:\n");
            scanf("%c",&name);
            getchar();
            switch (name)
            {
            case 'A':
                m0=m[0];n0=n[0];
                break;
            case 'B':
                m0=m[1];n0=n[1];
                break;
            case 'C':
                m0=m[2];n0=n[2];
                break;
            case 'D':
                m0=m[3];n0=n[3];
                break;
            case 'E':
                m0=m[4];n0=n[4];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            if (m0!=n0) printf("??????????????????????????????\n");
            else{
                order=n0;
                m[5]=order;n[5]=order;
                switch (name)
            {
            case 'A':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=inverse_matrix(A,order,i,j);
                    }
                }                
                break;
            case 'B':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=inverse_matrix(B,order,i,j);
                    }
                }
                break;
            case 'C':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=inverse_matrix(C,order,i,j);
                    }
                }
                break;
            case 'D':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=inverse_matrix(D,order,i,j);
                    }
                }
                break;
            case 'E':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=inverse_matrix(E,order,i,j);
                    }
                }
                break;
            default:
                printf("??????????????????\n");
                break;
                }
            printf("??????????????????????TEMP??\n");
            px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP??%d*%d??????\n",m0,n0);
            output(px,m0,n0);
            }
            printf("??????????????????????");
        }
        break;
    case '6':
        {
            printf("??????\"6.????????\"\n");
            printf("??????[??????(A??B??C??D??E)]??<????>????:\n");
            scanf("%c",&name);
            getchar();
            switch (name)
            {
            case 'A':
                m0=m[0];n0=n[0];
                break;
            case 'B':
                m0=m[1];n0=n[1];
                break;
            case 'C':
                m0=m[2];n0=n[2];
                break;
            case 'D':
                m0=m[3];n0=n[3];
                break;
            case 'E':
                m0=m[4];n0=n[4];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            if (m0!=n0) printf("??????????????????????????????\n");
            else{
                int order=n0;
                int ans;
                switch (name)
            {
            case 'A':
                ans = determinant(A,order);
                break;
            case 'B':
                ans = determinant(B,order);
                break;
            case 'C':
                ans = determinant(C,order);
                break;
            case 'D':
                ans = determinant(D,order);
                break;
            case 'E':
                ans = determinant(E,order);
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            printf("%c??????????%d\n",name,ans);
            }
            printf("??????????????????????");
        }
        break;
    case '7':
        {
            printf("??????\"7.??????????\"\n");
            printf("??????[??????(A??B??C??D??E)]??<????>????:\n");
            scanf("%c",&name);
            getchar();
            switch (name)
            {
            case 'A':
                m0=m[0];n0=n[0];
                break;
            case 'B':
                m0=m[1];n0=n[1];
                break;
            case 'C':
                m0=m[2];n0=n[2];
                break;
            case 'D':
                m0=m[3];n0=n[3];
                break;
            case 'E':
                m0=m[4];n0=n[4];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            if (m0!=n0) printf("????????????????????????????????\n");
            else{
                order=n0;
                m[5]=order;n[5]=order;
                switch (name)
            {
            case 'A':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=adjugate_matrix(A,order,i,j);
                    }
                }                
                break;
            case 'B':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=adjugate_matrix(B,order,i,j);
                    }
                }
                break;
            case 'C':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=adjugate_matrix(C,order,i,j);
                    }
                }
                break;
            case 'D':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=adjugate_matrix(D,order,i,j);
                    }
                }
                break;
            case 'E':
                for(i = 0;i < order;i ++){
                    {
                        for(j = 0;j < order;j ++)
                            TEMP[i][j]=adjugate_matrix(E,order,i,j);
                    }
                }
                break;
            default:
                printf("??????????????????\n");
                break;
                }
            printf("??????????????????????TEMP??\n");
            px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP??%d*%d??????\n",m0,n0);
            output(px,m0,n0);
            }
            printf("??????????????????????");
        }
        break;
    case '?':
        {
    printf("1.????????????\n");
    printf("2.????????\n");
    printf("3.????????\n");
    printf("4.??????????\n");
    printf("5.????????\n");
    printf("6.????????\n");
    printf("7.??????????\n");
    printf("@.????????????\n");
    printf("?.??????????????\n");
    printf("#.????\n");
    printf("????????????????");
        }
        break;
    case '@':
        {
            printf("??????\"@.????????????\"\n");
            printf("??????????????????????(TEMP??T????)\n");
            scanf("%c",&name);
            getchar();
            switch (name)
            {
            case 'A':
                px=&A[0][0];m0=m[0];n0=n[0];
                break;
            case 'B':
                px=&B[0][0];m0=m[1];n0=n[1];
                break;
            case 'C':
                px=&C[0][0];m0=m[2];n0=n[2];
                break;
            case 'D':
                px=&D[0][0];m0=m[3];n0=n[3];
                break;
            case 'E':
                px=&E[0][0];m0=m[4];n0=n[4];
                break;
            case 'T':
                px=&TEMP[0][0];m0=m[5];n0=n[5];
                break;
            default:
                printf("??????????????????\n");
                break;
            }
            printf("%c??%d*%d??????\n",name,m0,n0);
            printf("%c??%d*%d??????\n",name,m0,n0);
            output(px,m0,n0);
            printf("??????????????????????");
        }
        break;
    case '#':
        {
            printf("??????");
        }
        break;
            
    default:
        printf("????????????????????\n");
        printf("??????????????????????");
        break;
    }
}
return 0;
}