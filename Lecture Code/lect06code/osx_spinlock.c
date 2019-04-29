#include <libkern/OSAtomic.h>

#define RELEASED 10000000

int main(void)
{
	int count = 0;
	
	OSSpinLock spin_lock = OS_SPINLOCK_INIT;

	if (!OSSpinLockTry(&spin_lock))
		OSSpinLockLock(&spin_lock);

	while (count++ < RELEASED)
    	OSSpinLockTry(&spin_lock);

	OSSpinLockUnlock(&spin_lock);
}