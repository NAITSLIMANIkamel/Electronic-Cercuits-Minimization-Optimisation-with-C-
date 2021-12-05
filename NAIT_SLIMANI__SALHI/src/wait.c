#include <stdlib.h>
#include <unistd.h>

int main()
{

  int i=0;

  write(1,"\033[32m Plaise Wait ... ╠",29);

  while(1)
    {
      write(1,"═",3);
      sleep(2);
      i++;
      if(i==10)
	write(1," Oui ça va prendre du temps :-) ",33);
    }

  return EXIT_SUCCESS;
}
