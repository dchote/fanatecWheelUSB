#include "WProgram.h"
#include "Arduino.h"

#include "fanatec.h"

void setup();
void loop();

void init_wheel();
void whClear();
void whSetId(unsigned int val);

csw_in_t csw_in;
csw_out_t csw_out;

csl_in_t csl_in;
csl_out_t csl_out;

mcl_in_t mcl_in;
mcl_out_t mcl_out;

bool bt_connected;
bool show_fwvers;

uint32_t timing;
uint32_t timing_bt;
uint32_t disp_timout;


void setup() {
  fsetup();
	
  whClear();
  
  // prebuild output packet
  memset(csw_out.raw, 0, sizeof(csw_out_t));
  memset(csl_out.raw, 0, sizeof(csl_out_t));
  memset(mcl_out.raw, 0, sizeof(mcl_out_t));
  
  csw_out.header = 0xa5;
  mcl_out.header = 0xa5;
  csw_out.id = 0x00;
  
  Serial.begin(115200);
  Serial.println("MCU Ready");
	
  for (int i = 0; i < 10; ++i) {
    delay(100);
    Serial.print(".");
    /* code */
  }
  
  Serial.println("check for active connection...");
  
  fwelcome();
  
  timing = micros();
}

void loop() {
  switch(detectWheelType()) {
    case CSW_WHEEL:
      Serial.println("CSW Wheel");
      transferCswData(&csw_out, &csw_in, sizeof(csw_out.raw));
      
      init_wheel();
      
      Serial.print("CSW_IN:");
      for (int i=0; i<sizeof(csw_in.raw); i++) {
         Serial.print(csw_in.raw[i], HEX);
         Serial.print(":");
       }
       Serial.println();
       
       whSetId(csw_in.id);
      break;
    case CSL_WHEEL:
      Serial.println("CSL Wheel");
      
      transferCslData(&csl_out, &csl_in, sizeof(csl_out.raw), 0x00);
      whSetId(CSLP1XBOX);
      
      init_wheel();
      
      csl_out.disp = csw7segToCsl(csw_out.disp[0]);
      transferCslData(&csl_out, &csl_in, sizeof(csl_out.raw), 0x41);
      
      csl_out.disp = csw7segToCsl(csw_out.disp[1]);
      transferCslData(&csl_out, &csl_in, sizeof(csl_out.raw), 0x02);
      
      csl_out.disp = csw7segToCsl(csw_out.disp[2]);
      transferCslData(&csl_out, &csl_in, sizeof(csl_out.raw), 0x44);
      
      csl_out.disp = cswLedsToCsl(csw_out.leds);
      transferCslData(&csl_out, &csl_in, sizeof(csl_out.raw), 0x08);
      
      break;
    case MCL_WHEEL:
      Serial.println("MCL Wheel");
      
      transferMclData(&mcl_out, &mcl_in, sizeof(mcl_out.raw));
      
      init_wheel();
      
      whSetId(mcl_in.id);
      
      Serial.print("MCL_IN:");
      for (int i=0; i<sizeof(mcl_in.raw); i++) {
        Serial.print(mcl_in.raw[i], HEX);
        Serial.print(":");
      }
      Serial.println();
      
      break;
    default:
      Serial.println("No or Unknown Wheel");
      //fwelcome();
      whClear();
    }
    
    delay(5000);
}

void init_wheel() {
  if (disp_timout == 0) {
    // start showing fw vers
    if (detectWheelType() == MCL_WHEEL) {
      String fw_vers = String(mcl_in.fwvers);
      
      mcl_out.raw[1] = 0x11;
      // Erase all
      mcl_out.raw[2] = 0x0A;
      mcl_out.raw[3] = 0x0A;
      mcl_out.raw[4] = 0x0A;
      //
      mcl_out.raw[2] = fw_vers.charAt(0);
      
      if (fw_vers.length()>1) {
        mcl_out.raw[3] = fw_vers.charAt(1);
      }
        
      if (fw_vers.length()>2) {
        mcl_out.raw[4] = fw_vers.charAt(2);
      }
    } else {
      String fw_vers = String(csw_in.fwvers);
      
      if (csw_in.id == CSLMCLGT3) {
        csw_out.raw[1] = 0x11;
        // Erase all
        csw_out.raw[2] = 0x0A;
        csw_out.raw[3] = 0x0A;
        csw_out.raw[4] = 0x0A;
        //
        csw_out.raw[2] = fw_vers.charAt(0);
        
        if (fw_vers.length()>1) {
          csw_out.raw[3] = fw_vers.charAt(1);
        }
        
        if (fw_vers.length()>2) {
          csw_out.raw[4] = fw_vers.charAt(2);
        }
      } else {
        // TODO: AsciiTo7seg conversion
        csw_out.disp[0] = 0x00;
        csw_out.disp[1] = 0x00;
        csw_out.disp[2] = 0x00;
      }
    }
    
    disp_timout = millis();
  } else if(millis() - disp_timout >= 4000) {
    // stop
    show_fwvers = false;
    
    mcl_out.raw[1] = 0x11;
    mcl_out.raw[2] = 0x0A;
    mcl_out.raw[3] = 0x0A;
    mcl_out.raw[4] = 0x0A;
    mcl_out.raw[9] = 0x00;
    
    if (csw_in.id == CSLMCLGT3) {
      csw_out.raw[1] = 0x11;
      csw_out.raw[2] = 0x0A;
      csw_out.raw[3] = 0x0A;
      csw_out.raw[4] = 0x0A;
    }
  }
}

void whSetId(unsigned int val) {
  csw_out.id = val & 0xFF;
}

void whClear(){
  whSetId(NO_RIM);
  
  show_fwvers = true;
  disp_timout = 0;
}