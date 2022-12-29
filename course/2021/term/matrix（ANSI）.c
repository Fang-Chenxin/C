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
    int A[row][column],B[row][column],C[row][column],D[row][column],E[row][column],TEMP[row][column]/*��ʱ��������*/;
    int *px,*py;/*����ָ��*/
    int i,j,c,r,ans,order;
    char op;/*������*/
    int m0=0,n0=0,m1=0,n1=0,m[matrix_num+1],n[matrix_num+1];/*mΪ������nΪ����,0-4����ΪA-E,5ΪTEMP*/
    char name,name0;/*nameΪ������*/
    printf("��������������������ʮ�����ھ�����㡪������������������\n");
    printf("1.���������ֵ\n");
    printf("2.����ӷ�\n");
    printf("3.����˷�\n");
    printf("4.��ת�þ���\n");
    printf("5.�������\n");
    printf("6.������ʽ\n");
    printf("7.��������\n");
    printf("@.��ʾ������ֵ\n");
    printf("?.�ٴ���ʾ�˲˵�\n");
    printf("#.�˳�\n");
    printf("������������ţ�");
while (op!='#')
{    
    op=getchar();
    getchar();
    switch (op)
    {
    case '1':
        {
            printf("��ѡ��\"1.���������ֵ\"\n");
            printf("����������[������(A��B��C��D��E)] [����*����]�Զ�������С����<�����ַ�>������<�س�>ȷ��:\n");
            scanf("%c %d*%d",&name,&m0,&n0);
            getchar();
            printf("%c��%d*%d�ľ���\n",name,m0,n0);
            printf("�����밴������������ֵ:\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            input(px,m0,n0);
            printf("�ѽ��������뵽%c��\n",name);
            getchar();
            printf("��������һ��������ţ�");
        }
        break;
    case '2':
        {
            printf("��ѡ��\"2.����ӷ�\"\n");
            printf("��������Ҫ��ӵľ��󣬰�[������]+[������]���룺\n");
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
                printf("��������Ч�ľ�����\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            if (m0!=m1 || n0!=n1) printf("�����������ӷ�\n");
            else {
                m[5]=m0,n[5]=n1;
                add(px,py,TEMP,m0,n0);
                printf("�ѽ���������TEMP������\n");
                px=&TEMP[0][0];m0=m[5];n0=n[5];
                printf("TEMP��%d*%d�ľ���\n",m0,n0);
                output(px,m0,n0);
            }
            printf("��������һ��������ţ�");
        }
        break;
    case '3':
        {
            printf("��ѡ��\"3.����˷�\"\n");
            printf("��������Ҫ��˵ľ��󣬰�[������]*[������]���룺\n");
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
                printf("��������Ч�ľ�����\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            if (n0!=m1) printf("�����������˷�\n");
            else {
                m[5]=m0,n[5]=n1;
                multi(px,py,TEMP,m0,n1,n0);
                printf("�ѽ���������TEMP������\n");
                px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP��%d*%d�ľ���\n",m0,n0);
            output(px,m0,n0);
            }
            printf("��������һ��������ţ�");
        }
        break;
    case '4':
        {
            printf("��ѡ��\"4.��ת�þ���\"\n");
            printf("������[������(A��B��C��D��E)]��<�س�>ȷ��:\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            m[5]=n0;n[5]=m0;
            for (i=0;i<m0;i++){
                for (j=0;j<n0;j++){
                    TEMP[j][i]=*(px+i*column+j);
                }
            }
            printf("�ѽ���������TEMP������\n");
            px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP��%d*%d�ľ���\n",m0,n0);
            output(px,m0,n0);
            printf("��������һ��������ţ�");
        }
        break;
    case '5':
        {
            printf("��ѡ��\"5.�������\"\n");
            printf("������[������(A��B��C��D��E)]��<�س�>ȷ��:\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            if (m0!=n0) printf("��������������ȣ������������\n");
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
                printf("��������Ч�ľ�����\n");
                break;
                }
            printf("�ѽ�����������������TEMP��\n");
            px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP��%d*%d�ľ���\n",m0,n0);
            output(px,m0,n0);
            }
            printf("��������һ��������ţ�");
        }
        break;
    case '6':
        {
            printf("��ѡ��\"6.������ʽ\"\n");
            printf("������[������(A��B��C��D��E)]��<�س�>ȷ��:\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            if (m0!=n0) printf("��������������ȣ�����������ʽ\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            printf("%c������ʽ��%d\n",name,ans);
            }
            printf("��������һ��������ţ�");
        }
        break;
    case '7':
        {
            printf("��ѡ��\"7.��������\"\n");
            printf("������[������(A��B��C��D��E)]��<�س�>ȷ��:\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            if (m0!=n0) printf("��������������ȣ�������������\n");
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
                printf("��������Ч�ľ�����\n");
                break;
                }
            printf("�ѽ�����������������TEMP��\n");
            px=&TEMP[0][0];m0=m[5];n0=n[5];
            printf("TEMP��%d*%d�ľ���\n",m0,n0);
            output(px,m0,n0);
            }
            printf("��������һ��������ţ�");
        }
        break;
    case '?':
        {
    printf("1.���������ֵ\n");
    printf("2.����ӷ�\n");
    printf("3.����˷�\n");
    printf("4.��ת�þ���\n");
    printf("5.�������\n");
    printf("6.������ʽ\n");
    printf("7.��������\n");
    printf("@.��ʾ������ֵ\n");
    printf("?.�ٴ���ʾ�˲˵�\n");
    printf("#.�˳�\n");
    printf("������������ţ�");
        }
        break;
    case '@':
        {
            printf("��ѡ��\"@.��ʾ������ֵ\"\n");
            printf("��������Ҫ����ľ�����(TEMP��T����)\n");
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
                printf("��������Ч�ľ�����\n");
                break;
            }
            printf("%c��%d*%d�ľ���\n",name,m0,n0);
            printf("%c��%d*%d�ľ���\n",name,m0,n0);
            output(px,m0,n0);
            printf("��������һ��������ţ�");
        }
        break;
    case '#':
        {
            printf("���˳�");
        }
        break;
            
    default:
        printf("��������ȷ���������\n");
        printf("��������һ��������ţ�");
        break;
    }
}
return 0;
}