void webserver()
{
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
   
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client

    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
           
            
            // Display the HTML web page
           
           client.println(" <!DOCTYPE html><html><head><title>Luftfeuchtigkeit</title><style>body {background-color: #333333;}");
           client.println(" h1 {font-size: 3em;color: rgb(245, 245, 245);font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;text-align: center;background-color: #2f4f4f;padding: 20px;}");
           client.println(".box {display: inline-block;width: 45%;height: 200px;margin: 20px;background-color: #add8e6;box-shadow: 5px 5px 5px #000000;padding: 10px;border-radius: 40px;}");
           client.println(".box h2 {font-size: 2em;margin-bottom: 20px;font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;text-align: center;}");
           client.println(".box p {font-size: 2em;margin: 0;font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;text-align: center;}");
           client.println(".box2 {display: inline-block;width: 45%;height: 200px;margin: 20px;background-color: #add8e6;box-shadow: 5px 5px 5px #000000;padding: 10px;border-radius: 40px;}");
           client.println(".box2 h2 {font-size: 2em;margin-bottom: 20px;font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;text-align: center;}");
           client.println(".box2 p {font-size: 2em;margin: 0;font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;text-align: center;}");
           client.println(" </style></head><body> <h1>Keller Lueftung</h1>");
           client.println(" <div class=\"box\"><h2>Luftfeuchtigkeit abs. innen:</h2><p>"+ str_abs_hum_innen +" g/m3"+"</p></div>");
           client.println(" <div class=\"box\"><h2>Luftfeuchtigkeit abs. aussen:</h2><p>"+ str_abs_hum_aussen +" g/m3"+"</p></div>");
           client.println(" <div class=\"box2\"><h2>Temperatur innen:</h2><p>"+ str_temp_innen +"</p></div>");
           client.println("<div class=\"box2\"><h2>Temperatur aussen:</h2><p>"+ str_temp_aussen +"</p></div></body></html>");
           
           
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }



}