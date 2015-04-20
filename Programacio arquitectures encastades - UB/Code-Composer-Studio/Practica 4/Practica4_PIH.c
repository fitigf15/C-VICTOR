/*
 * programa práctica 1 de PIH.
 * fichero practica1_PIH.c
 */

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
#include <stdbool.h>


typedef unsigned char byte;

#define chartest 0x55 //tren de bits 01010101.
#define bRxPacketLength 4
#define TXD0_READY (UCA0IFG & UCTXIFG)
#define RXD0_READY (UCA0IFG & UCRXIFG)

volatile unsigned long i,j;            // Volatile to prevent optimization
volatile char txchar,rxchar;
unsigned char contraste   = 0x64;
unsigned char iluminacion  = 30;
char textstyle = 2, linea = 1;
char saludo[] = "Practica 4";
char cadena[17];
char borrar[] = "                 "; //17 espacios para borrar una linea entera
char estado=0;
char estado_anterior=8;
int estado_botones = 0;

byte bID = 1;

byte gbpTxBuffer[5];
byte gbpRxBuffer[5];
byte gbpParameter[];
byte gbRxBufferReadPointer;
bool Byte_Recibido;
byte DatoLeido_UART;

volatile byte gbpRxInterruptBuffer[10];

volatile byte gbRxBufferWritePointer;

/**************************************************************************
 * ESCRIBIR LINEA
 *
 * Datos de entrada: Linea, indica la linea a escribir
 * 					 String, cadena de caracteres que vamos a introducir
 *
 * Sin datos de salida
 *
 **************************************************************************/

void escribir(char String[], unsigned char Linea)

{
	halLcdPrintLine(String, Linea, OVERWRITE_TEXT); //superponemos la nueva palabra introducida, haya o no algo.
}

void init_botons(void)
{
  //Configuramos botones y leds:
  P1DIR |= 0x03;	//Puertos P1.0 y P1.1 como salidas (Leds)
  P1OUT |= 0x01;	//Inicializamos puerto P1.0 a 1, 
  P1OUT &= 0xFD;	// y P1.1 a 0, para leds en alternancia


  P2DIR &= ~0xC0;	//Puertos P2.6 y P2.7 como entradas (botones S1 y S2)
  P2SEL &= ~0xC0;	//Puertos P2.6 y P2.7 como I/O digitales,
  P2REN |= 0xC0;	//con resistencia activada
  P2OUT |= 0xC0;	// de pull-up
  P2IE |= 0xC0; 	//Interrupciones activadas en P2.6 y P2.7,
  P2IES &= ~0xC0;	// con transicion L->H
  
  
  //Configuramos el joystick:
  P2DIR &= ~0x3E;	//Puertos P2.1 a P2.5 como entradas (joystick)
  P2SEL &= ~0x3E;	//Puertos P2.1 y P2.5 como I/O digitales,
  P2REN |= 0x3E;	//con resistencia activada
  P2OUT |= 0x3E;	// de pull-up
  P2IE |= 0x3E; 	//Interrupciones activadas en P2.1 a P2.5,
  P2IES &= ~0x3E;	// con transicion L->H
  
}

void init_LCD(void)
{
	//Inicializamos la pantallita LCD:    
  halLcdInit();       
  halLcdBackLightInit();  
  halLcdSetBackLight(iluminacion);
  halLcdSetContrast(contraste);
  halLcdClearScreen(); 
}



/**************************************************************************
 * INICIALIZACIÓN DE LA UCS.
 * Inicializamos la UCS:
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/

void init_UCS(void)
{
 //inicialització de les freqüències de rellotge del microcontrolador
	unsigned long DCORSEL = DCORSEL_7; //DCORSEL_6 selecciona rango de DCO de 7 a 60 MHz
	unsigned short FLLN = 487; //Parametro N
	__bis_SR_register(SCG0); // Desactiva el FLL control loop
	UCSCTL0 = 0x00; // Posa DCOx, MODx al mínim possible
	UCSCTL1 = DCORSEL; // Seleccionem el rang de DCO 16 MHz
	UCSCTL2 = FLLN + FLLD_1; //Selecciona el factor multiplicador del DCO
	UCSCTL3 = 0; //Referència FLL SELREF = XT1, divisor =1;
	/* Selecció de la font de rellotge: ACLK el Clock extern de 215, SMCLK i MCLK el DCO intern de 16MHz */
	UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV | SELM__DCOCLKDIV ;
	UCSCTL5 = DIVA__1 | DIVS__1; //Divisor per SMCLK: f(SMCLK)/1 i ACLK: f(ACLK)/1
	__bic_SR_register(SCG0); // Enable the FLL control loop
	P11DIR = 0x07; //Configurem els pins 11.0, 11.1 y 11.2 com sortida
	P11SEL = 0x07; //ACLK, MCLK y SMCLK; activem els pins de test


	gbRxBufferReadPointer = gbRxBufferWritePointer = 0;
}

/**************************************************************************
 * INICIALIZACIÓN DE LA UART.
 * Inicializamos la UART:
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/

void init_UART(void)
{
	UCA0CTL1 |= UCSWRST; 		//Fem un reset de la USCI i es desactiva
	UCA0CTL0 = 0x00; 			//UCSYNC=0 mode asíncron
								//UCMODEx=0 seleccionem mode UART
								//UCSPB=0 nomes 1 stop bit
								//UC7BIT=0 8 bits de dades
								//UCMSB=0 bit de menys pes primer
								//UCPAR=x no es fa servir bit de paritat
								//UCPEN=0 sense bit de paritat
	UCA0CTL1 |= UCSSEL__SMCLK; 	//Triem SMCLK (16MHz) com a font del clock BRCLK
	UCA0BR0 = 1; 				//Prescaler de BRCLK fixat a 1 (LO byte = 1, ...
	UCA0BR1 = 0; 				//... HI byte = 0).
	UCA0MCTL = UCOS16; 			// No necessitem modulació (divisió entera), però
								// si oversampling => bit 0 = UCOS16 = 1.
								// El Baud rate és BRCLK/16=1MBps
	P3SEL |= 0x30; 				//I/O funcion: P3.4 = UART0TX, P3.5 = UART0RX
	P3REN |= 0x20; 				//amb resistència activada de pull-up l’entrada P3.5
	P3OUT |= 0x20; 				//
	P3DIR |= 0x80; 				//Port P3.7 com sortida (Data Direction: selector Tx/Rx)
	P3SEL &= ~0x80; 			//Port 3.7 com I/O digital
	P3OUT &= ~0x80; 			//Inicialitzem el port P3.7 a 0 (Rx)
	UCA0CTL1 &= ~UCSWRST; 		//Reactivem la línia de comunicacions sèrie
	//UCA0IE |= UCRXIE; 			//Això s’ha d’activar només quan fem la recepció


 }


/**************************************************************************
 * INICIALIZACIÓN DE TIMER B.
 *
 **************************************************************************/

void init_A0_timer(void)
{
	TA0CTL = TASSEL_2+MC_1; //TBSSEL_2 - Mode SMCLK, MC_1 Mode UP
	TA0CCTL0=CCIE; //Habilitem interrupcions
	TA0CCR0 = 17000; //SMCLK treballa a uns 16MHz, per tant fer-lo arribar a 17000 equivaldria a aproximadament 1ms

}

/**************************************************************************
 * SENTIT RX.
 *
 **************************************************************************/

void Sentit_Dades_Rx(void)
{ 								//Configuració del Half Duplex dels motors: Recepció
	P3OUT &= ~0x80; 			//El pin P3.7 (DIRECTION_PORT) el posem a 0 (Rx)
}

/**************************************************************************
 * SENTIT TX.
 *
 **************************************************************************/

void Sentit_Dades_Tx(void)
{ 								//Configuració del Half Duplex dels motors: Transmissió
	P3OUT |= 0x80; 				//El pin P3.7 (DIRECTION_PORT) el posem a 1 (Tx)
}
/**************************************************************************
 * TxUAC0.
 *
 **************************************************************************/

void TxUAC0(byte bTxdData)
{
	while(!TXD0_READY); 		// Espera a que estigui preparat el buffer de transmissió
	UCA0TXBUF = bTxdData;
}

/**************************************************************************
 * RESET TIMEOUT.
 *
 **************************************************************************/

void Reset_Timeout(void)
{
	i=0;
}
/**************************************************************************
 * TIMEOUT.
 *
 **************************************************************************/

byte TimeOut(int timeOut)
{
	byte to;
	to = 0x00;
	i=0;
	while(!Byte_Recibido)
	{
		if(i==timeOut)
		{
			to = 0xff;
			break;
		}
		//USCI_A0_ISR();
		i++;

	}
	return to;
}

/*
TxPacket() send data to RS485.
TxPacket() needs 3 parameter; ID of Dynamixel, Instruction byte, Length of parameters.
TxPacket() return length of Return packet from Dynamixel.
*/

byte TxPacket(byte bID, byte bParameterLength, byte bInstruction)
{
	byte bCount,bCheckSum,bPacketLength;
	char error[] = "adr. no permitida";
	if ((gbpParameter[0]<5)&&(bInstruction==3)){//si se intenta escribir en una direccion <= 0x05,
		//emitir mensaje de error de direccion prohibida:
		  halLcdPrintLine( error,8,textstyle);
		  //y salir de la funcion sin mas:
		  return 0;
	}
	Sentit_Dades_Tx(); 			//El pin P3.7 (DIRECTION_PORT) el posem a 1 (Tx)
	gbpTxBuffer[0] = 0xff; 		//Primers 2 bytes que indiquen inici de trama FF, FF.
	gbpTxBuffer[1] = 0xff;
	gbpTxBuffer[2] = bID; 		//ID del mòdul al que volem enviar el missatge
	gbpTxBuffer[3] = bParameterLength+2;//Length(Parameter,Instruction,Checksum)
	gbpTxBuffer[4] = bInstruction; 		//Instrucció que enviem al mòdul
	for(bCount = 0; bCount < bParameterLength; bCount++)//Comencem a generar la trama
	{
		gbpTxBuffer[bCount+5] = gbpParameter[bCount];
	}
	bCheckSum = 0;
	bPacketLength = bParameterLength+4+2;
	for(bCount = 2; bCount < bPacketLength-1; bCount++) //Càlcul del Checksum
	{
		bCheckSum += gbpTxBuffer[bCount];
	}
	gbpTxBuffer[bCount] = ~bCheckSum; 					//Escriu el Checksum (complement a 1) amb el bit RS485_TXD
	for(bCount = 0; bCount < bPacketLength; bCount++) 	//Aquest bucle és el que envia la trama
	{
		TxUAC0(gbpTxBuffer[bCount]);
	}
	while(UCA0STAT&UCBUSY); 							//Espera fins s’ha transmès el últim byte
	Sentit_Dades_Rx(); 									//Posem la línia de dades en Rx perquè el mòdul Dynamixel envia resposta
	return(bPacketLength);
}
/*
RxPacket() read data from buffer.
RxPacket() need a Parameter; Total length of Return Packet.
RxPacket() return Length of Return Packet.
1. Definicio var. locals
2. Direccio dades RX
3. Inicialitzacio timeout
4. Saber si ha rebut byte
5a.1 Ha rebut byte
5a.2 Afegir byte a la trama rebuda
5a.3a.1 Es l'ultim byte de la trama
5a.3a.2 Comprovem CheckSum
5a.3a.3a.1 Error de checksum
5a.3a.3a.2 Sortim amb missatge d'error
5a.3a.3b.1 No error de checksum
5a.3a.3b.1 Sortir i retornar trama rebuda
5a.3b.1 No es l'ultim byte de la trama
5a.3b.2 Tornem al pas 3 (Inicialitzacio de timeout)
5b.1 No ha rebut byte
5b.2 Comprovem el timeout
5b.2a.1 No hi ha timeout
5b.2a.2 Tornem al pas 4 (saber si ha rebut byte)
5b.2b.1 Hi ha timeout
5b.2b.2 Sortim amb missatge d'error

*/
byte RxPacket(byte RxPacketLength)
{
	// 1. Definicio var. locals
	byte bCount, bLength, bChecksum, bTimeout;
	bTimeout=0;
	//2. Direccio dades RX
	Sentit_Dades_Rx();
	//Timer_A0_ISR();
	for(bCount=0;bCount< bRxPacketLength; bCount++)
	{
		//3. Inicialitzacio timeout
		Reset_Timeout();
		Byte_Recibido=false;
		//4. Saber si ha rebut byte
		while(!Byte_Recibido)
		{
			bTimeout=TimeOut(5000);
			//5b.2 Comprovem el timeout
			if(bTimeout)break;
		}
		//5b.2 Comprovem el timeout
		if(bTimeout)break;
		//5a.2 Afegir byte a la trama rebuda
		gbpRxBuffer[bCount] = DatoLeido_UART;
	}
	bLength=bCount;
	bChecksum=0;
	if(!bTimeout)
	{
		if(gbpRxBuffer[0] != 0xff || gbpRxBuffer[1] != 0xff )
		{
			//estat =("\r\n [Error:Wrong Header]");
			estado = 10;
			return 0;
		}
		if(gbpRxBuffer[2] != gbpTxBuffer[2] )
		{
			//estat =("\r\n [Error:TxID != RxID]");
			estado = 11;
			return 0;
		}
		if(gbpRxBuffer[3] != bLength-4)
		{
			//estat =("\r\n [Error:Wrong Length]");
			estado = 12;
			return 0;
		}
		for(bCount = 2; bCount < bLength; bCount++) bChecksum +=gbpRxBuffer[bCount];
		if(bChecksum != 0xff)
		{
			estado = 13;
			//estat =("\r\n [Error:Wrong CheckSum]");
			return 0;
		}
	}
	return bLength;

}



void main(void)
{	

  	WDTCTL = WDTPW+WDTHOLD;       	// Paramos el watchdog timer
  	init_botons();					// Iniciamos los botones y Leds.
    _enable_interrupt(); 			// Activamos las interrupciones a nivel global del chip
    init_LCD();						// Inicializamos la pantalla
    init_UCS();						//Inicialitzem UCS
    init_UART();					//Inicialitzem UART
    //init_A0_timer();

    escribir(saludo,linea);

  	do
   	{
  		if (estado_anterior != estado)			// Dependiendo el valor del estado se encenderá un LED externo u otro.
		{
		   sprintf(cadena," estado %d", estado); 	// Guardamos en cadena lo siguiente frase: estado "valor del estado"
		   escribir(cadena,linea); 			// Escribimos cadena
		   estado_anterior=estado; 			// Actualizamos el valor de estado_anterior, para que no esté siempre escribiendo.
		}
   	}
  	while(1);

}
/*
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
	//Inicializamos los leds para que parpadeen en fase (S1) o alternando (S2):
	P2IE &= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) desactivadas
	P2IE &= 0x3E;  //interrupciones joystick (2.1-2.5) desactivadas
	switch (P2IFG) {
	case 0x40: //Boton S1
		    txchar=chartest;
	    	P1OUT |= 0x03; //Leds parpadean a la vez
	    	estado_botones=1;
		break;
	case 0x80: //Boton S2
			txchar=~chartest;
	    	P1OUT |= 0x01; //Leds parpadean en alternancia
	    	estado_botones=2;
		break;
	case 0x02: // joystick left
		    if (bID > 0x00) bID--;
	    	else bID = 0xFE;
		break;
	case 0x04: // joystick right
			if (bID < 0xFE) bID++;
	    	else bID = 0;
		break;
	case 0x08: // joystick center
			P1OUT |= 0x01;P1OUT &= 0xFD;//Leds parpadean alternando
		break;
	case 0x10: // joystick up
			if (bID < 0xF0) bID+=0x0F;
	    	else bID = 0;
		break;
	case 0x20: // joystick down
		    if (bID > 0x0F) bID-=0x0F;
	    	else bID = 0xFE;
		break;

	default: break;
	}
	
	sprintf(cadena,"bID = %d",bID);
	halLcdPrintLine( cadena,linea,OVERWRITE_TEXT );
	
	P2IFG = 0;		//limpiamos todas las interrupciones
	P2IE |= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) reactivadas
	P2IE |= 0x3E;  //interrupciones joystick (2.1-2.5) reactivadas
 return;
}
*/

/**************************************************************************
 * recepció de bytes mitjançant la UART.
 **************************************************************************/

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{ //interrupcion de recepcion en la uart A0
	UCA0IE &= ~UCRXIE; //Interrupciones desactivadas en RX
	DatoLeido_UART = UCA0RXBUF;
	Byte_Recibido=true;
	UCA0IE|= UCRXIE; //Interrupciones reactivadas en RX
	return;
}

/**************************************************************************
 * MINIPROGRAMA DE TIMER:
 * Mediante este programa, se detectará el timer
 *
 * Sin Datos de entrada
 *
 * Sin datos de salida
 *
 * Aumenta nuestra variable i
 *
 **************************************************************************/
#pragma vector= TIMER1_A0_VECTOR
__interrupt void Timer1_ISR(void)
{
	i++; //Quan s'arriba a TA1CCR0 s'incrementa i (Depen de la frequencia si es ACLK o SMCLK)
}

/*Falta per fer:
 * Inicialitzar el timer(SMCLK ens va a 16MHz, no a 1
 * Acabar RxPacket
 * Llibreria
 */
