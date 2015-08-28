#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

long int *MAGIC = new long int[2];

struct datos{
  long int magic1;
  long int magic2;
  long int na;
  long int nb;
};

struct rega{
  long int a1,a2,a3;
};

struct regb{
  long int b1,b2;
};

int main(int argc, char *argv[]) {

  MAGIC[0]=724809124570792400;
  MAGIC[1]=289644378304612860;

  if(argc < 7){
    cout << "argument missing";
    return 1;
  }

  if(!isdigit(*argv[1])){
    cout << "the first argument must be a number" << endl;
    return 1;
  }

  if(!isdigit(*argv[4])){
    cout << "the fourth argument must be a number" << endl;
    return 1;
  }

  int fd = open(argv[6], O_RDWR);
  datos datos;
  long int * indexa = new long int [datos.na];
  long int * indexb = new long int [datos.nb];

  lseek(fd, 32, SEEK_SET);
  read(fd, indexa, 8 * datos.na);

  lseek(fd, 32 + (8 * datos.na), SEEK_SET);
  read(fd, indexb, 8 * datos.nb);

  int times = atoi(argv[4]);
  int value = atoi(argv[5]);

  if(strcmp(argv[2],"a")==0){
    long int pos = indexa[atoi(argv[1])];
    for(int i = 0; i < times; i++){
      //se bloquea
      rega ra;
      flock infolock;
      infolock.l_type = F_WRLCK;
      infolock.l_whence = SEEK_SET;
      infolock.l_start = pos;
      infolock.l_len = sizeof(ra);
      fcntl(fd, F_SETLKW, &infolock);
      //almacenar en la estructura
      lseek(fd, pos, SEEK_SET);
      read(fd, &ra, sizeof(ra));
      //se verifica cual entrada del registro se
      //debe modificar
      if(strcmp(argv[3],"a1")==0){
	ra.a1 += value;
	lseek(fd, pos, SEEK_SET);
	write(fd, &ra, sizeof(ra));
      }else if(strcmp(argv[3],"a2")==0){
	ra.a2 += value;
	lseek(fd, pos, SEEK_SET);
	write(fd, &ra, sizeof(ra));
      }else if(strcmp(argv[3],"a3")==0){
	ra.a3 += value;
	lseek(fd, pos, SEEK_SET);
	write(fd, &ra, sizeof(ra));
      }else{
	cout<<"error with argument 3: "<<argv[3]<<endl;
	return 1;
      }
      //se desbloquea
      infolock.l_type = F_UNLCK;
      infolock.l_whence = SEEK_SET;
      infolock.l_start = pos;
      infolock.l_len = sizeof(ra);
      fcntl(fd, F_SETLKW, &infolock);
    }
  }else{
    long int pos = indexb[atoi(argv[1])];
    for(int i = 0; i < times; i++){
      //se bloquea
      regb rb;
      flock infolock;
      infolock.l_type = F_WRLCK;
      infolock.l_whence = SEEK_SET;
      infolock.l_start = pos;
      infolock.l_len = sizeof(rb);
      fcntl(fd, F_SETLKW, &infolock);
      //almacenar en la estructura
      lseek(fd, pos, SEEK_SET);
      read(fd, &rb, sizeof(rb));
      if(strcmp(argv[3],"b1")==0){
	rb.b1 += value;
	lseek(fd, pos, SEEK_SET);
	write(fd, &rb, sizeof(rb));
      }else if(strcmp(argv[3],"b2")==0){
	rb.b2 += value;
	lseek(fd, pos, SEEK_SET);
	write(fd, &rb, sizeof(rb));
      }else{
	cout<<"error with argument 3: "<<argv[3]<<endl;
	return 1;
      }
      //se desbloquea
      infolock.l_type = F_UNLCK;
      infolock.l_whence = SEEK_SET;
      infolock.l_start = pos;
      infolock.l_len = sizeof(rb);
      fcntl(fd, F_SETLKW, &infolock);
    }
  }
  close(fd);
  return 0;
}
