#pragma region Bibliotecas

  #include <Arduino.h>
  #include <ESP8266WiFi.h>

#pragma endregion

#pragma region Wifi

  const char* ssid = "";
  const char* password = "";

#pragma endregion

#pragma region Variaveis

  IPAddress ip(x,x,x,x);
  IPAddress gateway(x,x,x,x); 
  IPAddress subnet(x,x,x,x); 

  byte led = 2;

  WiFiServer server(80);

#pragma endregion

#pragma region Declaracao de funcoes

  bool conexao();

#pragma endregion

void setup(){

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  delay(10);
  digitalWrite(led, HIGH);
  Serial.println("");

  bool statusConexao =  conexao();

  if(statusConexao){

    Serial.println("");
    Serial.print("Conectado a rede sem fio ");
    Serial.println(ssid); 
    server.begin();
    Serial.println("Servidor iniciado");

  }

  else{

    Serial.println("Nao deu");
    delay(1000);
    return setup();

  }

}

void loop(){

  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>PAGINA OK</h1>");
  client.println("</html>");

}

bool conexao(){

  Serial.print("Conectando a ");
  Serial.print(ssid);

  byte tentativa = 1;
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){

    Serial.println("");
    Serial.print("tentativa: ");
    Serial.print(tentativa);
    tentativa++;
    delay(1000);

    if(tentativa >= 11){

      Serial.println("");
      return false;

    }

  }

  WiFi.config(ip, gateway, subnet);

  digitalWrite(led, LOW);
  return true;

}