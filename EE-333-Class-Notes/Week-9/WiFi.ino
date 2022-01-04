// Basic Arduino & ESP8266 webserver
//
// uses AltSoftSerial download from https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
// this can be replaced with the normal software serial
 
 
#include <SoftwareSerial.h> 
// Arduino pin 08 for RX
// Arduino Pin 09 for TX
 
SoftwareSerial espSerial(8, 9);
 
 
const bool printReply = true;
const char line[] = "-----\n\r";
int loopCount=0;
 
char html[256];
char command[20];
char reply[500]; // you wouldn't normally do this
 
char ipAddress [20];
char name[30];
int lenHtml = 0;
char temp[5];
 
 
void setup()
{
      Serial.begin(9600);
      Serial.println("Start\r\n\r\n");
 
      espSerial.begin(9600);
 
      // reset the ESP8266
      Serial.println("reset the module"); 
      espSerial.print("AT+RST\r\n");
      getReply( 2000 );
 
      // configure as a station
      Serial.println("Change to station mode"); 
      espSerial.print("AT+CWMODE=1\r\n");
      getReply( 1500 );

      // connect to the network. Uses DHCP. ip will be assigned by the router.
      Serial.println("Connect to a network ");
 
     // Enter the SSID and password for your own network
      espSerial.print("AT+CWJAP=\"EE435\",\"EMBEDDED\"\r\n");
      getReply( 6000 );
 
 
      // get ip address
      Serial.println("Get the ip address assigned by the router"); 
      espSerial.print("AT+CIFSR\r\n");
      getReply( 5000 );

      // parse ip address.
      int len = strlen( reply ); 
      bool done=false;
      bool error = false;
      int pos = 0;
      while (!done)
      {
           if ( reply[pos] == 10) {
              done = true;
           } 
           pos++;
           if (pos > len) { 
              done = true;
              error = true;
           }
      }
 
      if (!error)
      {
            int buffpos = 0;
            done = false;
            while (!done)
            {
               if ( reply[pos] == 13 ) { 
                  done = true;
               }
               else { 
                  ipAddress[buffpos] = reply[pos];
                  buffpos++; pos++;
               }
            }
            ipAddress[buffpos] = 0;
      }
      else { 
        strcpy(ipAddress,"ERROR");
      }
 
 
 
      // configure for multiple connections
      Serial.println("Set for multiple connections"); 
      espSerial.print("AT+CIPMUX=1\r\n");
      getReply( 1500 );
 
 
      // start server on port 80
      Serial.println("Start the server"); 
      espSerial.print("AT+CIPSERVER=1,80\r\n");
      getReply( 1500 );
 
      Serial.println("");
 
 
      Serial.println("Waiting for page request");
      Serial.print("Connect to "); 
      Serial.println(ipAddress);
      Serial.println("");
}
 
int web_delay = 2000;
 
void loop()
{
      if(espSerial.available()) // check if the ESP8266 is sending data
      {
          // this is the +IPD reply - it is quite long. 
          // normally you would not need to copy the whole message in to a variable you can copy up to "HOST" only
          // or you can just search the data character by character as you read the serial port.
          getReply( 2000 );      
 
 
          bool foundIPD = false;
          for (int i=0; i<strlen(reply); i++)
          {
               if (  (reply[i]=='I') && (reply[i+1]=='P') && (reply[i+2]=='D')   ) { foundIPD = true;    }
          }
 
 
          if ( foundIPD  )  
          {
 
              loopCount++;
              // Serial.print( "Have a request.  Loop = ");  Serial.println(loopCount); Serial.println(""); 
 
 
              // check to see if we have a name - look for name=
              bool haveName = false;
              int nameStartPos = 0;
              for (int i=0; i<strlen(reply); i++)
              {
                   if (!haveName) // just get the first occurrence of name
                   {
                         if (  (reply[i]=='n') && (reply[i+1]=='a') && (reply[i+2]=='m') && (reply[i+3]=='e')  && (reply[i+4]=='=') ) 
                         { 
                             haveName = true;
                             nameStartPos = i+5;
                         }
                   }     
              }
 
              // get the name - copy everything from nameStartPos to the first space character
              if (haveName)
              {
                    int tempPos = 0;
                    bool finishedCopying = false;
                    for (int i=nameStartPos; i<strlen(reply); i++)
                    {
                         if ( (reply[i]==' ') && !finishedCopying ) { 
                            finishedCopying = true;  
                         } 
                         if ( !finishedCopying ) { 
                            name[tempPos] = reply[i];
                            tempPos++;
                         }
                    }              
                    name[tempPos] = 0;
              }
 
              if (haveName) { 
                Serial.print( "name = ");  
                Serial.println(name); 
                Serial.println(""); 
              }
              else { 
                Serial.println( "no name entered");   
                Serial.println("");
              }
 
 
 
              // start sending the HTML
 
              strcpy(html,"<html><head></head><body>");
              strcat(html,"<h1>ESP8266 Webserver</h1>");
              strcat(html,"<p>Served by Arduino and ESP8266</p>");
              strcat(html,"<p>Request number ");
              itoa( loopCount, temp, 10);
              strcat(html,temp);
              strcat(html,"</p>");
  
             if (haveName)
             {
                  // write name
                  strcat(html,"<p>Your name is "); 
                  strcat(html, name ); 
                  strcat(html,"</p>");                          
             }

              // Send the command to ESP8266
              lenHtml = strlen( html );
              itoa(lenHtml, temp, 10);

              strcpy(command,"AT+CIPSEND=0,");
              strcat(command,temp);
              strcat(command,"\r\n");

              espSerial.print(command);
              getReply( web_delay );          
              espSerial.print(html);
              getReply( web_delay );    

              
              // Construct the name entry box
              strcpy(html,"<form action=\""); 
              strcat(html, ipAddress); 
              strcat(html, "\" method=\"GET\">"); 
              strcat(html,"Name:<br><input type=\"text\" name=\"name\">");  // new
              strcat(html,"<input type=\"submit\" value=\"Submit\"></form>");  //new
              strcat(html,"</body></html>");  // new

               // Send the command to ESP8266
              lenHtml = strlen( html );
              itoa( lenHtml, temp, 10);
              strcpy(command,"AT+CIPSEND=0,"); 
              itoa( lenHtml, temp, 10); 
              strcat(command, temp);  
              strcat(command, "\r\n");
 
              espSerial.print(command);
              getReply( web_delay ); 
              espSerial.print(html);
              getReply( web_delay ); 
 
              // close the connection
              espSerial.print( "AT+CIPCLOSE=0\r\n" );
              getReply( web_delay );            

 
 
          } // if(espSerial.find("+IPD"))
      } //if(espSerial.available())
 
 
      delay (100);
 
      // drop to here and wait for next request.
 
}
 
 
void getReply(int wait)
{
    int tempPos = 0;
    long int time = millis();
    char c;
    boolean complete_flag = 0;
    
    while( (time + wait) > millis() && !complete_flag)
    {
        while(espSerial.available())
        {
            c = espSerial.read(); 
            if (tempPos < 500) { 
               reply[tempPos] = c; 
               tempPos++;  
            }
            if((reply[tempPos-2] == 'O' && reply[tempPos-1] == 'K') || (reply[tempPos-2] == '\n' && reply[tempPos-1] == '>')) {
              complete_flag = 1;
              break;
            }
        }
        reply[tempPos] = 0;  //NULL
    }


    //Serial.println(millis()-time);
   

    if (printReply) { 
      Serial.println( reply );  
      Serial.println(line);     }
}
