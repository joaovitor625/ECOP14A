#include "adc.h"
#include "config.h"
#include "keypad.h"
#include "lcd.h"
#include "pic18f4520.h"
#include "pwm.h"
#include "serial.h"
#include "ssd.h"
#include "timer.h"
//includes
void LeTeclado(void);
void Serial(void);
void MostraDisplay(void);

void main(void) {
    char slot;
    //inicializações
    kpInit();
    lcdInit();
    adcInit();
    pwmInit();
    pwmFrequency(100000);
    adcInit();
    for (;;) {
        timerReset(5000);
        ssdUpdate();
        switch (slot) {
            case 0:
                LeTeclado();
                slot = 1;
                break;
            case 1:
                Serial();
                slot = 2;
                break;
            case 2:
                kpDebounce();
                slot = 3;
                break;
            case 3:
                MostraDisplay();
                slot = 0;
                break;
            default:
                slot = 0;
                break;
        }
        timerWait();
    }
}

void LeTeclado(void) {
    unsigned char tecla;
    kpDebounce();
    tecla = kpRead();
    if (BitTst(tecla, 0)) { //A
        lcdCommand(0x80);
        lcdData('J');
        lcdData('0');
        lcdData('a');
        lcdData('0');
    }
    if (BitTst(tecla, 1)) { //B
        lcdCommand(0xc0);
        lcdData(50);
        lcdData(48);
        lcdData(50);
        lcdData(50);
        lcdData(48);
        lcdData(48);
        lcdData(49);
        lcdData(56);
        lcdData(50);
        lcdData(49);
    }
    if (BitTst(tecla, 2)) { //C
        pwmSet1(100);
    }
    if (BitTst(tecla, 3)) { //D
        pwmSet1(0);
    }
    if (BitTst(tecla, 3)) { //0
        lcdCommand(0x01);
    }
}

void Serial(void) {
    int temp;
    unsigned char dadoSerial;
    dadoSerial = serialRead();
    if (dadoSerial != 0) { //Se dado e valido
        switch (dadoSerial) {
            case 'A':
                lcdCommand(0x80);
                lcdData('J');
                lcdData('0');
                lcdData('a');
                lcdData('0');
                break;
            case 'B':
                lcdCommand(0xc0);
                lcdData(50);
                lcdData(48);
                lcdData(50);
                lcdData(50);
                lcdData(48);
                lcdData(48);
                lcdData(49);
                lcdData(56);
                lcdData(50);
                lcdData(49);
                break;
            case 'C':
                pwmSet1(100);
                break;
            case 'D':
                pwmSet1(0);
                break;
            case '0':
                lcdCommand(0x01);
                break;
        }
        temp = adcRead() / 2;
        serialSend('T');
        serialSend(':');
        serialSend(((temp / 10) % 10) + 48);
        serialSend((temp % 10) + 48);
        serialSend(13);
    }

}

void MostraDisplay(void) {
    int temp;
    temp = adcRead() / 2;
    ssdDigit(((temp / 100) % 10), 2);
    ssdDigit(((temp / 10) % 10), 1);
    ssdDigit((temp % 10), 0);
}

