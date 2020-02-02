#include "World.h"

World w;
int main(int argc,char *argv[]){
	if(argc!=1)
		freopen(argv[1],"r",stdin);
	w.Run();
	return 0;
}
