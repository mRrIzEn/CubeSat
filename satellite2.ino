/* 
DIY Satellite Project
 
*/

int Batt1 = 7.4;// Initialize & Globalize Battery One Level

struct t_mtab { char c, pat; } ;

struct t_mtab morsetab[] = {
    {'.', 106},
  {',', 115},
  {'?', 76},
  {'/', 41},
  {'A', 6},
  {'B', 17},
  {'C', 21},
  {'D', 9},
  {'E', 2},
  {'F', 20},
  {'G', 11},
  {'H', 16},
  {'I', 4},
  {'J', 30},
  {'K', 13},
  {'L', 18},
  {'M', 7},
  {'N', 5},
  {'O', 15},
  {'P', 22},
  {'Q', 27},
  {'R', 10},
  {'S', 8},
  {'T', 3},
  {'U', 12},
  {'V', 24},
  {'W', 14},
  {'X', 25},
  {'Y', 29},
  {'Z', 19},
  {'1', 62},
  {'2', 60},
  {'3', 56},
  {'4', 48},
  {'5', 32},
  {'6', 33},
  {'7', 35},
  {'8', 39},
  {'9', 47},
  {'0', 63}
} ;

#define N_MORSE  (sizeof(morsetab)/sizeof(morsetab[0]))

#define SPEED  (35)  //default 12 25 still stable 35 working
#define DOTLEN  (1200/SPEED)
#define DASHLEN  (3*(1200/SPEED))

int LEDpin = 3; //Needs to be PWM pin

void
dash()
{
  analogWrite(LEDpin, 128) ;//128 default
  delay(DASHLEN);
  analogWrite(LEDpin, 0) ;
  delay(DOTLEN) ;
}

void
dit()
{
  analogWrite(LEDpin, 128) ;//128 default
  delay(DOTLEN);
  analogWrite(LEDpin, 0) ;
  delay(DOTLEN);
}

void
send(char c)
{
  int i ;
  if (c == ' ') {
    Serial.print(c) ;
    delay(7*DOTLEN) ;
    return ;
  }
  for (i=0; i<N_MORSE; i++) {
    if (morsetab[i].c == c) {
      unsigned char p = morsetab[i].pat ;
      Serial.print(morsetab[i].c) ;

      while (p != 1) {
          if (p & 1)
            dash() ;
          else
            dit() ;
          p = p / 2 ;
      }
      delay(2*DOTLEN) ;
      return ;
    }
  }
  /* if we drop off the end, then we send a space */
  Serial.print("?") ;
}

void
sendmsg(char *str)
{
  while (*str)
    send(*str++) ;
  Serial.println("");
}

#include <avr/wdt.h>
void setup() {
  wdt_disable();
  wdt_enable (WDTO_8S);//watchdog
  pinMode(LEDpin, OUTPUT) ;
  Serial.begin(9600) ; //serial unnecessary except debugging as needed
  Serial.println("Eric's Arduino Satellite CW Downlink") ;
  Serial.println("by Eric William") ;
  Serial.println("www.mkmer.org") ;
  //Serial.println("") ;
}

void loop() {
  wdt_reset ();//Reset Watchdog
  Transmit();
 }

void Transmit(){//Make sure these are all CAPS or will not TX
   sendmsg("AURORA1 SAT/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("OS,OK/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("SAFEMODE,NO/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("WATCHDOG,4/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("ITEMP,0C/ ") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("LUX,22/ ") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("TELEMETRY,OK/ ") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("ANTENNA,DEP/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("PV,520MV/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("BATT1,620MV/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("BUSA,4MA/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("RSSI,4DBM/") ;
   wdt_reset ();//Reset Watchdog
   sendmsg("WWW.MKME.ORG...") ; //All this code needs to be replaced with the INT to CHAR values from monitoring/systems
   //sendmsg (Batt1);
  delay(3000) ;
}
void Batt(){
  //input battery check/monitoring code here
}
void Watchdog(){
  //input Watchdog code here
}
void Solar(){
  //input Solar Cell monitoring & code here
}
