void datalogging()
{
  if ((millis()-timer) >= 1800000 )
  {
    // uhrzeit und messdaten hintereinanderhängen
    String data_aussen = time_client.getFormattedDate()+"-> "+ str_hum_aussen.c_str();
    String data_innen = time_client.getFormattedDate()+"-> "+ str_hum_innen.c_str();

  // schreiben der einzelnen messungen
    writeFile(SD,"/datalog.txt", "Luftfeuchtigkeit aussen: ");
    writeFile(SD,"/datalog.txt", data_aussen.c_str()); 
    writeFile(SD,"/datalog.txt","\n");
    writeFile(SD,"/datalog.txt", "Luftfeuchtigkeit innen: ");
    writeFile(SD,"/datalog.txt",data_innen.c_str()); 
    writeFile(SD,"/datalog.txt","\n");

    timer = millis();
  }
}

// funktion zum sd karte schreiben

void writeFile(fs::FS &fs, const char * path, const char * message){
 
  
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.println(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
   
}


   