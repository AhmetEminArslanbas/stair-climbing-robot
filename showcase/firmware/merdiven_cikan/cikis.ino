void cikis()
{
on_mesafe=on_sensor.ping_cm();
delay(10);
ileri_git(300,300);
while(on_mesafe>5 and on_mesafe!=0)
{
ileri_git(300,300);
on_mesafe=on_sensor.ping_cm();
delay(10);
}
delay(1000);
ax12a.moveSpeed(5, 850,300);
delay(5);
ax12a.moveSpeed(5, 850,300);
delay(5);
ax12a.moveSpeed(6, 170,300);
delay(5);
ax12a.moveSpeed(6, 170,300);
delay(5);
ax12a.moveSpeed(7, 412,300);
delay(5);
ax12a.moveSpeed(7, 412,300);
delay(5);
ax12a.moveSpeed(8, 612,300);
delay(10);
ax12a.moveSpeed(8, 612,300);
delay(1190);
ax12a.moveSpeed(5, 620,300);
delay(5);
ax12a.moveSpeed(5, 620,300);
delay(5);
ax12a.moveSpeed(6, 400,300);
delay(5);
ax12a.moveSpeed(6, 400,300);
delay(5);
ax12a.moveSpeed(7, 200,300);
delay(5);
ax12a.moveSpeed(7, 200,300);
delay(5);
ax12a.moveSpeed(8, 820,300);
delay(10);
ax12a.moveSpeed(8, 820,300);
delay(990);

dur();
ax12a.moveSpeed(7, 512,500);
delay(5);
ax12a.moveSpeed(7, 512,500);
delay(5);
ax12a.moveSpeed(8, 512,500);
delay(5);
ax12a.moveSpeed(8, 512,500);
delay(5);
ax12a.moveSpeed(5, 512,500);
delay(5);
ax12a.moveSpeed(5, 512,500);
delay(5);
ax12a.moveSpeed(6, 512,500);
delay(5);
ax12a.moveSpeed(6, 512,500);

}