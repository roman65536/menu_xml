#if AVR
#include <avr/pgmspace.h>
#endif
#ifdef NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif

#include <stdio.h>

#ifndef PROGMEM 
#define PROGMEM 
#endif





#define BACK_MENU 1
#define EXIT_MENU 2
#define RADIO_MENU 3
#define SUB_MENU 4
#define CHECK_MENU 5
#define FUNC_MENU  6
#define VAR_MENU   7
#define SETV_MENU  8




struct item {
char *title;
int val;
};

struct menu_item {
char *title ;
  struct menu_item *next;     /*next item */
  struct menu_item *prev;     /*prev item */
  struct menu_item *up; 
  
int type;
union {
int (*func) ();
int *val; 
struct {
  int cnt;
 int *val;
 struct item *items;
}item;
  struct {
    int min,max;
    int *val;
  }cval;
  struct menu_item *down;
}u;
};

int func_ls();
int func_edit();
int test;
int test1;
int test2;
int test3;
int mode;
int ab_auf;
int auto_v;



#include "menu.h"


struct menu_item *glb_ptr; 

int func_ls()
{
printf("ls");
}

int func_edit()
{
printf("edit");
}

#define LAST 2
#define OK 1

menu_next()
{
  if(glb_ptr->next !=0) glb_ptr=glb_ptr->next;
  else return LAST;
  return OK;
}

menu_prev()
{
  if(glb_ptr->prev !=0) glb_ptr=glb_ptr->prev;
  else return LAST;
  return OK;
}

menu_up()
{
  if(glb_ptr->up !=0) glb_ptr=glb_ptr->up;
  else return LAST;
  return OK;
}

menu_down()
{
  if(glb_ptr->u.down !=0) glb_ptr=glb_ptr->u.down;
  else return LAST;
  return OK;
}


main()
{


int a,b;
test=123;
 struct menu_item *tmp_ptr;

 init();

 glb_ptr=&menu_item_2;
 tmp_ptr=glb_ptr;


 do
  {

    int  c;


   move(11,5);
   printw(" >%-20s< ",glb_ptr->title);
   refresh();


   c=getch();
   switch(c)
     {
     case 'j' :
       menu_next();
       break;
     case 'k' :
       menu_prev();
       break;
    


     case KEY_ENTER:
      case  '\n':
       {

   if (glb_ptr->type == FUNC_MENU ) {
     if(glb_ptr->u.func !=0 )
       (glb_ptr->u.func)();
   }
   else if (glb_ptr->type == VAR_MENU )
    printf(" %d** ",*glb_ptr->u.val);
   else if(glb_ptr->type == SUB_MENU )
	   menu_down();
   else if(glb_ptr->type == BACK_MENU )
     menu_up();
   else if ((glb_ptr->type == RADIO_MENU) || (glb_ptr->type == CHECK_MENU ))
     {
       int z=0;
       struct item *ptr1;
       int item_cnt=glb_ptr->u.item.cnt;
       //      printf("set is %d", ptr->u.item.val);     

       for(;z!=-2;)
	 {
	
         move(11,5);
	 if(z >= 0) {
	   ptr1=&glb_ptr->u.item.items[z];
	   if(glb_ptr->type == RADIO_MENU){
	   if (ptr1->val ==*glb_ptr->u.item.val)
	     printw("(x)[%s] ",ptr1->title);
	   else printw("( )[%s] ",ptr1->title);
	   }
	   if(glb_ptr->type == CHECK_MENU) {
	     if (ptr1->val & *glb_ptr->u.item.val)
	     printw("(*)[%s] ",ptr1->title);
	   else printw("( )[%s] ",ptr1->title);
	   }
	 } else
	     printw("   <<BACK ");
	   refresh();
   
      c=getch();
   switch(c)
     {
     case 'j' :
       if(z < item_cnt-1) z++;
       break;
     case 'k' :
       if( z >= 0)  z--;
       break;
     case   KEY_ENTER:
     case  '\n':
       if(z >= 0) 
	 {
	   if(glb_ptr->type == RADIO_MENU)
       *glb_ptr->u.item.val=ptr1->val;

	   if(glb_ptr->type == CHECK_MENU)
       *glb_ptr->u.item.val^= ptr1->val;

	 }
       if (z == -1) z=-2;
       break;
     }
	 }
     }
   break;
   }
    
     }
 

  }while(1);



}




init()
{

 initscr();
 keypad(stdscr,TRUE);
 erase();
 refresh();
 }

