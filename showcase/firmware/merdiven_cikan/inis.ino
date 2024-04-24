void inis()
{
alt_mesafe=alt_sensor.ping_cm();
delay(10);
while(alt_mesafe<20 and alt_mesafe!=0)
{
ileri_git(300,300);
alt_mesafe=alt_sensor.ping_cm();
delay(10);
}
dur();
ax12a.moveSpeed(5, 362,300);
delay(5);
ax12a.moveSpeed(5, 362,300);
delay(5);
ax12a.moveSpeed(6, 662,300);
delay(5);
ax12a.moveSpeed(6, 662,300);
delay(5);
ax12a.moveSpeed(7, 662,300);
delay(5);
ax12a.moveSpeed(7, 662,300);
delay(5);
ax12a.moveSpeed(8, 362,300);
delay(5);
ax12a.moveSpeed(8, 362,300);
delay(5);
delay(300);

ileri_git(300,300);
delay(1000);
dur();
delay(200);
ax12a.moveSpeed(5, 512,300);
delay(5);
ax12a.moveSpeed(5, 512,300);
delay(5);
ax12a.moveSpeed(6, 512,300);
delay(5);
ax12a.moveSpeed(6, 512,300);
delay(5);
ax12a.moveSpeed(7, 512,300);
delay(5);
ax12a.moveSpeed(7, 512,300);
delay(5);
ax12a.moveSpeed(8, 512,300);
delay(5);
ax12a.moveSpeed(8, 512,300);
delay(5);
ileri_git(300,300);
delay(300);
dur();
delay(200);
geri_git();
delay(600);
}

void inis_2()
{
  ax12a.moveSpeed(5, 712,300);
  delay(5);
  ax12a.moveSpeed(5, 712,300);
  delay(5);
  ax12a.moveSpeed(6, 312,300);
  delay(5);
  ax12a.moveSpeed(6, 312,300);
  delay(5);
  ax12a.moveSpeed(7, 712,300);
  delay(5);
  ax12a.moveSpeed(7, 712,300);
  delay(5);
  ax12a.moveSpeed(8, 312,300);
  delay(5);
  ax12a.moveSpeed(8, 312,300);
  delay(500);

  ileri_git(300, 300);
  delay(10);
  ileri_git(300, 300);
  delay(10);
  ileri_git(300, 300);
  delay(10);
  delay(5000);
  dur();
}