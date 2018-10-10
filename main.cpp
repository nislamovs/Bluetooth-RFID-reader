#include <avr/io.h>
#include <util/delay.h>

#include "Configuration/commons.h"
#include "Configuration/uart.h"

#include "HardwareSerial.h"
#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.

#define LED_PORT PORTD
#define LED_PIN1 0
#define LED_PIN2 1
#define LED_DDR DDRD

#define BAUDRATE 115200
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)
//
void USART_init(void){

    UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (3<<UCSZ00);
}

int main(void) {
//
//    while (1) {
//        PIN_ON(LED_PORT, LED_PIN1);
//        _delay_ms(1300);
//        PIN_OFF(LED_PORT, LED_PIN1);
//        _delay_ms(1300);
//    }


    USART_init();
    Serial.begin(115200);		// Initialize serial communications with the PC
    while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

    SPI.begin();			// Init SPI bus
    mfrc522.PCD_Init();		// Init MFRC522
    mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

    while(1) {
        // Look for new cards
        if (!mfrc522.PICC_IsNewCardPresent()) {
            return 1;
        }

        // Select one of the cards
        if (!mfrc522.PICC_ReadCardSerial()) {
            return 2;
        }

        // Dump debug info about the card; PICC_HaltA() is automatically called
        mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    }
    return 0;
}
