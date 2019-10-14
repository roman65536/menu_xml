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
  struct menu_item *down;
}u;
};

int func_ls();
int func_edit();
int test;
int test1;
int test2;
int test3;


char text1[] PROGMEM = "Einstellungen";
char text2[] PROGMEM = "Edit without cut&paste";
char text3[] PROGMEM = "Variable ";
char text4[] PROGMEM = "Sim Mode";
char text5[] PROGMEM = "Mode";
char text6[] PROGMEM = "Simulation";
char text_bg[] PROGMEM = "<<BACK";

struct item item_s[] PROGMEM = {
{ "Aufgang", 1},
{ "Untergang",-1}
};



struct item item_s2[] PROGMEM = {
{ "Auto",1 },
{ "Manual",0}
};

struct item item_s3[] PROGMEM = {
{ "Star Sim",0 },
{ "All",1},
{ "Stars O",2},
{ "Sun O",3},
{ "Earth O",4},
};



struct menu_item menu_item1;
struct menu_item menu_item2;
struct menu_item menu_item5;
struct menu_item menu_item6;
struct menu_item menu_item7;
struct menu_item menu_item8;
struct menu_item menu_item9;

struct menu_item menu_item1 PROGMEM = {
  .title=text1,
  .next=&menu_item2,
  .prev=0,
  .up=0,
  .type=5,
  .u.down=&menu_item6,
};

struct menu_item menu_item2 PROGMEM = {
  .title=text2,
  .next=0,
  .prev=&menu_item1,
  .up=0,
  .type=1,
};

struct menu_item menu_item9 PROGMEM = {
  .title=text_bg,
  .next=&menu_item5,
  .prev=0,
  .up=&menu_item1,
  .type=6,
};


struct menu_item menu_item5 PROGMEM = {
  .title=text3,
  .next=&menu_item6,
  .prev=&menu_item9,
  .up=&menu_item1,
  .type=2,
  .u.val=&test,
};


struct menu_item menu_item6 PROGMEM = {
  .title=text4,
  .next=&menu_item7,
  .prev=&menu_item9,
  .up=&menu_item1,
  .type=4,
  .u.val=&test,
  .u.item.cnt=sizeof(item_s)/sizeof(struct item),
  .u.item.items = item_s, 
  .u.item.val=&test1,
};


struct menu_item menu_item7 PROGMEM = {
  .title=text6,
  .next=&menu_item8,
  .prev=&menu_item6,
  .up=&menu_item1,
  .type=4,
  .u.item.cnt=sizeof(item_s2)/sizeof(struct item),
  .u.item.items = item_s2, 
  .u.item.val=&test2,
};


struct menu_item menu_item8 PROGMEM = {
  .title=text5,
  .next=0,
  .prev=&menu_item7,
  .up=&menu_item1,
  .type=4,
  .u.item.cnt=sizeof(item_s3)/sizeof(struct item),
  .u.item.items = item_s3, 
  .u.item.val=&test3,
};


struct menu_item *glb_ptr;


#if 0

struct menu_item menu_items[] PROGMEM = {
  {menu_item[1],menu_item[5],  text1 , 1, .u.func =func_ls },
  {  text2 , 1, .u.func = func_edit },
  {  text3 , 2, .u.val = &test },
  {  text4 , 3, .u.val = &test1 },
  {  text5 , 4, .u.item.cnt=sizeof(item_s)/sizeof(struct item), .u.item.items = item_s, .u.item.val=1 }
};

#endif


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

 glb_ptr=&menu_item1;
 tmp_ptr=glb_ptr;


 do
  {

    int  c;


   move(11,5);
   printw(" >%s< %d %x ",glb_ptr->title,glb_ptr->type,glb_ptr->u.func);
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

   if (glb_ptr->type == 1) {
     if(glb_ptr->u.func !=0 )
       (glb_ptr->u.func)();
   }
   else if (glb_ptr->type == 2)
    printf(" %d** ",*glb_ptr->u.val);
   else if(glb_ptr->type == 5)
	   menu_down();
   else if(glb_ptr->type ==6)
     menu_up();
   else if (glb_ptr->type == 4)
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
	   if (ptr1->val ==*glb_ptr->u.item.val)
	     printw("(x)[%s] ",ptr1->title);
	   else printw("( )[%s] ",ptr1->title);
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
       *glb_ptr->u.item.val=ptr1->val;
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

