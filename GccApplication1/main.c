/*
 * GccApplication1.c
 *
 * Created: 26.01.2021 19:05:40
 * Author : aga
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define SPI_DDR DDRB
#define CS      PORTB2
#define MOSI    PORTB3
#define SCK     PORTB5

void SPI_init();
void Send_spi(int8_t x);

int main(void)
{
	DDRB = 255;		
	PORTB = 0b11101111; 
	
	SPI_init();
    
    while (1) 
    {
        Send_spi(5);
        _delay_ms(1000);
		Send_spi(150);
		_delay_ms(1000);
		Send_spi(250);
		_delay_ms(1000);
    }
}

void SPI_init()
{
	// set CS, MOSI and SCK to output
	SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);

	// enable SPI, set as master, and clock to fosc/128
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

void Send_spi(int8_t x)
{
	SPDR = x;
	while (!bit_is_set(SPSR, SPIF));
}