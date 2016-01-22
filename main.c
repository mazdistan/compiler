#include <stdio.h>
#include <stdlib.h>
struct tl1{
struct tl1 *next;
struct tl1 *pre;
char data[30];
char atri[10];
int line;
int b;
int c;

};
typedef struct tl1 tl1;
typedef struct tl1* tl1ptr;
int iskey(char a[] , tl1ptr cur ,tl1ptr start)

{
    if(strcmpi(a ,"int")==0 || strcmpi(a ,"float")==0 ||strcmpi(a ,"bool")==0 ||strcmpi(a ,"char")==0 ||strcmpi(a ,"if")==0 || strcmpi(a ,"while")==0 || strcmpi(a, "else")==0 )
        {

            cur =cur->pre;
            if(cur == start)
                return 0;

            if(strcmpi(cur->data , ";") ==0)
                {

                    return 0;
                    cur = cur->next;

                }



        }



    if(!(strcmpi(a ,"int")==0 || strcmpi(a ,"float")==0 ||strcmpi(a ,"bool")==0 ||strcmpi(a ,"char")==0 ||strcmpi(a ,"if")==0 || strcmpi(a ,"while")==0 || strcmpi(a, "else")==0) )
           {

               if((a[0]>='a' && a[0]<='z') || (a[0]>='A' && a[0]<='Z')){

            cur=cur->pre;

        if((strcmpi(cur->data , ";")==0) || (strcmpi(cur->data , "int")==0) ||(strcmpi(cur->data , "float")==0) ||(strcmpi(cur->data , "char")==0) || (strcmpi(cur->data , "bool")==0)  )

            return 0;

            }
           }
        else
            return 1;

}
void atribute(tl1ptr start)
{

    tl1ptr current;
    tl1ptr temp;
    char a[15];
    int i=1;
    current=start->next;
    while(current !=0)
    {
        strcpy(a,current->data);

        temp=current;

        strcpy(a , current->data);
        if(strcmpi(current->data ,"+")==0 || strcmpi(current->data ,"-")==0 ||strcmpi(current->data ,"=")==0 || strcmpi(current->data ,"*")==0 || strcmpi(current->data ,"/")==0 || strcmpi(current->data ,"%")==0)
        {strcpy(current->atri ,"op");
        }
      else if((a[0]>='0' && a[0]<='9') || a[0]=='-')
        {

            while(a[i]!=0)
            {
                if(!((a[i]>='0' && a[i]<='9') || a[i]=='.'))
                {
                    current->b=1;
                    strcpy(current->atri , "");
                    if(current->next!=0)
                        current=current->next;
                    while(current!=0 && strcmpi(current->data ,";")!=0)
                    {
                        current->b=1;
                        current=current->next;
                    }
                    break;
                }
                i++;
            }
            if(a[i]==0 ||a[i]=='\n')
                {
                    strcpy(temp->atri , "num");
                        temp->b=0;
                }
        }
        else if((a[0]>='a' && a[0]<='z') || (a[0] >='A' && a[0]<='Z'))
        {
            if(strcmpi(current->data , "return")==0 || strcmpi(current->data , "main")==0 || strcmpi(current->data , "while")==0 || strcmpi(current->data , "else")==0 || strcmpi(current->data , "if")==0 || strcmpi(current->data , "bool")==0 || strcmpi(current->data , "char")==0 || strcmpi(current->data , "float")==0 || strcmpi(current->data , "int")==0)
            {strcpy(current->atri ,"keyword");
            }
            else
            {while(a[i] !=0)
            {
            if(!((a[0]>='a' && a[0]<='z') || (a[0] >='A' && a[0]<='Z') || (a[i]>='0' && a[i]<='9')))
                {current->b=1;
                if(current->next!=0)
                    current=current->next;
                while(current!=0 && strcmpi(current->data ,";")!=0)
                {
                    current->b=1;
                    current=current->next;
                }


                }
                break;}
                if(a[i]==0 || a[i]=='\n')
                    {strcpy(current->atri ,"id");
                    }
                    }
        }


        else if(a[0]=='#' || a[0]==';' || a[0]==')' || a[0]=='(' || a[0]=='{' || a[0]=='}')
            {

                if(a[1]==0 || a[1]=='\n')
                    strcpy(current->atri , "punc");
                    else
                     strcpy(current->atri,"unknown ");
            }
            else
            {
                strcpy(current->atri , "unknown");
                current->b=1;
            }

       current=temp;
       current=current->next;

    }

}
void add(tl1ptr start , char a[] ,int line )
{
    tl1ptr current;
    tl1ptr new;
    tl1ptr t;
    int z=0;
    new=malloc(sizeof(tl1));
    new->next=0;
    new->c=0;
    new->b=0;
    current=start;
    strcpy(new->data , a);
    new->line= line;
    while(current -> next != 0)
    {
        current = current -> next;
    }
    current-> next = new;
    new->pre = current;
    /*z=iskey(new->data , new ,start);
    if(z==1)
    {

        t=malloc(sizeof(tl1));
        strcpy(t->data , ";");

        current->next = t;
        new->pre = t;
        t->next =new;
        t->pre = current;
    }*/
}
void tokenise(tl1ptr start)
{

FILE *p;
FILE *s;
char m[200];
char *ptr;
int line=1;
p=fopen("data.txt" ,"r");
fgets(m,200,p);

s=strtok(m," ");

while(s!=0)
{

    add(start ,s, line);
    s=strtok(NULL ," ");

}

line++;

while(!feof(p))
{
    fgets(m,200,p);

s=strtok(m," ");

while(s!=0)
{

    add(start ,s, line);
    s=strtok(NULL ," ");

}
line++;
}



}
void print(tl1ptr start)
{
    tl1ptr current;
    current = start ->next;
    while(current != 0)
    {
        printf("%s%s%d\n" , current->data,current->atri ,current->b);
        current = current -> next;
    }
}
struct st{
char name[10];
char value[20];
char type[10];
int index;
struct st *pre;
struct st *next;
int b;

};
typedef struct st st;
typedef struct st* stptr;
void makesymboltable(tl1ptr start , stptr start2)
{
    int i=0;
    tl1ptr cur ;
    stptr cur2 ;
    stptr new;
    cur=start->next;
    cur2=start2;

    while(cur != 0 )
    {
        if((strcmpi(cur->data , "int")==0 || strcmpi(cur->data, "float")==0 || strcmpi(cur->data , "char")==0 || strcmpi(cur->data,"bool")==0))
        {
            i++;
            new=malloc(sizeof(st));
            strcpy(new->type , cur->data);
            new->b=0;
            cur2->next=new;
            new->pre=cur2;
            if(cur->next!=0)
            {
                cur = cur->next;
                strcpy(new->name ,cur->data );
            }
            cur2=new;
        }
        cur=cur->next;
    }
    if(i!=0)
        new->next=0;
}

void sede(stptr start)
{
    stptr temp;
    stptr current;
    current=start->next;

    if(current!=0 && current->next!=0)
    {temp=current->next;
    while(temp!=0)
    {
        current=temp->pre;
        while(current!=0 )
        {
            if(strcmpi(current->name ,temp->name )==0)
            {
                temp->b=1;
            }
            current=current->pre;
        }


        temp=temp->next;
    }
    }
}
void index(stptr start)
{
    int index=0;
    stptr current = start->next;
    while(current!=0)
    {
        if(current->b == 0)
        {
            current->index=index;
            index++;
        }
        else
        {
            current->index= -1;
        }
        current=current->next;
    }
}

void print2(stptr start)
{

    stptr current;
    current = start ->next;
    while(current != 0)
    {
        printf("%s-%s-%d\n" , current->name ,current ->type,current->index);
        current = current -> next;
    }
}
/*void dbz(tl1ptr start ,stptr start2)
{
    tl1ptr cur;
    stptr cur2;
    cur =start->next;
    cur2=start->next;
    while(cur != 0)
    {
        if(strcmpi(cur->data , "/")==0)
        {

            if(cur->next !=0)
            {
                cur = cur ->next;
                if(strcmpi(cur->data ,"0")==0)
                    puts("ERROR");
                else
                {
                    while(strcmpi(cur->data , cur2->name) != 0  &&  cur2!=0)
                    {

                        cur2=cur2->next;


                    }
                    if(cur2!=0)
                    {
                        if(strcmpi(cur2->value ,"0")==0 )
                            printf("ERROR");
                    }

                }


            }
        }
        cur2=start2;
        cur=cur->next;
    }
}
/*void valuecheking(tl1ptr start ,stptr start2)
{
    tl1ptr cur = start -> next;
    stptr cur2 = start2->next;
    while(cur != 0)
    {
        if(isop(cur->data)==0)
        {
            if(cur->next!=0)
            {
                cur =cur->next;
            }
        }
    }
}
void typecheching(tl1ptr start , stptr start2)
{
    tl1ptr cur=start->next;
    stptr cur2=start2->next;
    char a[10];
    while(cur != 0)
    {
        if(isop(cur->data)==0)
        {
            cur = cur->pre;
            if(d(cur->data)==2)
            {
                cur2=start2->next;
                while(cur2 != 0 && strcmpi(cur->data , cur2->name)!=0)
                {
                    cur2 = cur2->next;
                }
                if(cur2 == 0)
                {
                    puts(" avali tarif nashode ast");

                }
                else
                {
                    strcpy(a , cur2-> type);
                    if(cur->next != 0)
                        cur = cur->next;
                    if(cur ->next !=0)
                        cur = cur -> next;
                    cur2=start2->next;
                    while(cur2 != 0 && strcmpi(cur->data , cur2->name)!=0)
                {
                    cur2 = cur2->next;
                }
                if(cur2 == 0)
                {
                    puts(" dovomi tarif nashode ast");

                }
                else{
                        if(strcmpi(cur2->type, a)!= 0)
                            printf("error yeki nistand");


                }
                }
            }
        }
        cur=cur->next;
    }
}*/
tl1ptr statement(tl1ptr current)
{
    tl1ptr cur;
    char a[10];
    if(strcmpi(current->atri , "num")==0)
    {
        if(current ->next != 0)
        {
            current = current -> next;
            if( strcmpi(current->data , "=")==0 || strcmpi(current->data ,";")==0)
                {
                    if(strcmpi(current->data ,"=")==0)
                    {
                        printf("error in line %d after a num shoud be ... no = " ,current->line);
                        while(current != 0 && strcmpi(current->data , ";")==0)
                        {
                            current=current->next;

                        }

                        return current;
                    }

                else
                {
                    printf("aaaaafffffarrrrrin");
                    return current;
                }



                }
            else
            {
                strcpy(a, current->data);
                if(a[0]!='+' && a[0]!='*' && a[0]!='/' && a[0]!='-' && a[0]!='%')
                    {printf("error in line %d after a num shoud be ..." , current ->line);

                    while(current != 0 && a[0]!=';')
                    {
                        current->b=1;
                        current=current->next;
                        if(current!=0)
                            strcpy(a,current->data);
                    }
                    if(current!=0)
                    {current->b=1;}
                    puts("**");
                    return current;

                    }
                else
                {
                    if(current -> next != 0)
                    {
                        current=current->next;
                        strcpy(a , current->data);
                        if(strcmpi(current->atri , "num")!=0 && strcmpi(current->atri ,"id")!=0 )
                            {

                                if(a[0]==';')
                                {
                                    printf("error in line %d after op shoud be num or id no ; " ,current->line);
                                    current->b=1;
                                    current=current->pre;
                                    strcpy(a,current->data);
                                    while(current!=0 && a[0]==';')
                                    {
                                        current->b=1;
                                        current=current->pre;
                                        strcpy(a,current->data);
                                    }
                                    puts("***");
                                    return current;
                                }
                                else
                                    {
                                        printf("error in line %d after an op shoud be a num or id" ,current->line);
                                        while(current->next !=0 && strcmpi(current->data ,";")!=0)
                                        {
                                            current->b=1;
                                            current=current->next;
                                        }
                                        if(current !=0)
                                            {current->b=1;}

                                        return current;
                                    }

                            }
                            if(current->next!=0)
                            {
                                current=current->next;
                                strcpy(a, current->data);
                                if(a[0]!=';' )
                                {
                                    printf("error in line %d at the end of a statement shoud be ;" ,current->line);
                                    while(a[0]!=';' && current!=0)
                                    {
                                        current->b=1;
                                        current=current->next;
                                        if(current!=0)
                                        {strcpy(a,current->data);}                                    }

                                    if(current!=0)
                                    {current->b=1;}

                                    return current;
                                }
                                else { return current;}
                            }
                            else
                                {puts("your satement finished whithout ;"); return current;}

                    }
                }
            }
        }

    }

 if(strcmpi(current->atri , "id")==0)
 {
     if(current->next != 0)
     {
         current=current->next;
        strcpy(a,current->data);
         if(a[0]!= '=')
         {
              if(a[0]==';')
         {
             printf("ok");
             return current;
         }

             else
                {strcpy(a, current->data);
                if(a[0]!='+' && a[0]!='*' && a[0]!='/' && a[0]!='-' && a[0]!='%')
                    {printf("error in line %d shoud be+ .. here" , current ->line);

                    while(current != 0 && a[0]!=';')
                    {
                        current->b=1;
                        current=current->next;
                        if(current!=0)
                            strcpy(a,current->data);
                    }
                    if(current!=0)
                    {current->b=1;}

                    return current;

                    }
                else
                {
                    if(current -> next != 0)
                    {
                        current=current->next;
                        strcpy(a , current->data);
                        if(strcmpi(current->atri , "num")!=0 && strcmpi(current->atri ,"id")!=0 )
                            {

                                if(a[0]==';')
                                {
                                    printf("error in line %d after an op should be num or id no ;" ,current->line);
                                    current->b=1;
                                    current=current->pre;
                                    strcpy(a,current->data);
                                    while(current!=0 && a[0]==';')
                                    {
                                        current->b=1;
                                        current=current->pre;
                                        strcpy(a,current->data);
                                    }

                                    return current;
                                }
                                else
                                    {
                                        printf("error in line %d after an op shoud be a num or an id" ,current->line);
                                        while(current->next !=0 && strcmpi(current->data ,";")!=0)
                                        {
                                            current->b=1;
                                            current=current->next;
                                        }
                                        if(current !=0)
                                            {current->b=1;}

                                        return current;
                                    }

                            }
                            if(current->next!=0)
                            {
                                current=current->next;
                                strcpy(a, current->data);
                                if(a[0]!=';' )
                                {
                                    printf("error in line %d the statement should finish with ;" ,current->line);
                                    while(a[0]!=';' && current!=0)
                                    {
                                        current->b=1;
                                        current=current->next;
                                        if(current!=0)
                                        {strcpy(a,current->data);}
                                                                           }

                                    if(current!=0)
                                    {current->b=1;}

                                    return current;
                                }
                                else { printf(" ERROR in line %d at the end of a statement shoud be ; " ,current->line); return current;}
                            }
                            else
                                {puts("YOUR PROGRAM FINISH WHITHOUT ;"); return current;}

                    }
                    else if(current->next ==0)
                    {
                        printf("ERROR YOUR STATEMEN WASNOT C");
                    }
                }


                }
         }
         else if(a[0]=='=')
         {
             if(current->next != 0)
             {
                 current = current->next;
                 strcpy(a,current->data);
                 if(a[0]==';')
                 {printf("error in line %d after = should be a math s no ;" ,current->line);

                 current->b=1;
                 current=current->pre;
                 strcpy(a,current->data);
                 while(current !=0 && a[0] != ';')
                 {
                     current->b=1;
                     current=current->pre;
                     if(current!= 0)
                     {
                         strcpy(a, current->data);
                     }
                 }

                return current;

                 }
                 else
                 {
                     if(strcmpi(current->atri ,"num") !=0 && strcmpi(current->atri ,"id")!=0 )
                     {
                         printf("error in line %d after = should be a num or an id" ,current->line);
                         if(current->next != 0)
                         {
                             current=current->next;
                             strcpy(a,current->data);
                             while(current!=0 && a[0]!= ";")
                             {
                                 current->b=1;
                                 current=current->next;
                                 if(current!=0)
                                 {
                                     strcpy(a,current->data);
                                 }
                             }
                             return current;
                         }
                         else
                         {
                             printf("error in line %d your s is not comp" ,current->line);
                             return current;
                         }
                     }
                     else
                     {
                         if(current->next != 0)
                           {

                            current = current->next;
                            strcpy(a, current->data);
                if(a[0]!='+' && a[0]!='*' && a[0]!='/' && a[0]!='-' && a[0]!='%')
                    {printf("error in line %d here shoud be an op" , current ->line);

                    while(current != 0 && a[0]!=';')
                    {
                        current->b=1;
                        current=current->next;
                        if(current!=0)
                            strcpy(a,current->data);
                    }
                    if(current!=0)
                    {current->b=1;}
                    else
                    {printf("your program finish without ';'" );  return current;}

                    }
                else
                {
                    if(current -> next != 0)
                    {
                        current=current->next;
                        strcpy(a , current->data);
                        if(strcmpi(current->atri , "num")!=0 && strcmpi(current->atri ,"id")!=0 )
                            {

                                if(a[0]==';')
                                {
                                    printf("error in line %d here shoud be a num or an id no ;" ,current->line);
                                    current->b=1;
                                    current=current->pre;
                                    strcpy(a,current->data);
                                    while(current!=0 && a[0]==';')
                                    {
                                        current->b=1;
                                        current=current->pre;
                                        strcpy(a,current->data);
                                    }

                                    return current;
                                }
                                else
                                    {
                                        printf("error in line %d here shoud be a num or an id " ,current->line);
                                        strcpy(a, current->data);
                                        while(current !=0 && a[0]!=';')
                                        {
                                            current->b=1;
                                            current=current->next;
                                            if(current!=0)
                                                strcpy(a,current->data);
                                        }
                                        if(current !=0)
                                            {current->b=1;}
                                        else
                                        {
                                            printf("error in line %d your s is not comp " ,current->line);
                                            return current;
                                        }
                                    }

                            }
                            if(current->next!=0)
                            {
                                current=current->next;
                                strcpy(a, current->data);
                                if(a[0]!=';' )
                                {
                                    printf("error in line %d your s shoud finish with ;" ,current->line);
                                    while(a[0]!=';' && current!=0)
                                    {
                                        current->b=1;
                                        current=current->next;
                                        if(current!=0)
                                        {strcpy(a,current->data);}                                    }

                                    if(current!=0)
                                    {current->b=1;}

                                    return current;
                                }
                                else { puts(" OK "); return current;}
                            }
                            else
                                {printf(" your s  finish without ; "); return current;}

                    }
                }
                     }
                     }

                 }
             }

         }
         }
     }

     }
     void syntax(tl1ptr current)
     {

         while(current!=0  )
         {
             if(current->next!=0)
             {
                 current=current->next;
                 if(current !=0 && current->b ==1)
             {
                 while(current!=0 && current->b==1)
                 {
                     current=current->next;
                 }
             }
             if(current !=0)
             {current=statement(current);}
             }
             else
                return;
         }
     }


/*void ifelsew(tl1ptr current)
{
    tl1ptr temp;
    temp= current;
  if(current->next !=0)
  current=current->next;
  if(strcmpi(current->data ,"(")!=0)
    printf("error in line %d" ,currenr->line);
  else
  {
      if(current->next!=0)
        current=current->next;
      conditioncheck(current);
      if(current->next != 0)
        current= current->next;
      if(strcmpi(current->data , ")") != 0)
        printf("error in line %d" ,current->line);
      if(current->next != 0)
        current = current->next;
      if(strcmpi(current->data ,"{")!=0)
        printf("error in line %d" , current->line);
      if(current->next != 0)
        current = current->next;
      while(current !=0 && strcmpi(current->data , "}")!=0)
      {
          root=statement(current);
          current=current->next;
      }
      if(current == 0)
        printf("the statement in line %d doesnt have }" ,temp->line );
      if(current -> next ==0)
               printf("the statement in line %d doesnt have }" ,temp->line );
  }
}
{

}*/
int main()
{
    stptr start2;
    tl1ptr start;
    tl1ptr current;
    stptr cur;
    start = malloc(sizeof(tl1));
    start->next=NULL;
    start-> pre = NULL;
    strcpy(start->data , "unkown");
    start2=malloc(sizeof(st));
    start2->next =NULL;
    start2->pre = NULL;
    tokenise(start);
    atribute(start);

    makesymboltable(start , start2);
    sede(start2);
    index(start2);
    print2(start2);


    return 0;
}
