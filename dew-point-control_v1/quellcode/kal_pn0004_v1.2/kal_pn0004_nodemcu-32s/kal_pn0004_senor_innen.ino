void get_value_innen ()
{
  sensors_event_t event;


  // sensordaten lesen temperatur

  dht_innen.temperature().getEvent(&event);
  
  if (isnan(event.temperature))
   {
    Serial.println((time_client.getFormattedDate() +"Error reading temperature inside!"));
    Serial.println();
    Serial.println();
    str_temp_innen = "Error reading temperature inside!";
    temp_innen = 9999;
   }

  else 
  { 
   temp_innen = event.temperature;
   str_temp_innen = String(temp_innen);;
  }

  
  
  // sensordaten lesen luftfeuchtigkeit

   dht_innen.humidity().getEvent(&event);

  if (isnan(event.relative_humidity)) 
  {
    Serial.println((time_client.getFormattedDate() +": " +"Error reading humidity inside!"));
    Serial.println();
    Serial.println();

    str_hum_innen = "Error reading humidity inside!";
    hum_innen =9999;
  }

  else
  {
   hum_innen = event.relative_humidity;
   str_hum_innen = String(hum_innen);

   Serial.println(("sensor innen:"));
   Serial.print  (("temperatur: ")); 
   Serial.print  (time_client.getFormattedDate() +"-> " + temp_innen+"°C");
   Serial.println();
   Serial.print  (("luftfeuchtigkeit: "));
   Serial.print  (time_client.getFormattedDate() +"-> " +hum_innen+"%");
   Serial.println();
   Serial.println();
  }
}