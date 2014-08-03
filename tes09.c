#include <stdio.h>

int main(int argc, char **argv)
{
	__set_current_state(TASK_INTERRUPTIBLE);

	schedule();
	return 0;
}
