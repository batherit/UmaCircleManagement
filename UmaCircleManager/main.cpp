#include"CUmaCircleManagementSystem.h"

#define RUN(System) \
System.Init();\
System.StartServer();\
while(System.Run()) {};\
System.EndServer();\

int main(void)
{
	CUmaCircleManagementSystem umaCircleManagementSystem;
	
	RUN(umaCircleManagementSystem)

	return 0;
}
