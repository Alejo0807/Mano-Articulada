/*
 * servomotor.c
 *
 * Created: 08/10/2017 03:51:43 a. m.
 * Author : Alejandro Enrique
 */ 



#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>


uint16_t adc0;
uint16_t adc1;
uint16_t adc2;
uint16_t adc3;
uint16_t adc4;

int valor;

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////		 PARA USAR LA SEÑAL PWM EN LOS SERVOMOTORES	  ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void timer_0(){
	
	TCCR0A |= (1<<COM0A1)|(1<<COM0B1)|(0<<WGM01)|(1<<WGM00); //Fase correcta pwm por OC0B
	TCCR0B |= (1<<CS02)|(0<<CS01)|(0<<CS00); //prescaler a 64
	// OCR0B y OCR0A activos
}

void timer_1(){
	
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(0<<WGM11)|(1<<WGM10); //Fase correcta pwm por OC0B
	TCCR1B |= (1<<CS12)|(0<<CS11)|(0<<CS10); //prescaler a 64
	// OCR1B y OCR1A activos
}
	
void timer_2(){
	
	TCCR2A |= (1<<COM2A1)|(1<<COM2B1)|(0<<WGM21)|(1<<WGM20); //Fast pwm por OC0B
	TCCR2B |= (1<<CS22)|(0<<CS21)|(0<CS20); //prescaler a 64
	// OCR2B y OCR2A activos
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////									ADC PARA LOS SOFTPOT							   ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adc_0(){
	
	
	//-Se utiliza el ADC0
	
	ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	//Activa el conversor analogico digital
	//prescaler en 64

	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

void adc_1(){
	
	
	//-Se utiliza el ADC1
	
	ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0);
	//Activa el conversor analogico digital
	//prescaler en 64

	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

void adc_2(){
	
	
	//-Se utiliza el ADC2
	
	ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0);
	//Activa el conversor analogico digital
	//prescaler en 64

	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}
void adc_3(){
	
	
	//-Se utiliza el ADC3
	
	ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);
	//Activa el conversor analogico digital
	//prescaler en 64

	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

void adc_4(){
	
	
	//-Se utiliza el ADC4
	
	ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0);
	//Activa el conversor analogico digital
	//prescaler en 64

	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

uint16_t read_adc(){
	
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return(ADC);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void giro0(int valor){
	
	OCR0A = valor;
	
}
void giro1(int valor){
	
	OCR0B = valor;
	
}
void giro2(int valor){
	
	OCR1A = valor;
	
}
void giro3(int valor){
	
	OCR1B = valor;
	
}
void giro4(int valor){
	
	OCR2A = valor;
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////




int main(void)
{
	
	DDRB |= (1<<PINB1)|(1<<PINB2)|(1<<PINB3);
	DDRD |= (1<<PIND3)|(1<<PIND5)|(1<<PIND6);
	DDRC = 0x00;
	
	timer_0();
	timer_1();
	timer_2();
	
	while (1)
	{	
		
		
		adc_0();
		adc0 = read_adc();
		adc0 = adc0*39/1023;
		if (adc0 >= 20){
			giro0(20);	
		}else{
			giro0(adc0);
		}
		
		adc_1();
		adc1 = read_adc();
		adc1 = adc1*39/1023;
		if (adc1 >= 36){
			giro1(36);
		}else{
			giro1(adc1);
		}
		
		adc_2();
		adc2 = read_adc();
		adc2 = adc2*39/1023;
		if (adc2 >= 20){
			giro2(20);
		}else{
			giro0(adc2);
		}
		
		adc_3();
		adc3 = read_adc();
		adc3 = adc3*39/1023;
		if (adc3 >= 20){
			giro3(20);
		}else{
			giro3(adc3);
		}
		
		adc_4();
		adc4 = read_adc();
		adc4 = adc4*39/255;

		//giro4(29); //minimo
	
		//giro4(160);// maximo
		
		
		if (adc4 >= 60){
			giro4(60);
		}else{
			giro4(adc4);
		}
		
	}
	
}
