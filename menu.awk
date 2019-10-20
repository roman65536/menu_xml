#@load xml
#back_arg if set to 1, generator creates a "Back" within sub menues
#

BEGIN { idx=1; put_stack(1); menu[1]="MAIN"; level=0; }


function put_stack(idx)
{
    menu_stack[++stck_idx]=idx;
}

function pop_stack()
{
    menu_stack[stck_idx]=0;
    stck_idx--;
    return  menu_stack[stck_idx];
}


function get_parent()
{
    return menu_stack[stck_idx-1];
}


function get_idx()
{
    max_idx=++idx;
return max_idx;
}


XMLCHARDATA 	{
		data=$0;
		}

XMLSTARTELEM {
	depth++;
#	print XMLPATH;
	data="";
	}


XMLENDELEM  && XMLPATH ~ /menu$/ {
       
    if(menu_type[cur_idx] ~ /(radio|check)/)
	{
	    if(menu_items[cur_idx] == 0)
		printf("//WARNING %s is defined as %s, but has no items\n",menu[cur_idx],menu_type[cur_idx]);
	    if(menu_variable[cur_idx] == "" )
	    printf("//WARNING: %s is defined as %s, but no variable is defined\n",menu[cur_idx],menu_type[cur_idx]);
	}
  cur_idx=pop_stack();
	depth--;

}


XMLSTARTELEM && XMLPATH ~ /menu$/ {
    tmp=cur_idx;
 #    printf("cur %d ",tmp);
cur_idx=get_idx();
#    printf("cur %d ",tmp);
#menu_next[tmp]=cur_idx;
put_stack(cur_idx);
par=get_parent();
menu_type[cur_idx]=XMLATTR["type"]
menu_variable[cur_idx]=XMLATTR["variable"];
menu_min[cur_idx]=XMLATTR["min"];
menu_max[cur_idx]=XMLATTR["max"];
menu_func[cur_idx]=XMLATTR["function"];
menu_args[cur_idx]=XMLATTR["args"];
menu_subs[par]= menu_subs[par] "  " cur_idx;
#printf("some Menu starts %d %d\n",cur_idx,depth);
item_cnt++; item_idx=0;
}

XMLENDELEM && XMLPATH ~ /title/ {
#printf("title %s\n",data);
menu[cur_idx]=data;

}


XMLSTARTELEM && XMLPATH ~ /item$/ {
    item_idx++;
    val=XMLATTR["val"];
}

XMLENDELEM && XMLPATH ~ /item$/ {
    menu_items[cur_idx]=item_idx;
    items[cur_idx,item_idx]=data;
    items_val[cur_idx,item_idx]=val;
}


END{
 #   for (a=1;a<=max_idx;a++)
 #   printf("%s \"%s\" n:%s sub:[%s]\n",a,menu[a],menu_next[a], menu_subs[a]);



    print_subs1(1);
 printf("\n\n\n/* Menu configuration as defined \n");
 print_subs2(1);
 printf(" Menu configuration as defined */\n\n\n");
 #printf("\n************************\n");
 print_items_c(1);
 print_menus_c(1);

}





function print_subs1(x, z , a_t,cnt,idx,b)
{

    level++;
#    for(a_t=0;a_t<=level;a_t++) 
#	printf("%*c",level," ");

    cnt=split(menu_subs[x],z);
#    printf("1: %d %d\n",cnt,x);
    for(a_t=1;a_t<=cnt;a_t++)
    {
	menu_next[z[a_t]]=0;
	if(a_t == 1)  {
#	    printf("2: x: %d \n",x);
	    if((x != 1) && (back_arg == 1)) {
	    #insert the back point 
	    b=get_idx();
	    menu[b]="<<BACK";
	    menu_prev[b]=0;
	    menu_next[b]=z[a_t];
	    menu_up[b]=x;
	    menu_prev[ z[a_t] ] =b;
	    menu_type[b]="back";
	    } else menu_prev[z[a_t]]=0;
	}
	else
	{
	    menu_prev[ z[a_t] ] =  z[a_t -1] 
	    menu_next[ z[a_t -1] ] =   z[a_t];
	}
	if(x!=1)
        menu_up[z[a_t]]=x;
	else menu_up[z[a_t]]=0;
#	printf("%*c %[%s] %d %s %d %d \n",level," ",level,menu[ z[a_t]],x,z[a_t],menu_next[z[a_t]],menu_prev[z[a_t]]);
	if(menu_items[z[a_t]] > 0) {
#	    printf("%*c %s\n",level+1," ",menu_variable[z[a_t]]);
	    idx=menu_items[z[a_t]];
#	    for(b=1;b<=idx;b++) printf("%*c [%s<=%s]\n",level+1," ",items[z[a_t],b],items_val[z[a_t],b]);
	}
	if (menu_subs[ z[a_t]] != "" ) print_subs1(z[a_t]);
    }
    level--;
}

function print_subs2(x, z , a_t,cnt)
{

    level++;
#    for(a_t=0;a_t<=level;a_t++) 
#	printf("%*c",level," ");

    cnt=split(menu_subs[x],z);
  
    for(a_t=1;a_t<=cnt;a_t++)
    {

	printf("//%*c[%s] type [%s]\n",level," ",menu[ z[a_t]],menu_type[z[a_t]]);
	if (menu_subs[ z[a_t]] != "" ) print_subs2(z[a_t]);
    }
    level--;


}


function print_items_c(x, z , a_t,cnt,idx,b)
{

    level++;
#    for(a_t=0;a_t<=level;a_t++) 
#	printf("%*c",level," ");

    cnt=split(menu_subs[x],z);
#    printf("1: %d %d\n",cnt,x);
    for(a_t=1;a_t<=cnt;a_t++)
    {


#	printf("%*c %d [%s] %d %s %d %d \n",level," ",level,menu[ z[a_t]],x,z[a_t],menu_next[z[a_t]],menu_prev[z[a_t]]);
	if(menu_items[z[a_t]] > 0) {
#	    printf("%*c %s\n",level+1," ",menu_variable[z[a_t]]);
	    idx=menu_items[z[a_t]];
	    for(b=1;b<=idx;b++) printf("char item_txt_%d_%d[] PROGMEM =\"%s\";\n",z[a_t],b, items[z[a_t],b]);
	    printf("struct item item_s_%d[] PROGMEM = { \n",z[a_t]);
	    for(b=1;b<=idx;b++) printf("{ item_txt_%d_%d,%s},\n",z[a_t],b,items_val[z[a_t],b]);
	     printf("};\n");
	} 
	if (menu_subs[ z[a_t]] != "" ) print_items_c(z[a_t]);
    }
    level--;
}

function print_menus_c(x, z , a_t,cnt,idx,b)
{

    level++;
#    for(a_t=0;a_t<=level;a_t++) 
#	printf("%*c",level," ");

    cnt=split(menu_subs[x],z);
#    printf("1: %d %d\n",cnt,x);


 for(a_t=2;a_t<=max_idx;a_t++)
 {
     printf("char menu_text_%s[] PROGMEM=\"%s\"; /*forward declaration **%s** */ \n",a_t,menu[a_t],menu[a_t]);
 }

 for(a_t=2;a_t<=max_idx;a_t++)
 {
     printf("struct menu_item menu_item_%s; /*forward declaration **%s** */ \n",a_t,menu[a_t]);
 }


    for(a_t=2;a_t<=max_idx;a_t++)
    {

        printf("\n\n\n/* Menu definition for %s */\n",menu[a_t]);
	printf("struct menu_item menu_item_%s PROGMEM = {\n",a_t);
	printf(" .title=menu_text_%s,\n",a_t);
	if(menu_next[a_t] != 0)
	printf(" .next=&menu_item_%s,\n",menu_next[a_t]);
	else 
	   printf(" .next=0,\n");
	if(menu_prev[a_t] != 0)
	printf(" .prev=&menu_item_%s,\n",menu_prev[a_t]);
	else 
	   printf(" .prev=0,\n");

	if((menu_up[a_t] != 0) && (a_t != 2))
	printf(" .up=&menu_item_%s,\n",menu_up[a_t]);
	else 
	   printf(" .up=0,\n"); 

	if(menu_type[a_t] ~ /sub/) {
	    split(menu_subs[a_t],z);
	    printf(" .type=SUB_MENU,\n .u.down=&menu_item_%s,\n",z[1]);
	} 
	if(menu_type[a_t] ~ /exit/) {
		printf(" .type=EXIT_MENU,\n");
	    }
	if(menu_type[a_t] ~ /radio/ ) {
		printf(" .type=RADIO_MENU,\n");
		printf(" .u.item.cnt=%d,\n",menu_items[a_t]);
		printf(" .u.item.items= item_s_%d,\n",a_t);
		printf(" .u.item.val=&%s,\n", menu_variable[a_t]);
	}
	if(menu_type[a_t] ~ /check/ ) {
		printf(" .type=CHECK_MENU,\n");
		printf(" .u.item.cnt=%d,\n",menu_items[a_t]);
		printf(" .u.item.items= item_s_%d,\n",a_t);
		printf(" .u.item.val=&%s,\n", menu_variable[a_t]);
	}
	if(menu_type[a_t] ~ /variable/ ) {
	    	printf(" .type=VAR_MENU,\n");
		printf(" u.val=&%s,\n", menu_variable[a_t]);
	}
	if(menu_type[a_t] ~ /back/ ) {
	    	printf(" .type=BACK_MENU,\n");
	
	}
	if(menu_type[a_t] ~ /change/ ) {
	    	printf(" .type=SETV_MENU,\n");
		printf(" .u.cval.val=&%s,\n", menu_variable[a_t]);
		printf(" .u.cval.min=%s,\n", menu_min[a_t]);
		printf(" .u.cval.max=%s,\n", menu_max[a_t]);
	}
	if(menu_type[a_t] ~ /function/ ) {
	        printf(" .type=FUNC_MENU,\n");
	        printf(" .u.func=%s,\n",menu_func[a_t]);
		if(menu_args[a_t])
		printf(" .u.val=%s,\n",menu_args[a_t]);
	}
	printf("};\n");
    }
    level--;
}
