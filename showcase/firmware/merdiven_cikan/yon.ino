void hareket(int sol_teker, int sag_teker)
{
  sag_teker = constrain(sag_teker, -1000, 1000);
  sol_teker = constrain(sol_teker, -1000, 1000);

  if(sag_teker > 0)
  {
    ax12a.turn(2, RIGHT, sag_teker);
    ax12a.turn(4, RIGHT, sag_teker);
  }
  else if(sag_teker < 0)
  {
    ax12a.turn(2, LEFT, -sag_teker);
    ax12a.turn(4, LEFT, -sag_teker);
  }
  else
  {
    ax12a.turn(2, RIGHT, 0);
    ax12a.turn(4, RIGHT, 0);
  }

  if(sol_teker > 0)
  {
    ax12a.turn(1, LEFT, sol_teker);
    ax12a.turn(3, LEFT, sol_teker);
  }
  else if(sol_teker < 0)
  {
    ax12a.turn(1, RIGHT, -sol_teker);
    ax12a.turn(3, RIGHT, -sol_teker);
  }
  else
  {
    ax12a.turn(1, RIGHT, 0);
    ax12a.turn(3, RIGHT, 0);
  }
}

void ileri_git(int a, int b)
{
ax12a.turn(1, LEFT, a);
ax12a.turn(2, RIGHT, b);
ax12a.turn(3, LEFT, a);
ax12a.turn(4, RIGHT, b);

}
void geri_git()
{
ax12a.turn(1, RIGHT, 500);
ax12a.turn(2, LEFT, 500);
ax12a.turn(3, RIGHT, 500);
ax12a.turn(4, LEFT, 500);
}
void geri_git(int speed)
{
ax12a.turn(1, RIGHT, speed);
ax12a.turn(2, LEFT, speed);
ax12a.turn(3, RIGHT, speed);
ax12a.turn(4, LEFT, speed);
}
void saga_don()
{
ax12a.turn(1, LEFT, 800);
ax12a.turn(2, LEFT, 800);
ax12a.turn(3, RIGHT, 800);
ax12a.turn(4, RIGHT, 800);
}
void sola_don()
{ 
ax12a.turn(1, RIGHT, 800);
ax12a.turn(2, RIGHT, 800);
ax12a.turn(3, LEFT, 800);
ax12a.turn(4, LEFT, 800);
}
 void  dur()
 {
ax12a.turn(1, LEFT, 0);
ax12a.turn(2, RIGHT, 0);
ax12a.turn(3, LEFT, 0);
ax12a.turn(4, RIGHT, 0);
 }