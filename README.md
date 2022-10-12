# bry-tecnologia
 Teste para Estágio na BRY Tecnologia
 
# Certificado
Foi dado um certificado .crt e outro .cer
A entrada no programa e em .cer ou .pem
Foi utilizado o seguinte caminho para converter o .crt em .pem
openssl x509 -in ./certificado-ac-raiz-bry-v3.crt -out ./certificado-ac-raiz-bry-v3.pem

# Para compilar o programa utilize
gcc main.c -o main -lssl -lcrypto

# Para executar o programa compilado utilizar
./main /home/henrique_buzin/Documentos/bry-tecnologia/certificado-ac-raiz-bry-v3.pem
