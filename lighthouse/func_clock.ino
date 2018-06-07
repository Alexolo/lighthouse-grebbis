unsigned long lastClockPrintMillis;

void clockSet(int unixTime) {
  // Subtract 946684800 as RtcDateTime uses time from 2000/01/01 00:00:00
  RtcDateTime currentTime = RtcDateTime(unixTime - 946684800);
  rtcObject.SetDateTime(currentTime);
}

RtcDateTime clockGetDateTime(){
  return rtcObject.GetDateTime();
}

void clockPrintTime(){
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

