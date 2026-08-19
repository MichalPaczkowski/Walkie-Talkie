#include <Arduino.h>
#include "AudioHandler.h"
#include "RadioManager.h"
#include <WiFi.h>
static constexpr int I2S_BCLK = 26;
static constexpr int I2S_WS   = 25;
static constexpr int I2S_DOUT = 22;
static constexpr int I2S_DIN  = 35;
static constexpr int BUTTON   = 32; 

uint8_t peerAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

AudioHandler audio(I2S_BCLK, I2S_WS, I2S_DOUT, I2S_DIN);
RadioManager radio;
TaskHandle_t AudioTaskHandle = NULL;
QueueHandle_t audioQueue = NULL;

void AudioTask(void *pvParameters) {
    static constexpr size_t samplesCount = 120; 
    int16_t buffer[128] = {0}; 
  
    while(true) {
        bool state = digitalRead(BUTTON);

        if (state == LOW) { 
            Serial.println("lala"
            );
            int read = audio.readAudio(buffer, samplesCount);
            for(int i = 0; i<120; i++){
                if (buffer[i]< 300 || buffer[i]<-300){
                    buffer[i] == 0;
                }
            }
            if (read == samplesCount) {
               radio.sendAudio(peerAddress, buffer, samplesCount);  
            } 
            // audio.playAudio(buffer, samplesCount);
        //     for (int i = 0; i < samplesCount; i++) {
        //    Serial.println(buffer[i]); 
        // }s
      }
        else {
            if (xQueueReceive(audioQueue, buffer, pdMS_TO_TICKS(10)) == pdPASS) {
                audio.playAudio(buffer, samplesCount);
            }else{
                memset(buffer, 0, samplesCount * sizeof(int16_t));
        audio.playAudio(buffer, samplesCount);
            }
            
        }
    }}


void setup() {
    Serial.begin(115200);
    audio.begin();
    pinMode(BUTTON, INPUT_PULLUP);
    
    audioQueue = xQueueCreate(10, 120 * sizeof(int16_t));

    if (radio.begin(audioQueue)) {
        radio.addPeer(peerAddress);
        Serial.println("Radio initialized successfully!");
    }
    
    xTaskCreatePinnedToCore(
        AudioTask,       
        "AudioTask",     
        10000,           
        NULL,            
        1,               
        &AudioTaskHandle,
        1                
    );
}

void loop() {
    // Empty loop, operations handled by RTOS tasks
}