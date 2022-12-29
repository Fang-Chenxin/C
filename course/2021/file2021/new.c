#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    FILE *fp;                  	/* 定义文件指针*/
    if( ( fp = fopen("f1.txt", "w") ) == NULL){	/* 打开文件 */
   	    printf("File open error!\n");
   	    exit(0);
    }
	fprintf( fp, "%s", "Hello World! " );   	/* 写文件 */    
    	if( fclose( fp ) ){	
        printf( "Can not close the file!\n" );
        exit(0);    }
    return 0;}
