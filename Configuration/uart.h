#ifndef BT_RFID_READER_UART_H
#define BT_RFID_READER_UART_H

//#define BAUDRATE 115200
//#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//void USART_init(void){
//
//    UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
//    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
//    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
//    UCSR0C = (3<<UCSZ00);
//}
//
//unsigned char USART_receive(void){
//
//    while(!(UCSR0A & (1<<RXC0)));
//    return UDR0;
//
//}
//
//void USART_send( unsigned char data){
//
//    while(!(UCSR0A & (1<<UDRE0)));
//    UDR0 = data;
//
//}
//
//void USART_putstring(char* StringPtr){
//
//    while(*StringPtr != 0x00){
//        USART_send(*StringPtr);
//        StringPtr++;}
//
//}

#endif //BT_RFID_READER_UART_H
