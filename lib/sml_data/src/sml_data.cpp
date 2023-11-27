#include <sml_data.h>

#undef DEBUG 

double T1Wh = -2;
double SumWh = -2; 
double T1cur = -2;
double T1cur_old = -2;

char sml_data[MAX_BUF_SIZE];
unsigned char manuf[MAX_STR_MANUF];
char floatBuffer[20];

void PowerT1(){ 
  smlOBISWh(T1Wh); 
}

void PowerSum(){ 
  smlOBISWh(SumWh); 
}

void PowerCur(){ 
  smlOBISW(T1cur); 
}

void Manufacturer(){
  smlOBISManufacturer(manuf, MAX_STR_MANUF); 
}

// clang-format off
OBISHandler OBISHandlers[] = {
  {{ 0x81, 0x81, 0xc7, 0x82, 0x03, 0xff }, &Manufacturer}, /* 129-129:199.130.3*255 */
  {{ 0x01, 0x00, 0x01, 0x08, 0x01, 0xff }, &PowerT1},      /*   1-  0:  1.  8.1*255 (T1) */
  {{ 0x01, 0x00, 0x01, 0x08, 0x00, 0xff }, &PowerSum},     /*   1-  0:  1.  8.0*255 (T1 + T2) */
  {{ 0x01, 0x00, 0x10, 0x07, 0x00, 0xff }, &PowerCur},     /*   1-  0: 16.  7.0*255 (Power currenctly W) */
  {{ 0, 0 }}
};

void init_sml_data(){
 //Implemenation
}

void read_sml_data(){
  
  unsigned int i = 0, iHandler = 0;
  unsigned char c;
  sml_states_t s;
  bool new_data = false;

  if(Serial.available() > 0){
    Serial.readBytes(sml_data,sizeof(sml_data));

    new_data = true;
  }

  if (new_data == true) {

    //Serial.println("new data");

    for (i = 0; i < sizeof(sml_data); ++i) {
      c = sml_data[i];
      s = smlState(c);
      if (s == SML_START) {
        //Serial.println("SML_START");
        /* reset local vars */
        T1Wh = -3;
        SumWh = -3;
      }
      if (s == SML_LISTEND) {
        //Serial.println("SML_LISTEND");
        /* check handlers on last received list */
        for (iHandler = 0; OBISHandlers[iHandler].Handler != 0 &&
                           !(smlOBISCheck(OBISHandlers[iHandler].OBIS));
             iHandler++)
             ;
        if (OBISHandlers[iHandler].Handler != 0) {
          OBISHandlers[iHandler].Handler();
          //Serial.println("Handler");
        }
      }
      
      if (s == SML_UNEXPECTED) {
        //Serial.print(F(">>> Unexpected byte! <<<\n"));
      }

      if (s == SML_FINAL) {

        //Serial.print(F("Power Currently    (1-0:16.7.0)..: "));
        dtostrf(T1cur, 10, 3, floatBuffer);
        //Serial.println(floatBuffer);
        
#if defined(DEBUG)        
        Serial.println("SML_FINAL");

        Serial.print(F(">>> Manufacturer :"));
        Serial.print((char *)manuf);
        Serial.print(F("\n")); 
        
        Serial.print(F("Power T1    (1-0:1.8.1)..: "));
        dtostrf(T1Wh, 10, 3, floatBuffer);
        Serial.print(floatBuffer);
        Serial.print(F("\n"));

        Serial.print(F("Power T1+T2 (1-0:1.8.0)..: "));
        dtostrf(SumWh, 10, 3, floatBuffer);
        Serial.print(floatBuffer);
        Serial.print(F("\n"));

        Serial.print(F("Power Currently    (1-0:16.7.0)..: "));
        dtostrf(T1cur, 10, 3, floatBuffer);
        Serial.print(floatBuffer);
        Serial.print(F("\n\n\n\n"));
#endif      
      }

    }
    new_data = false;
  }
}