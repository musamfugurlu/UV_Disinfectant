/*
 * File:   Sbox 16F1503.c
 * Author: Musa
 *
 * Created on 17 Haziran 2020 Çarsamba, 21:25
 */


#include <xc.h>
#include "pic16f1503.h"

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)
#define _XTAL_FREQ 16000000
#define buton   RA5
#define hall    RC3

#define kirmizi RC5
#define yesil   RA4
#define mavi    RC4
#define uv      RC2

   unsigned int    btdeger=0, btdegerson=0, ucdk=0,  ucdkkey=0, ucsn=0, ucsnkey=0, altidk=0, ondk=0;
   unsigned char   btsn=0, program=0, i=0, birsn=0, birsnkey=0, btkey=0;
   unsigned char   hallkey=0, blink=0, btblink=0, btblinkkey=0;

 void batarya_oku(void){  // BATARYA GERILIMINI OKUMA

         GO=1;
         while(GO);
         btdeger=(ADRESH<<8)+ADRESL;

      /* if(btdegerson==0) btdegerson=btdeger; // CIHAZA ELEKTRIK GIDINCE DEGERLER 1 DEFA ESITLENIR

         if((btdeger+35)<btdegerson){ // SARJ AZALMAYA BASLADIGINDA
             btdegerson=btdeger; yesil=0; btblinkkey=0;}

         if(btdeger > (btdegerson+30)){  // BT SARJ OLURKEN
             btdegerson=btdeger;
             btblinkkey=1; kirmizi=0;
            }

             if(btblinkkey==1 && btblink>50){ // BT SARJ OLURKEN YESIL BLINK
                 yesil=1;
                 if(btblink>100){
                 yesil=0;
                 btblink=0;}
                 } */


         if(btdeger>1020) {    // FULL SARJ YESIL YANIK
             yesil=1; kirmizi=0; btkey=0;}

         if(btblinkkey==0){
           if(btdeger>765 && btdeger<850 ){   // SARJ YETERLI
             kirmizi=0; yesil=0; btkey=0;}

           if(btdeger>735 && btdeger<=745 && btsn>50){ // SARJ AZ KALMIS
             btsn=0;
             btkey=0;
            yesil=0; kirmizi=!kirmizi;}

           if(btdeger<=720) {   // SARJ BITMIS
             yesil=0; kirmizi=1; mavi=0; uv=0;
                ucsn=0;
                altidk=0;
                ucdk=0;
                program=0;
                birsnkey=0;
                birsn=0;

             if(btkey==0){
             for(i=0;i<6;i++){
                    kirmizi=!kirmizi;
                    yesil=kirmizi;
                    mavi=kirmizi;
                    btkey=1;
                    __delay_ms(12);

                }
                    kirmizi=0;
                    mavi=0;
                    yesil=0;
             }
           }
         }
      }
 void kapak(void){

     if(hall==0)hallkey=0;

     else if(hall==1){ // KAPAK ACIKKEN PROGRAM CALISMAZ
                uv=0;
                ucsn=0;
                altidk=0;
                ucdk=0;
                program=0;
                birsnkey=0;
                birsn=0;

        if(hallkey==0){ // HALL ANIMASYONU
             for(i=0;i<6;i++){
                   hallkey=1;
                    kirmizi=!kirmizi;
                    yesil=kirmizi;
                    mavi=kirmizi;
                    __delay_ms(12);
                 }


        }
     }

 }
     void program_sec(void){
        if(buton==0 && uv==0 && program==0){
            for(i=0; i<100; i++);
            while(buton==0){};
            program=1;
        }

       switch (program) {

        case 1:

            if(ucsn<300){ // 3 SN SONRA 3 DK MOD BASLAR
                if(buton==0 && uv==0 && program==1){
                for(i=0; i<100; i++);
                while(buton==0){};
                program=2;
                }
            }
           if(ucsn==300){ // BASLAMA ANIMASYONU
               kirmizi=1; yesil=1; mavi=1;
               __delay_ms(75);
               kirmizi=0; yesil=0; mavi=0;
            uv=1;
            ucdk=0;
           }

            if(ucsn>300 && blink>=30){ // 0.3 SN MAVI BLINK
                mavi=!mavi;
                blink=0;}

             if(ucdk==18000){ // 3 DK SONRA PROGRAM KAPAT
               uv=0;
               ucsn=0;
               ucdk=0;
               program=0;
               mavi=1; ondk=0;
             }
              if(buton==0)
            {
                birsnkey=1;
                if(birsn==100)
                {
                uv=0;
                ucsn=0;
                altidk=0;
                ucdk=0;
                program=0;
                birsnkey=0;
                birsn=0;
                 for(i=0;i<6;i++){
                    kirmizi=!kirmizi;
                    yesil=kirmizi;
                    mavi=kirmizi;
                    __delay_ms(12);
                }
                while(buton==0){};
                }
            }
        break;

        case 2:

            if(uv==0){
            kirmizi=1; yesil=1; mavi=1;
            __delay_ms(75);
            kirmizi=0; yesil=0; mavi=0;
            }
            uv=1;

            if(blink>=100){ //1 SN MAVI BLINK
                mavi=!mavi;
                blink=0;}

            if(altidk==36000){ // 6 DK SONRA PROGRAM KAPAT
                uv=0;
                ucsn=0;
                altidk=0;
                ucdk=0;
                program=0;
                mavi=1; ondk=0;
                }

            if(buton==0){
                birsnkey=1;
                if(birsn==100){
                uv=0;
                ucsn=0;
                altidk=0;
                ucdk=0;
                program=0;
                birsnkey=0;
                birsn=0;
                for(i=0;i<6;i++){
                    kirmizi=!kirmizi;
                    yesil=kirmizi;
                    mavi=kirmizi;
                    __delay_ms(12);
                }
                while(buton==0){};
                }
            }


        break;

        case 0: break;

      }
    }

void main(void) {

    TRISA=0b100000; TRISC=0b001010;
    CHS4=0; CHS3=0; CHS2=1; CHS1=0; CHS0=1;
    ADFM=1; ADON=1; ANSELC=0;

    PORTA=0b100000; PORTC=0b001000;

    T0CS=0; PSA=0; PS2=0; PS1=0; PS0=1;
    TMR0IF=0; TMR0=0;


    while(1){

        if(TMR0IF==1){ // HER 10 MS DE BURAYA GIRER
            TMR0IF=0; TMR0=0;
            btsn++; blink++; ondk++; btblink++;

            if(birsnkey==1)birsn++;
                if(program==1){
                ucdk++; ucsn++;}

            if(program==2){
                altidk++;}
         }
        if(ondk==60000)mavi=0; // 10 DK SONRA MAVI SONDUR

          kapak();
          program_sec();
          batarya_oku();

        }
     return;
}

