// To connect with WiFi
#include<WiFi.h>

//  To make our device as server 
#include<WebServer.h>

//  ssid , password
const char ssid[] = "Maloo Home";
const char password[] = "rpds@231180";

//  RGb led pins
byte r_pin = 15;
byte g_pin = 2;
byte b_pin = 4;

//  defining channels
#define r_channel 0
#define g_channel 1
#define b_channel 2

//  defining frequency and reolution
#define frequency 5000
#define resolution 8

//  starting a server at port 80
WebServer server(80);

void setup(){

  //  setting frequency and resolution at channels
  ledcSetup(r_channel , frequency , resolution);
  ledcSetup(g_channel , frequency , resolution);
  ledcSetup(b_channel , frequency , resolution);

  //  attaching GPIOs
  ledcAttachPin(r_pin , r_channel);
  ledcAttachPin(g_pin , g_channel);
  ledcAttachPin(b_pin , b_channel);

  //   starting serial communication
  Serial.begin(115200);

  //  connecting with the WiFi and printing IP Address
  Serial.print("Connecting with : ");
  Serial.println(ssid);
  WiFi.begin(ssid , password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with the Network !");
  Serial.print("IP address assgined by the access point : ");
  Serial.println(WiFi.localIP());

  //  Define APIs
  server.on("/" , handle_root);
  server.on("/red" , handle_red);
  server.on("/green" , handle_green);
  server.on("/blue" , handle_blue);
  server.on("/yellow" , handle_yellow);
  server.on("/cyan" , handle_cyan);
  server.on("/magenta" , handle_magenta);
  server.on("/orange" , handle_orange);  

  //  Define API, if other APIs are not found
  server.onNotFound(handle_notfound); 
  

  //  start the server
  server.begin();
  Serial.println("HTTP server started");

  
}

void loop(){

  server.handleClient();

}

void handle_root(){
  
  Serial.println("No Color");
  //  getting html
  String html = generate_html();
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_red(){
  
  Serial.println("Red Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(255,0,0);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_green(){

  Serial.println("Green Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(0,255,0);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_blue(){

  Serial.println("Blue Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(0,0,255);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_orange(){

  Serial.println("Orange Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(255,147,0);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_cyan(){

  Serial.println("Cyan Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(0,255,255);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_magenta(){

  Serial.println("Magenta Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(255,0,255);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_yellow(){

  Serial.println("Yellow Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(255,255,0);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_notfound(){

  //  sending message
  server.send(200 , "text/plain" , "Can't find anything, please try again!");
}

void color_generator(byte r , byte g , byte b){
    
  ledcWrite(r_channel , r);
  ledcWrite(g_channel , g);
  ledcWrite(b_channel , b);
}



//  generating HTML Page
String generate_html(){
  
  String html = "<!DOCTYPE html>\n";
         html += "<html lang=\"en\">\n";
         html += "<head>\n";
         html += "<meta charset=\"UTF-8\">\n";
         html += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
         html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
         html += "<title>ESP32 RGB CONTROLLER</title>\n";
         html += "</head>\n";
         html += "<body>\n";
         html += "<div style=\"padding-left: 50%; padding-top: 10%;\">\n";
         html += "<h1>COLOR GENERATOR</h1>\n";
         html += "</div>\n";

         html += "<div style=\"padding-left: 40%;\">\n";
         html += "<a href=\"/red\"><button>Red</button></a>\n";
         html += "<a href=\"/green\"><button>Green</button></a>\n";
         html += "<a href=\"/blue\"><button>Blue</button></a>\n";
         html += "<a href=\"/yellow\"><button>Yellow</button></a>\n";
         html += "<a href=\"/cyan\"><button>Cyan</button></a>\n";
         html += "<a href=\"/magenta\"><button>Magenta</button></a>\n";
         html += "<a href=\"/orange\"><button>Orange</button></a>\n";
         html += "</div>\n";
    
         html += "</body>\n";
         html += "</html>\n";

  return html;
}
