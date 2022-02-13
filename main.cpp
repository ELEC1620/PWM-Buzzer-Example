/*  PWM-Buzzer-Example
*   Generate a pwm signal to be passed to the buzzer to play required tones.
*
*   NOTE: - more note definitions held in Note_definitions.txt
*         - Note definitions taked from arduino.cc
*
*   Author: Andrew Knowles 2021
*/

#include "mbed.h"

//note definitions
#define NOTE_C4  262    //octave 4 - middle c
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

DigitalIn button(PC_10);
DigitalOut led(PC_0);
PwmOut buzzer(PA_15);

const int C_major_scale[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5}; //create array with the required notes (in order)

void play_note(int frequency);

int main(){
    led.write(0);

    while(1){
        if(button.read() == 1){
            led.write(1);

            for(int i = 0; i < 8; i++){         //iterate through the C_major_scale array
                play_note(C_major_scale[i]);    //pass the note at position C_major_scale[i] to function
            }

            buzzer.pulsewidth_us(0);            //turn off buzzer
            led.write(0);
        }
    }
}

void play_note(int frequency){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);    //set the period of the pwm signal (in us)
    buzzer.pulsewidth_us(buzzer.read_period_us()/2);            //set pulse width of the pwm to 1/2 the period
    ThisThread::sleep_for(500ms);                               //play sound for 500ms
}


