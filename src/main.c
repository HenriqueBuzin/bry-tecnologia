#include <stdio.h>
#include <stdlib.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/asn1.h>
#include <openssl/x509_vfy.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

void get_certificate(char *path);
void validate_certificate(char *path);

int main(int argc, char **argv) {
    char *path = argv[1];
    validate_certificate(path);
}

void validate_certificate(char *path){

    if(!strcmp(strrchr(path, '.'), ".pem")){ 
	char s1[] = "openssl x509 -in ";
        char s2[] = " -out certificate_aux.der -outform DER";

	int lenght = strlen(s1) + strlen(path) + strlen(s2);
	
	char *str = (char*) malloc (sizeof(char*)*(lenght+1));

	
	strcpy(str, s1);
	strcat(str, path);
        strcat(str, s2);
        printf("%s\n", str);
        
        
        system(str);
    }
    
  
    
    get_certificate("certificate_aux.der");

}

void get_certificate(char *path){

    FILE * file;
    long long unsigned int lenght;
    unsigned char * buffer;
    int result;
    char *resultado;
    
    file = fopen(path, "rb");
    if (file==NULL) {fputs ("File error",stderr); exit (2);}

    
    fseek(file, 0 , SEEK_END);
    lenght = ftell(file);
    rewind(file);

    buffer = (unsigned char*) malloc (sizeof(unsigned char)*(lenght+1));
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (3);}

    result = fread(buffer,1,lenght,file);
    if (result != lenght) {fputs ("Reading error",stderr); exit (4);}

    X509 *x; 
    x = d2i_X509(NULL, (const unsigned char **)&buffer,result);
    if (x == NULL){fputs ("Reading error",stderr); exit (5);}

    X509_NAME* subject = X509_get_subject_name(x);
    
    resultado= (char*) malloc (sizeof(char)*(result+1));
    resultado = X509_NAME_oneline(subject,buffer,result);
    
    printf("%s \n", resultado);
    
    fclose (file);
    
    if (remove("certificate_aux.der") == 0) {
        printf("The file is deleted successfully.");
    } else {
        printf("The file is not deleted.");
    }
    
    free (buffer);
    
}
