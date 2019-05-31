
#include "cMIPS.h"

#include "uart_defs.h"

//retorna nrx
int proberx(void){


}

//retorna ntx
int propetx(void){

}

//retorna inteiro com status no byte menos sign.
Tstatus iostat(void){


}

//escreve byte menos sign no reg. de controle
void ioctl(Tcontrol){

}


//escreve byte menos sign no reg. de interrupções
int ioint(Tinterr){


}

//retira o octeto da fila, decrementa nrx
char Getc(void){

}

//insere octeto na fila, decrementa ntx
void Putc(char){


}

//Inicializa a UART
void InitUART(void){
	Tserial  volatile *uart;  // tell GCC not to optimize away code
	Tcontrol ctrl;
	extern   int Ud[2];      // space reserved/declared in include/handlers.s
	volatile int *bfr;       // points to buffer Ud[]
	char c;

	bfr = (int *)Ud;             // buffer declared in include/handlers.s
	uart = (void *)IO_UART_ADDR; // bottom of UART address range
	ctrl.ign   = 0;
	ctrl.rts   = 0;  // make RTS=0 to hold remote unit inactive
	ctrl.ign4  = 0;
	ctrl.speed = SPEED;
	uart->ctl  = ctrl; // initialize UART
	// handler sets flag=[U_FLAG] to 1 after new character is received;
	// this program resets the flag on fetching a new character from buffer
	bfr[U_FLAG] = 0;      //   reset flag  

	// do generate interrupts on RXbuffer full
	uart->interr.i = UART_INT_progRX; // program only RX interrupts

	ctrl.ign   = 0;
	ctrl.rts   = 1;  // make RTS=1 to activate remote unit
	ctrl.ign4  = 0;
	ctrl.speed = SPEED; // operate at fraction of highest data rate
	uart->ctl = ctrl;
}

char Getc(void){
	
}

void Putc(char){
	
}

int main(void){
	static int[2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 , 41 , 43 , 47 , 49 , 53 , 59 , 61 , 67 , 71 , 73 , 79 , 83 , 89 , 97 , 101 , 103 , 107 , 109 , 113 , 119 , 127 , 131. 137 , 139 , 149 , 151 , 163 , 167];

	InitUart();



  do {
    while ( (c = (char)bfr[U_FLAG]) == 0 )  // check flag in Ud[]
      delay_cycle(1);                       // nothing new, wait

    c = (char)bfr[U_DATA];   // get new character
    bfr[U_FLAG] = 0;         //   and reset flag

    if (c != (char)EOT)      // if NOT end_of_transmission
      to_stdout( c );        //   then print new char
    else
      to_stdout( '\n' );     //   else print new-line

  } while (c != (char)EOT);  // end of transmission?

  return c;             // so compiler won't optimize away the last loop

}