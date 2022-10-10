#include<stdio.h>
#include <stdlib.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/asn1.h>
#include <openssl/x509_vfy.h>

//para a bibliotaca lcrypto
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

void get_certificate(char *path);
void validate_certificate(char *path);

int main(void) {
    char *path = "/home/henrique_buzin/Documentos/bry-tecnologia/certificado-ac-raiz-bry-v3.crt";
    validate_certificate(path);
}

void validate_certificate(char *path){

    char *filename = strrchr(path, '/');
    char *extension = strrchr(filename, '.');   
    if(!extension || extension == filename) {fputs ("AFile error",stderr); exit (1);}
    
    if(!strcmp(extension, ".crt")){ 
        char *c1 = "openssl x509 -in ../certificado-ac-raiz-bry-v3.crt -out ../certificado-ac-raiz-bry-v3.pem -outform PEM";
        system(c1);
    }
    
    //get_certificate(path);

}

void get_certificate(char *path){
    printf("%s", path);

    FILE * file;
    file = fopen(path, "rb");
    if (file==NULL) {fputs ("AFile error",stderr); exit (2);}

    long long unsigned int tamanho;
    fseek(file, 0 , SEEK_END);
    tamanho = ftell(file);
    rewind(file);

    unsigned char * buffer;
    buffer = (unsigned char*) malloc (sizeof(unsigned char)*(tamanho+1));
    if (buffer == NULL) {fputs ("BMemory error",stderr); exit (3);}

    int result;
    result = fread(buffer,1,tamanho,file);
    if (result != tamanho) {fputs ("CReading error",stderr); exit (4);}

    X509 *x; 
    x = d2i_X509(NULL, (const unsigned char **)&buffer,result);
    if (x == NULL){fputs ("DReading error",stderr); exit (5);}

    X509_NAME* subject = X509_get_subject_name(x);
    
    char *resultado;
    resultado= (char*) malloc (sizeof(char)*(result+1));
    resultado = X509_NAME_oneline(subject,buffer,result);
    
    printf("%s \n", resultado);
    
    fclose (file);
    free (buffer);

}
