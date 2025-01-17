void relay_control()
{

  // luefter an schalten

  if ((hum_abs_aussen <= (hum_abs_innen-1)) && (hum_aussen != 9999) && (hum_innen != 9999) && (temp_aussen > 4))
  {
    digitalWrite(luefter, HIGH);

  }




  // luefter abschalten 
  if ((hum_abs_aussen >= hum_abs_innen) )
  {
    digitalWrite(luefter, LOW);

  }




  //luefter abschalten sensor fehler

  if ((hum_aussen == 9999) || (hum_innen == 9999) || (temp_aussen < 4))
  {
    digitalWrite(luefter, LOW);

  }


}