#ifndef OS_PRIVATE_H
#define OS_PRIVATE_H


/* TASK STATES */
/*typedef enum
{DORMANT , READY, SUSPEND, DELETE}STATE;*/

#define DORMANT                  0
#define READY                    1
#define SUSPEND                  2
#define DELETE                   4

typedef struct
{
	u16 periodicity ;
	void(*f_ptr)(void);
	u16 firstDelay;
	u8 State ;
}Task;



#endif
