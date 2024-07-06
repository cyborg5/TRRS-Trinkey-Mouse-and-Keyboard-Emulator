#if (MY_DEBUG)
  #define DEBUG_PRINT(s)  Serial.print(s);
  #define DEBUG_PRINTLN(s) Serial.println(s);
  #define DEBUG_WRITE(c)  Serial.write(c);
#else
  #define DEBUG_PRINT(s)  
  #define DEBUG_PRINTLN(s) 
  #define DEBUG_WRITE(c)
#endif
