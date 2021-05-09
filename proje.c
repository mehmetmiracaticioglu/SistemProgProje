#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include "jval.h"
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
void fill_jrb(){
    Jval val;
    IS is;
    JRB b,bn;
    char *arr,*arr1;
    int i,satir=0,j=0;
    b = make_jrb();
    is = new_inputstruct("ornek2/.kilit");
    if (is == NULL) {
        perror("ornek2/.kilit");
        exit(1);
    }
    
    while(get_line(is) >= 0){
    	satir++;
    }
     is = new_inputstruct("ornek2/.kilit");
    if (is == NULL) {
        perror("ornek2/.kilit");
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
	jrb_traverse(bn, b) {
	    printf("%s %s\n", jval_s(bn->key),jval_s(bn->val));
	  }
    jettison_inputstruct(is);
}

void descripted(const char *giris_metin , const char *cikis_metin){
    fill_jrb();
    printf("ddd\n");
}
void encripted(const char *giris_metin , const char *cikis_metin){
	printf("eee\n");
}
int main(int argc, char const *argv[]){
    if (argc != 5)
    {
    	printf("Eksik arguman..!\n");
    	printf("$>./exe kripto -d giriş_metin cikis_metin\n");
    }
    else{
    	if (strcmp(argv[1],"kripto")!=0)
    	{
    		printf("Hatali arguman..!\n");
    		printf("$>./exe kripto -d giriş_metin cikis_metin\n");	
    	}
    	else{
    		if (strcmp(argv[2],"-d")==0)
    		{
    			descripted(argv[3],argv[4]);
    		}
    		else if(strcmp(argv[2],"-e")==0)
    		{
    			encripted(argv[3],argv[4]);
    		}
    		else{
    			printf("Hatali arguman..!\n");
    			printf("$>./exe kripto -d giriş_metin cikis_metin\n");
    		}
    	}
    }
       

#include "jrb.h"
#include "fields.h"

int main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
  }

  jrb_rtraverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }

}