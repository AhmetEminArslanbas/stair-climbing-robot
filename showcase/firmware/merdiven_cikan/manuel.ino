

void manuel()
{
  veri_oku();

  digitalWrite(led_r, HIGH);
    digitalWrite(led_g, LOW);
    digitalWrite(led_b, LOW);

  

  if(btn_x == 2) // kolu aşa yap
  {
    if(millis() - kol_zaman > 1)
    {
      kol_derece += kol_speed * 10;
      kol_zaman = millis();
    }
  }
  else if(btn_b == 2) // kolu yukarı yap
  {
    if(millis() - kol_zaman > 1)
    {
      kol_derece -= kol_speed * 10;
      kol_zaman = millis();
    }
  }
  kol_derece = constrain(kol_derece, 512, 812);
  //Serial.println(kol_derece);
  ax12a.moveSpeed(9, kol_derece, 1000);
  //Serial.print(rt);
  //Serial.print("   ");
  
  //eğlence modu kolları stikler kontrolü
  /*ax12a.moveSpeed(5, map(rt, 100, 200, 512, 850), 300);
  ax12a.moveSpeed(6, map(rt, 100, 200, 512, 170), 300);

  ax12a.moveSpeed(7, map(lt, 100, 200, 512, 200), 300);
  ax12a.moveSpeed(8, map(lt, 100, 200, 512, 820), 300);*/

  if(throttle_2 == 100)
    {
      if(millis() - yukseklik_zaman > 1)
      {
        el_1_derece += btn_rb * el_speed * 10;
        el_1_derece -= btn_lb * el_speed * 10;

        el_2_derece -= btn_rb * el_speed * 10;
        el_2_derece += btn_lb * el_speed * 10;
      }

      el_1_derece = constrain(el_1_derece, 512, 762);
      el_2_derece = constrain(el_2_derece, 262, 512);
    }
    else
    {
      el_1_derece = map(throttle_2, 0, 200, 332, 512);
      el_2_derece = map(throttle_2, 0, 200, 672, 512);
    }

    /*ax12a.moveSpeed(5, el_2_derece, 300);
    ax12a.moveSpeed(6, el_1_derece, 300);

    ax12a.moveSpeed(7, el_1_derece, 300);
    ax12a.moveSpeed(8, el_2_derece, 300);*/

    float motor_5_power = el_2_derece + map(rt, 100, 200, 0, 400);
    float motor_6_power = el_1_derece - map(rt, 100, 200, 0, 400);
    float motor_7_power = el_1_derece - map(lt, 100, 200, 0, 400);
    float motor_8_power = el_2_derece + map(lt, 100, 200, 0, 400);

    motor_5_power = constrain(motor_5_power, 0, 1000);
    motor_6_power = constrain(motor_6_power, 0, 1000);
    motor_7_power = constrain(motor_7_power, 0, 1000);
    motor_8_power = constrain(motor_8_power, 0, 1000);


    ax12a.moveSpeed(5, motor_5_power, 300);
    ax12a.moveSpeed(6, motor_6_power, 300); //map(rt, 100, 200, el_1_derece, 262), 300);

    ax12a.moveSpeed(7, motor_7_power, 300); //map(lt, 100, 200, el_1_derece, 262), 300);
    ax12a.moveSpeed(8, motor_8_power, 300);
  

  
  if(btn_y == 2) // manuelden çık
  {
    manuel_durum = false;
  }

  if(btn_a == 2) // manuele gir
  {
    manuel_durum = true;
  }

  if(btn_right == 2)
  {
    donus_speed = 3;
  }
  else
  {
    donus_speed = 6;
  }



  int sag_teker = 0;
  int sol_teker = 0;

  sag_teker = ((throttle - 100) * ileri_speed) + ((-(rol - 100)) * donus_speed);
  sol_teker = ((throttle - 100) * ileri_speed) - ((-(rol - 100)) * donus_speed);
  
  /*Serial.print("sol_teker: ");
  Serial.print(sol_teker);
  Serial.print("   sag_teker: ");
  Serial.println(sag_teker);*/
  hareket(sol_teker, sag_teker);
}

void veri_oku()
{
  if(hc06.parseInt() == 256)
  {
    hc06.readBytes(araci_veri, 16);
    if(araci_veri[5] == (byte)(araci_veri[2] / 2) + (araci_veri[3] / 2))
    {
      throttle = araci_veri[2];
      rol = araci_veri[3];

      rt = araci_veri[6];
      lt = araci_veri[7];
      
      btn_y = araci_veri[8];
      btn_x = araci_veri[9];
      btn_b = araci_veri[10];
      btn_a = araci_veri[11];

      btn_rb = araci_veri[12];
      btn_lb = araci_veri[13];

      btn_right = araci_veri[14];

      throttle_2 = araci_veri[15];
    }
    /*Serial.print(araci_veri[0]);
      Serial.print(" ");
      Serial.print(araci_veri[1]);
      Serial.print(" ");
      Serial.print(araci_veri[2]);
      Serial.print(" ");
      Serial.print(araci_veri[3]);
      Serial.print(" ");
      Serial.print(araci_veri[4]);
      Serial.print(" ");
      Serial.print(araci_veri[5]);
      Serial.print(" ");
      Serial.print(araci_veri[6]);
      Serial.print(" ");
      Serial.print(araci_veri[7]);
      Serial.print(" ");
      Serial.print(araci_veri[8]);
      Serial.println(" ");
      Serial.print(araci_veri[9]);
      Serial.println(" ");*/
      
    
  }
}