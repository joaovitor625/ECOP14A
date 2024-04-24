void configurarled(void){
  (*(volatile __near unsigned char*) 0xf95) =0x00;
  (*(volatile __near unsigned char*) 0xf83) =0x00;
}

void ligarled(char num){
    char mascara;
    mascara = 1 <<num;
    (*(volatile __near unsigned char*)0xf83)|=mascara;
}

void desligarled(char num){
    char mascara;
    mascara = 1 <<num;
    (*(volatile __near unsigned char*)0xf83)&=~mascara;
}