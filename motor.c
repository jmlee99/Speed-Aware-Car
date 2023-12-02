###############################################################################################
###################################### 선언 및 정의 ############################################
###############################################################################################
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

/*
###############################################################################################
######################################## 함수 정의 ##############################################
###############################################################################################
*/

void PWM_init(void)
{
	// 핀을 출력으로 설정
	DDRE |= (1 <<0)|(1 <<2)|(1 <<5);	// 0b00100101;
	DDRB |= (1 <<0)|(1 <<2)|(1 <<5);	// 0b00100101;
	PORTE |= 0x00;
	PORTB |= 0x00;
	
	//모드 14 고속 pwm timer/counter 3번
	TCCR3A |=(1 << WGM30);
	TCCR3B |=(1 << WGM32);
	
	
	TCCR1A |=(1 << WGM10);
	TCCR1B |=(1 << WGM12);
	
	// 비반전 모드 TOP : 0xff 비교 일치 값 : OCR3C : PE5
	TCCR3A |=(1<<COM3C1);
	// 비교 일치 A 비반전
	TCCR1A |=(1<<COM1A1);
	
	//분주비 64 : 16000000HZ / 64 ==> 250000HZ
	// 256 / 250000 == > 1.02ms , 약 1ms
	// 127/ 250000 ==> 0.5 ms
	TCCR3B |= (1<<CS31)|(1<<CS30); 
	TCCR1B |= (1 << CS11) | (1 << CS10); // 분주비 64
	
	OCR3C = 0;
	OCR1A = 0;
	//OCR1B = 0;
}

void ADC_init(unsigned char channel)
{
	ADMUX |= 0x40; // ADC 내부전압 사용 설정
	ADMUX |= 0x41;
	ADCSRA |= 0x07; // 분주비 설정
	ADCSRA |= (1<<ADEN); // ADC활성화 설정
	ADCSRA |= (1<<ADFR); // 프리러닝 모드 설정
	
	ADMUX = ((ADMUX&0xE0) |channel); //채널 선택 설정
	ADCSRA |= (1<<ADSC); // 변환 시작 설정
}

int read_ADC(void)
{
	ADMUX |= 0x40; // ADC 내부전압 사용 설정, PF0번 핀
	while(!(ADCSRA & (1<<ADIF))); // 데이터 레지스터에 새로운 데이터가 들어올 때까지 대기
	return ADC;
}

int read_ADC1(void)
{
	ADMUX |= 0x41; // ADC 내부전압 사용 설정, PF1번 핀
	while(!(ADCSRA & (1<<ADIF)));
	return ADC;
}

/*
###############################################################################################
######################################## 메인 코드 ##############################################
###############################################################################################
*/

int main(void)
{
	int read;
	int brk;
    ADC_init(0);
	PWM_init();
	
    while (1) 
    {
		OCR3C = 0;
		PORTE |= 0x00; 
		PORTB |= 0x00;			//정지
		read = read_ADC();
		brk = read_ADC1();
		
		if(brk < 250)
		{
			if(read < 100)
			{
				PORTE &= (1 << 4)|(1 << 0); // 정방향
				PORTB &= (1 << 4)|(1 << 0);
				OCR3C = 0;	  
				OCR1A = 0;		// stop
				_delay_ms(100);
			}
			else if((read >= 100) && (read < 200))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =25;	  // half speed
				OCR3C =25;	  // half speed
				_delay_ms(100);
			
			}
			else if((read >= 200) && (read < 300))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR3C =50;	// full speed
				OCR1A =50;	  // half speed
				_delay_ms(100);
			}
			else if((read >= 300) && (read < 400))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =75;	  // half speed
				OCR3C =75;	// full speed
				_delay_ms(100);
			}
			else if((read >= 400) && (read < 500))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =100;	  // half speed
				OCR3C = 100;	// full speed
				_delay_ms(100);
			}
			else if((read >= 500) && (read < 600))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A = 125;	  // half speed
				OCR3C = 125;	// full speed
				_delay_ms(100);
			}
			else if((read >= 600) && (read < 700))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =150;	  // half speed
				OCR3C =150;	// full speed
				_delay_ms(100);
			}
			else if((read >= 700) && (read < 800))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =175;	  // half speed
				OCR3C =175;	// full speed
				_delay_ms(100);
			}
			else if((read >= 800) && (read < 900))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =200;	  // half speed
				OCR3C =200;	// full speed
				_delay_ms(100);
			}
			else if((read >= 900) && (read < 1000))
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =225;	  // half speed
				OCR3C =225;	// full speed
				_delay_ms(100);
			}
			else
			{
				PORTE |= (1 << 4)|(1 << 0); // 정방향
				PORTB |= (1 << 4)|(1 << 0); // 정방향
				OCR1A =255;	  // half speed
				OCR3C =255;	// full speed
				_delay_ms(100);
			}
		}
		else
		{
			read = 0;
		}
    }
}
