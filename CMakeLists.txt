CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_CXX_STANDARD 14)

#============================================================================================
PROJECT(bt-rfid-reader)

SET(DEVICE "atmega328p")
SET(FREQ "16000000")

#============================================================================================
#include_directories(/usr/share/arduino/hardware/arduino/cores/arduino/)
#include_directories(/usr/share/arduino/hardware/arduino/variants/standard/)
#include_directories(/usr/share/arduino/libraries/SPI/)


include_directories("${PROJECT_SOURCE_DIR}/additional_libs/SoftwareSerial/src/")
include_directories("${PROJECT_SOURCE_DIR}/additional_libs/SPI/src")
include_directories("${PROJECT_SOURCE_DIR}/additional_libs/rfid/src")
include_directories("${PROJECT_SOURCE_DIR}/additional_libs/avr/cores/arduino/")
include_directories("${PROJECT_SOURCE_DIR}/additional_libs/avr/variants/standard/")


include_directories(/usr/lib/avr/include/)




#============================================================================================

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

SET(CMAKE_C_FLAGS  "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -std=gnu99 -Wl,--gc-sections")
SET(CMAKE_CXX_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -Wl,--gc-sections")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#============================================================================================
#Sources
SET(SOURCE_FILES
        main.cpp
        additional_libs/avr/cores/arduino/HardwareSerial.cpp
        additional_libs/avr/cores/arduino/HardwareSerial0.cpp
        additional_libs/SPI/src/SPI.cpp
        additional_libs/rfid/src/MFRC522.cpp
        additional_libs/avr/cores/arduino/Stream.cpp
        additional_libs/avr/cores/arduino/wiring.c
        additional_libs/avr/cores/arduino/wiring_digital.c
        additional_libs/avr/cores/arduino/Print.cpp
        additional_libs/avr/cores/arduino/hooks.c

)

#Headers
SET(HEADER_FILES
        /usr/lib/avr/include/inttypes.h
        /usr/lib/avr/include/avr/iom328p.h
        /usr/lib/avr/include/string.h
        /usr/lib/avr/include/avr/pgmspace.h
        /usr/lib/avr/include/ctype.h
        /usr/lib/avr/include/stdlib.h

        Configuration/commons.h
        Configuration/uart.h
        additional_libs/avr/cores/arduino/HardwareSerial.h
        additional_libs/SPI/src/SPI.h
        additional_libs/rfid/src/MFRC522.h
        additional_libs/rfid/src/deprecated.h
        additional_libs/avr/cores/arduino/Arduino.h
        additional_libs/avr/variants/standard/pins_arduino.h
        additional_libs/avr/cores/arduino/Stream.h
        additional_libs/avr/cores/arduino/wiring_private.h
        additional_libs/avr/cores/arduino/Print.h
)

#============================================================================================

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -R.eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.eep)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} --mcu=${DEVICE} --format=avr)
