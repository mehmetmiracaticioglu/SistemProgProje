#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include "jval.h"
#define MAX_SIZE 500
char* foo(int baslangic,int bitis,char *s){
	char *ptr = malloc(sizeof(char)*(bitis-baslangic));
	int i,j =0;
	for (i = baslangic; i < bitis; ++i)
	{
		if (s[i]!= '"')
		{
			ptr[j] = s[i];
			j++;
		}
	}
	return ptr;
}
JRB fill_jrb(){
    Jval val;
    IS is;
    JRB b,bn;
    char *arr,*arr1;
    int i,satir=0,j=0;
    b = make_jrb();
    is = new_inputstruct(".kilit");
    if (is == NULL) {
        perror("/.kilit");
        exit(1);
    }
    
    while(get_line(is) >= 0){
    	satir++;
    }
     is = new_inputstruct(".kilit");
    if (is == NULL) {
        perror("/.kilit");
        exit(1);
    }

    while(get_line(is) >= 0) {
		for (i = 0; i < is->NF; i++) {
     		if (j != 0 && j != satir-1)
     		{
                val = new_jval_s(is->fields[i]);
                if (j == satir-2)
                {
                	val.s = foo(1,strlen(val.s)-1,val.s);
                }
                if (j != satir-2){
                	val.s = foo(1,strlen(val.s)-2,val.s);
                }
                if (i % 2 == 0 ) // kelime
                {
                	arr = malloc(sizeof(char)*strlen(val.s));
                	strcpy(arr,val.s);
                	
                }
                if (i % 2 == 1 ) // sayi;
                {
                	arr1 = malloc(sizeof(char)*strlen(val.s));
                	strcpy(arr1,val.s);
                	(void) jrb_insert_str(b, strdup(arr), new_jval_s(arr1));
                }
     		}
     	}
     	j++;
     }
	
    jettison_inputstruct(is);
    return b;
}

void encripted(const char *giris_metin , const char *cikis_metin){
	//printf("geldik lo");encripted
    IS is;
	int i,j,size=0;
	FILE *fp = fopen(cikis_metin,"w+");
	char input_metin[MAX_SIZE][20];
	JRB bn;
    JRB b = fill_jrb();
	is = new_inputstruct(giris_metin);
	if (is == NULL) {
		perror(giris_metin);
		exit(1);
	}

	while(get_line(is) >= 0) {
		for (i = 0; i < is->NF; i++) {
	  		if (size >= MAX_SIZE)
			{
				printf("500 kelimeden fazla input ..!\n");
				return;
			}
			else{
		  		strcpy(input_metin[size],is->fields[i]);
		  		size++;
			}
		}
	}
	for (i = 0; i < size; ++i)
	{
		bn = jrb_find_str(b, input_metin[i]) ;
		if (bn != NULL )
		{
			//printf("%s ",jval_s(bn->val));
			fprintf(fp,"%s ", jval_s(bn->val));
		}
		else{
			fprintf(fp,"%s ", input_metin[i]);
		}
	}
}

void descripted(const char *giris_metin , const char *cikis_metin){
	IS is;
	int i,j,size=0;
	FILE *fp = fopen(cikis_metin,"w+");
	char input_metin[MAX_SIZE][20];
	JRB bn,ptr;
    JRB b = fill_jrb();
  
	is = new_inputstruct(giris_metin);
	if (is == NULL) {
	perror(giris_metin);
	exit(1);
	}
	while(get_line(is) >= 0) {
		for (i = 0; i < is->NF; i++) {
	  		if (size >= MAX_SIZE)
			{
				printf("500 kelimeden fazla input ..!\n");
				return;
			}
			else{
		  		strcpy(input_metin[size],is->fields[i]);
		  		size++;
			}
		}
	}
	int flag=0;

	for (i = 0; i < size; ++i)
	{
		flag=0;
		for(ptr = jrb_first(b); ptr != jrb_nil(b); ptr = jrb_next(ptr)){
			if(strcmp(input_metin[i],jval_s(ptr->val)) == 0){
				fprintf(fp,"%s ", jval_s(ptr->key));
				flag=1;
			}

		}
		if (flag!=1)
		{
			fprintf(fp,"%s ", input_metin[i]);
		}
		

	}
}
int main(int argc, char const *argv[]){
    if (argc != 4)
    {
    	printf("Eksik arguman..!\n");
    	printf("$>./kripto -d giriş_metin cikis_metin\n");
    }
    else{
    	if (strcmp(argv[0],"./kripto")!=0)
    	{
    		printf("Hatali arguman..!\n");
    		printf("$>./kripto -d giriş_metin cikis_metin\n");	
    	}
    	else{
    		if (strcmp(argv[1],"-d")==0)
    		{
    			descripted(argv[2],argv[3]);
    		}
    		else if(strcmp(argv[1],"-e")==0)
    		{
    			encripted(argv[2],argv[3]);
    		}
    		else{
    			printf("Hatali arguman..!\n");
    			printf("$>./kripto -d giriş_metin cikis_metin\n");
    		}
    	}
    }
       
}
