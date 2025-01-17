void hum_abs ()
{
  // koeffizienten aussen bestimmen
 if (temp_aussen >= 0)
  {
   a_aussen = 7.5;
   b_aussen = 237.4;
  }
  else
  {
   a_aussen = 7.6;
   b_aussen = 240.7;
  }
  // koeffizienten innen bestimmen
 if (temp_innen >= 0)
  {
   a_innen = 7.5;
   b_innen = 237.4;
  }
  else
  {
   a_innen = 7.6;
   b_innen = 240.7;
  }

  // umrechnung rel. luftfeuchte in abs. luftfeuchte
  
  DD_aussen = (hum_aussen/100)*(6.1078*pow(10,((a_aussen*temp_aussen)/(b_aussen+temp_aussen))));
  DD_innen = (hum_innen/100)*(6.1078*pow(10,((a_innen*temp_innen)/(b_innen+temp_innen))));

  hum_abs_aussen = (100000*(Mw/Ur)*DD_aussen)/(temp_aussen + 273.15);
  hum_abs_innen = (100000*(Mw/Ur)*DD_innen)/(temp_innen + 273.15);
  str_abs_hum_innen = String(hum_abs_innen);
  str_abs_hum_aussen = String(hum_abs_aussen); 

}