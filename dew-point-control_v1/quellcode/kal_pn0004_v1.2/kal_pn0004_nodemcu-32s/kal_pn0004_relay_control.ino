void relay_control()
{

  bool hilfs_luefter = luefter;


  // luefter an schalten

  if ((hum_abs_aussen <= (hum_abs_innen-1)) && (hum_aussen != 9999) && (hum_innen != 9999) && (temp_aussen > 4))
  {
    digitalWrite(luefter, HIGH);

    if (hilfs_luefter == LOW && luefter == HIGH)
    {
      luefter_start = ("Luefter start ->"+time_client.getFormattedDate());
    }
  }




  // luefter abschalten 
  if ((hum_abs_aussen >= hum_abs_innen) )
  {
    digitalWrite(luefter, LOW);

    if (hilfs_luefter == HIGH && luefter == LOW)
    {
      luefter_stop = ("Luefter stop ->"+ time_client.getFormattedDate());

      writeFile(SD,"/datalog.txt", "Luefter an:");
      writeFile(SD,"/datalog.txt", luefter_start.c_str()); 
      writeFile(SD,"/datalog.txt", "Luefter aus:");
      writeFile(SD,"/datalog.txt", luefter_stop.c_str());
      writeFile(SD,"/datalog.txt","\n");
    }
  }




  //luefter abschalten sensor fehler

  if ((hum_aussen == 9999) || (hum_innen == 9999) || (temp_aussen < 4))
  {
    digitalWrite(luefter, LOW);

    if (hilfs_luefter == HIGH && luefter == LOW)
    {
      luefter_stop = ("Luefter stop ->"+ time_client.getFormattedDate());

      writeFile(SD,"/datalog.txt", "Luefter an:");
      writeFile(SD,"/datalog.txt", luefter_start.c_str()); 
      writeFile(SD,"/datalog.txt", "Luefter aus:");
      writeFile(SD,"/datalog.txt", luefter_stop.c_str());
      writeFile(SD,"/datalog.txt","\n");
    }
  }


}