
void clockSet(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second) {
  RtcDateTime currentTime = RtcDateTime(year,month,day,hour,minute,second);
  rtcObject.SetDateTime(currentTime);
}

RtcDateTime clockGetDateTime(){
  return rtcObject.GetDateTime();
}

unsigned long lastClockPrintMillis;
void clockTimePrint(){
  if(currentMillis - lastClockPrintMillis >= 1000){
  
  RtcDateTime currentTime = rtcObject.GetDateTime();
  char str[20];
  
  sprintf(str, "%d/%d/%d %02d:%02d:%02d",
          currentTime.Year(),   //get year method
          currentTime.Month(),  //get month method
          currentTime.Day(),    //get day method
          currentTime.Hour(),   //get hour method
          currentTime.Minute(), //get minute method
          currentTime.Second()  //get second method
         );
 
  Serial.println(str); //print the string to the serial port
  lastClockPrintMillis = currentMillis;
  }
}

float clockGetTemp(){
  RtcTemperature currentTemp = rtcObject.GetTemperature();
  return currentTemp.AsFloatDegC();
}

