void get_value_aussen ()
{
 sensors_event_t event;

 // sensordaten lesen temperatur

  dht_aussen.temperature().getEvent(&event);

  if (isnan(event.temperature))
   {
    Serial.println((time_client.getFormattedDate() +": "+"Error reading temperature outside!"));
    Serial.println();
    Serial.println();
    str_temp_aussen = "Error reading temperature outside!";
    temp_aussen =9999;
   }

  else 
  { 
   temp_aussen = event.temperature;
   str_temp_aussen = String(temp_aussen);;
  }

  



   // sensordaten lesen luftfeuchtigkeit
   
  dht_aussen.humidity().getEvent(&event);

  if (isnan(event.relative_humidity)) 
  {
    Serial.println((time_client.getFormattedDate() +": "+"Error reading humidity outside!"));
    Serial.println();
    Serial.println();
    str_hum_aussen = "Error reading humidity outside!";
    hum_aussen =9999;
  }

  else
  {
   hum_aussen = event.relative_humidity;
   str_hum_aussen = String(hum_aussen); 

  Serial.println(("sensor aussen:"));
  Serial.print  (("temperatur: ")); 
  Serial.print  (time_client.getFormattedDate() +"-> "+ temp_aussen+"°C");
  Serial.println();
  
  Serial.print  (("luftfeuchtigkeit: "));
  Serial.print  (time_client.getFormattedDate() +"-> " + hum_aussen+"%");

  Serial.println();
  Serial.println();
  }
}