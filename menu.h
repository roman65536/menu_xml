


/* Menu configuration as defined 
// [Mode] type [radio]
// [Simulation] type [sub]
//  [Auf-/Abgang] type [radio]
//  [Auto Mode] type [radio]
//  [Auto Mode] type [change]
// [CHECK] type [check]
//  [Exit] type [exit]
 Menu configuration as defined */


char item_txt_2_1[] PROGMEM ="Stern Sim.";
char item_txt_2_2[] PROGMEM ="Alle";
char item_txt_2_3[] PROGMEM ="Nacht";
char item_txt_2_4[] PROGMEM ="Tag";
struct item item_s_2[] PROGMEM = { 
{ item_txt_2_1,1},
{ item_txt_2_2,2},
{ item_txt_2_3,3},
{ item_txt_2_4,4},
};
char item_txt_4_1[] PROGMEM ="Ab";
char item_txt_4_2[] PROGMEM ="Auf";
struct item item_s_4[] PROGMEM = { 
{ item_txt_4_1,-1},
{ item_txt_4_2,1},
};
char item_txt_5_1[] PROGMEM ="Auto";
char item_txt_5_2[] PROGMEM ="Manual";
struct item item_s_5[] PROGMEM = { 
{ item_txt_5_1,1},
{ item_txt_5_2,0},
};
char item_txt_7_1[] PROGMEM ="Auto Update";
char item_txt_7_2[] PROGMEM ="FFT";
char item_txt_7_3[] PROGMEM ="SCOPE";
struct item item_s_7[] PROGMEM = { 
{ item_txt_7_1,1},
{ item_txt_7_2,2},
{ item_txt_7_3,4},
};
char menu_text_2[] PROGMEM="Mode"; /*forward declaration **Mode** */ 
char menu_text_3[] PROGMEM="Simulation"; /*forward declaration **Simulation** */ 
char menu_text_4[] PROGMEM="Auf-/Abgang"; /*forward declaration **Auf-/Abgang** */ 
char menu_text_5[] PROGMEM="Auto Mode"; /*forward declaration **Auto Mode** */ 
char menu_text_6[] PROGMEM="Auto Mode"; /*forward declaration **Auto Mode** */ 
char menu_text_7[] PROGMEM="CHECK"; /*forward declaration **CHECK** */ 
char menu_text_8[] PROGMEM="Exit"; /*forward declaration **Exit** */ 
char menu_text_9[] PROGMEM="<<BACK"; /*forward declaration **<<BACK** */ 
char menu_text_10[] PROGMEM="<<BACK"; /*forward declaration **<<BACK** */ 
struct menu_item menu_item_2; /*forward declaration **Mode** */ 
struct menu_item menu_item_3; /*forward declaration **Simulation** */ 
struct menu_item menu_item_4; /*forward declaration **Auf-/Abgang** */ 
struct menu_item menu_item_5; /*forward declaration **Auto Mode** */ 
struct menu_item menu_item_6; /*forward declaration **Auto Mode** */ 
struct menu_item menu_item_7; /*forward declaration **CHECK** */ 
struct menu_item menu_item_8; /*forward declaration **Exit** */ 
struct menu_item menu_item_9; /*forward declaration **<<BACK** */ 
struct menu_item menu_item_10; /*forward declaration **<<BACK** */ 



/* Menu definition for Mode */
struct menu_item menu_item_2 PROGMEM = {
 .title=menu_text_2,
 .next=&menu_item_3,
 .prev=0,
 .up=0,
 .type=RADIO_MENU,
 .u.item.cnt=4,
 .u.item.items= item_s_2,
 .u.item.val=&mode,
};



/* Menu definition for Simulation */
struct menu_item menu_item_3 PROGMEM = {
 .title=menu_text_3,
 .next=&menu_item_7,
 .prev=&menu_item_2,
 .up=0,
 .type=SUB_MENU,
 .u.down=&menu_item_4,
};



/* Menu definition for Auf-/Abgang */
struct menu_item menu_item_4 PROGMEM = {
 .title=menu_text_4,
 .next=&menu_item_5,
 .prev=&menu_item_9,
 .up=&menu_item_3,
 .type=RADIO_MENU,
 .u.item.cnt=2,
 .u.item.items= item_s_4,
 .u.item.val=&ab_auf,
};



/* Menu definition for Auto Mode */
struct menu_item menu_item_5 PROGMEM = {
 .title=menu_text_5,
 .next=&menu_item_6,
 .prev=&menu_item_4,
 .up=&menu_item_3,
 .type=RADIO_MENU,
 .u.item.cnt=2,
 .u.item.items= item_s_5,
 .u.item.val=&auto_v,
};



/* Menu definition for Auto Mode */
struct menu_item menu_item_6 PROGMEM = {
 .title=menu_text_6,
 .next=0,
 .prev=&menu_item_5,
 .up=&menu_item_3,
 .type=SETV_MENU,
 .u.cval.val=&auto_v,
 .u.cval.min=0,
 .u.cval.max=100,
};



/* Menu definition for CHECK */
struct menu_item menu_item_7 PROGMEM = {
 .title=menu_text_7,
 .next=0,
 .prev=&menu_item_3,
 .up=0,
 .type=CHECK_MENU,
 .u.item.cnt=3,
 .u.item.items= item_s_7,
 .u.item.val=&auto_v,
};



/* Menu definition for Exit */
struct menu_item menu_item_8 PROGMEM = {
 .title=menu_text_8,
 .next=0,
 .prev=&menu_item_10,
 .up=&menu_item_7,
 .type=EXIT_MENU,
};



/* Menu definition for <<BACK */
struct menu_item menu_item_9 PROGMEM = {
 .title=menu_text_9,
 .next=&menu_item_4,
 .prev=0,
 .up=&menu_item_3,
 .type=BACK_MENU,
};



/* Menu definition for <<BACK */
struct menu_item menu_item_10 PROGMEM = {
 .title=menu_text_10,
 .next=&menu_item_8,
 .prev=0,
 .up=&menu_item_7,
 .type=BACK_MENU,
};
