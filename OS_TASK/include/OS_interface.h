#ifndef OS_INTERFACE_H
#define OS_INTERFACE_H


void OS_voidCreateTask(u8 copy_u8Proirity,u16 copy_periodicity,void(*copy_ptr)(void), u8 copy_firstDelay);
void OS_voidStart(void);
void OS_voidScheduler(void);
/* stop executing a task for a time */
void OS_voidSuspend(u8 copy_u8TaskId);
/* proceed executing a task after suspending */
void OS_voidResume (u8 copy_u8TaskId);
/* disable the task */
void OS_voidDelete (u8 copy_u8TaskId);



#endif
