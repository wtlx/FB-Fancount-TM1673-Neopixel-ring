//lights the next neopixel before changing the color of the actual pixel
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <TM1637Display.h>
#include <Adafruit_NeoPixel.h>

#define PIN D7  //PIN 7 for the neopixel ring
#define CLK D2 //PIN 2 for CLK PIN
#define DIO D3 //PIN3 for DIO 

TM1637Display display(CLK, DIO); 
int delayVal = 500;
int pause = 120;
int numPixels = 16;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "xxxxxxxxx"; 
const char* password = "yyyyyyyyyy"; 


void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }

//Neopixel-Ring
strip.begin();
  strip.setBrightness(20); // 0-255
  strip.show(); // set all neopixels off


//TM1673 Display
  display.setBrightness(10); //0-15
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };  //4 segments
  display.setSegments(data);
  //Pause
  delay(delayVal);


}

//define colors
uint32_t aus = strip.Color(0, 0, 0); 
uint32_t blue = strip.Color(0, 0, 255); 
uint32_t white = strip.Color(255, 255, 255); 
uint32_t lila = strip.Color(155, 0, 255); 


void loop(){

 if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http;  
    http.begin("http://yourdomain.com/yourscript.php"); 
    int httpCode = http.GET();                                                                
    if (httpCode > 0) { 
       String payload = http.getString();  
      Serial.println(payload);                     
     int fancount = payload.toInt(); //convert sting of the payload to an int
      display.showNumberDec(fancount, false, 4, 4); //Display the number of fans
    } 
    http.end();   //Close connection
  }



//first round, just for fun
 for(uint16_t i=15; i>=0; i--) { //count pixel (unfortunately counting down because I want my counter going clockwise)
      strip.setPixelColor(i, lila); 
      strip.show();
      delay(1000); //wait 1 second
      strip.setPixelColor(i, aus); 
      strip.show(); 
  Serial.println("current pixel:"); 
   Serial.println(i); 
 if (i==0){break;} //break after 1 round
  }




//from here it counts 16*16 rounds before starting the loop again



 for(uint16_t j=16; j>=0; j--){

    for(uint16_t i=15; i>=0; i--) { 
      int pre = i-1;        //define which pixel shoud be lighted additionally
      if (i==0) {pre=15;}
      
       strip.setPixelColor(i, lila); 
       strip.show(); 
       delay(1000); 
       strip.setPixelColor(pre, lila); 
       strip.show(); 
       delay(1000); 
       if (j<=i){      
            strip.setPixelColor(i, white); 
            strip.show();  
        }
        else {
            strip.setPixelColor(i, blue); 
             strip.show(); 
        }
  Serial.println("Pixel:"); 
   Serial.println(i); 
 if (i==0){break;}
  }

  Serial.println("Round:"); 
   Serial.println(j); 





 if (j==0){break;}
 }

  
}
 

  
 


  
  
  
