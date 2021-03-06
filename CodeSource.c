#include <stdio.h>
#include <stdlib.h>
 
typedef struct _Process{
	int id;
	int temp_rest;
	int temp_arrive;
	int temp_Attende;
	int priority;
	int temp_sejour;
	struct _Process *next;
}Process;
Process *Ini_processus(){
	Process *P;
	P=(Process*)malloc(sizeof(Process));
	P->next=NULL;
	return P;
}
Process *create_processus (int id,int t_res,int t_arrire,int priority){
	Process *P=Ini_processus();
	P->id=id;
	P->priority=priority;
	P->temp_arrive=t_arrire;
	P->temp_rest=t_res;
	P->temp_Attende=0;
	P->temp_sejour=P->temp_Attende+P->temp_rest;
	return P;
}
void Affiche_Proce(Process *P){
	printf("Id = %d \t",P->id);
	printf("Remning Time = %d \t",P->temp_rest);
	printf("Arrive Time = %d \t",P->temp_arrive);
	printf("Priority = %d \t ",P->priority);
	printf("Waiting Time = %d \n ",P->temp_Attende);
}
typedef struct {
	Process *Head;
	Process *Tail;
	int Size;
}File;
typedef File *file;
file ini_file(){
	file f;
	f=(file) malloc(sizeof(File));
	f->Head=NULL;
	f->Tail=NULL;
    f->Size=0;
    return f;
}
int vide_File(file F){
	if(F->Head==NULL && F->Tail==NULL ) {  return 1;   }
	else return 0;
}
void Affiche_File(file F){
	if(vide_File(F)==1) {   printf(" \n File is empty"); exit(1); }
	else {
	   	Process*temp=F->Head;
	   	int i=1;
	   	while(temp!=NULL){
	   		printf("La Process %d :",i);
	   		Affiche_Proce(temp);
	   		temp=temp->next;
	   		i++;
		   }
	}
}
 
void Emfiler(file f,Process*P){
	if(vide_File(f)==1) {  f->Tail=P;   f->Head=P;  }
	else {
	f->Tail->next=P;
	f->Tail=P;
        f->Size++;
	}
}
int Taile_File(file f){
	int T;
	if(vide_File(f)==1) {   return 0;   }
	else {
     	Process*temp=f->Head;
     	T=0;
     	while(temp!=NULL){
     		T++;
		    temp=temp->next;
		   	}
        f->Size=T;
      	return T;
	}
}
Process*pop__process(file f){
	Process*P;
	if(vide_File(f)==1){    printf("_ _File is Empty_ _") ; exit(1);   }
	else {
		P=f->Head;
		f->Head=f->Head->next;
                f->Size--;
		return P;
	}
}
void read_process(file f){
	if(vide_File(f)==1){    printf("_ _File is Empty_ _") ; exit(1);   }
	else {
		Affiche_Proce(f->Head);
	}
}
void Echange(Process*A,Process*B){
	Process*C=Ini_processus();
	C->id=A->id;
	C->temp_rest=A->temp_rest;
	C->temp_arrive=A->temp_arrive;
	C->priority=A->priority;
 
	A->id=B->id;
	A->temp_rest=B->temp_rest;
	A->temp_arrive=B->temp_arrive;
	A->priority=B->priority;
 
	B->id=C->id;
	B->temp_rest=C->temp_rest;
	B->temp_arrive=C->temp_arrive;
	B->priority=C->priority;
 
}
void Tre_Arrive(file f){
	if(f->Head==NULL) {  printf("Pile is Empty ");  }
	else {
	    Process*temp=f->Head;
	    int T=Taile_File(f);
	    int i,j;
	    for(i=1;i<T;i++){
	       for(j=1;j<T;j++) {
	       	  if (temp->next->temp_arrive==temp->temp_arrive){
	       	  	  if(temp->next->priority>=temp->priority){
	       	  	  	  Echange(temp,temp->next);
					   }
				 }
	          else if(temp->next->temp_arrive<temp->temp_arrive){  Echange(temp,temp->next);    }
	           temp=temp->next;
		    }
	temp=f->Head;
    	}
	}
}
void push_FIFO(file f){
	Tre_Arrive(f);
	int a;
	Process*tump=f->Head;
	a=tump->temp_rest;
	while(tump->next!=NULL){
	tump->next->temp_Attende=a-tump->next->temp_arrive;
	if(tump->next->temp_Attende<0){  tump->next->temp_Attende=0;  }
	a=tump->next->temp_Attende+tump->next->temp_rest+tump->next->temp_arrive;
	tump=tump->next;
	}
}
void Defile_Emfile(file f1,file f2){
	Emfiler(f2,pop__process(f1));
}
Process*Suprime_Pos(file f,int pos){
	Process*tump;
	int i;
	Process*P;
	if(pos>Taile_File(f)){   printf("Position >Taile_de_File "); exit(1); }
	else {
	  if(pos==1){
	     if(f->Head->next==NULL){
		  P=f->Head;
		  f->Head=NULL;
		  f->Tail=NULL;
	     }
	     else {
		   tump=f->Head;
	       P=f->Head;
	       f->Head=f->Head->next;	
	     }
    	}
	else if(pos==Taile_File(f)){
	       if(f->Head->next==NULL){
		    P=f->Head;
		    f->Head=NULL;
		    f->Tail=NULL;
	      }	
	      else {
	       tump=f->Head;
	       while(tump->next->next!=NULL){
	   		tump=tump->next;
		   }
		   P=f->Tail;
		   f->Tail=tump; 
		   tump->next=NULL; 	
		  }
    	}
	else {
	   	    i=1;
	   	    tump=f->Head;
	        while(i!=pos-1){
	        tump=tump->next;
	        i++;
	        }
	        P=tump->next;
	        tump->next=tump->next->next;	
    	 }
 
	}
	return P;
}
file push_SJF(file f1){
	file f2=ini_file();
	Process*tump1;
	Process*tump2;
	int id,T_r,T_a,Prio;
	tump1=f1->Head;
	while(tump1!=NULL){
	tump1->temp_Attende=0;
	tump1=tump1->next;
	}
	int SJ;
	int pos=0;
	int pos_SJ;
	Process*P_SJ;
	int a;
    Defile_Emfile(f1,f2);
	while(Taile_File(f1)!=0){
 
	tump2=f2->Tail;
	tump1=f1->Head;
    SJ=f1->Head->temp_rest;
	a=tump2->temp_Attende+tump2->temp_rest+tump2->temp_arrive;
	pos_SJ=1;
	while(tump1!=NULL){
		pos++;
		if(tump1->temp_arrive<=a){
			if(tump1->temp_rest<=SJ){
				SJ=tump1->temp_rest;
				pos_SJ=pos;
			}
		}
	  tump1=tump1->next;
	}
	P_SJ=Suprime_Pos(f1,pos_SJ); 
	id=P_SJ->id;
	T_r=P_SJ->temp_rest;
	T_a=P_SJ->temp_arrive;
	Prio=P_SJ->priority;
	Emfiler(f2,create_processus(id,T_r,T_a,Prio));
	}
	int b;
	Process*tump3=f2->Head;
	a=tump3->temp_rest;
	while(tump3->next!=NULL){
	tump3->next->temp_Attende=a-tump3->next->temp_arrive;
	if(tump3->next->temp_Attende<0){  tump3->next->temp_Attende=0;  }
	a=tump3->next->temp_Attende+tump3->next->temp_rest+tump3->next->temp_arrive;
	tump3=tump3->next;
	}
    return f2;
}
void affiche_Tab(int Tab[22]){
	int i;
	for(i=0;i<20;i++){
		if(i<10){ printf("%d      ",Tab[i]); }
		else { printf("%d     ",Tab[i]);  }
	}
 
}
void affiche_Tab2(char Tab[22],int c){
	int i;
	printf("Process %d:",c);
	for(i=0;i<22;i++){
     printf("%c      ",Tab[i]);
	}
	printf("\n");
}
void Diagramme(file F1){
	Process*tump=F1->Head;
	char Taa[22];
	int a,b,c=0,i;
	while(tump!=NULL){
		c++;
		a=tump->temp_arrive+tump->temp_Attende;
		b=tump->temp_arrive+tump->temp_Attende+tump->temp_rest;
    	for(i=0;i<tump->temp_arrive;i++){   Taa[i]=' ';  }
        for(i=tump->temp_arrive;i<a;i++){ Taa[i]='o';  }
        for(i=a;i<b;i++){  Taa[i]='x';  }
        for(i=b;i<22;i++){ Taa[i]=' '; }
        printf("\n");
        affiche_Tab2(Taa,c);
		tump=tump->next;
	}
	int Taa2[22];
	    for(i=0;i<22;i++){ Taa2[i]=i; }
	    printf("\n");
	    printf("          "); affiche_Tab(Taa2);
}
int main(int argc, char *argv[]) {
	int id,T_a,T_r,Prio,n,i;
	file F1=ini_file();
	printf("Entrer Nombre Des Process :");
	scanf("%d",&n);
	for(i=1;i<=n;i++){
	printf("P%d : \n",i);
	printf("Id : ");
	scanf("%d",&id);
	printf("T_a : ");
	scanf("%d",&T_a);
	printf("T_r : ");
	scanf("%d",&T_r);
	printf("Prio : ");
	scanf("%d",&Prio);
	Emfiler(F1,create_processus (id,T_r,T_a,Prio));
	}
	push_FIFO(F1);
	Affiche_File(F1);
	printf("Diagramme FIFO : \n");
	Diagramme(F1);
    printf("\n");
	file F2=ini_file();
	F2=push_SJF(F1);
	Affiche_File(F2);
	printf("Diagramme SJF : \n");
	Diagramme(F2);
	return 0;
}
