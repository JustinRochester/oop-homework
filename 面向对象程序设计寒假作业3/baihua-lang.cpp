#include "World.h"

World world;
int main(int argc,char *argv[]){
	if(argc!=1)
		freopen(argv[1],"r",stdin);
	world.Run();
	return 0;
}
