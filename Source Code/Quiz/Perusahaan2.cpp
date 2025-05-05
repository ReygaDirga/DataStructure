#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct data{
	char name[100];
	char ticket[100];
	struct data* next;
	struct data* prev;
}*h,*t,*c;

void push(char name[], char ticket[]){
	struct data *data = (struct data*)malloc(sizeof(struct data));
	data->name = name;
	data->ticket = ticket;
	data->next = NULL;
	data->prev = NULL;
	
	
	struct data *temp = h;
	while(temp){
		int compare = strcmp(temp->ticket, c->ticket);
		
		if(compare > 0){
			c->next = temp->next;
			c->prev = temp->prev;
			
			if(temp->prev){
				temp->prev->next = h;
			}else{
				h = c;
			}
			temp->prev = c;
			return;
		}
		temp = temp->next;
	}
	t->next = c;
	c->prev = t;
	t = c;
}

void pop(char name[]){
	if(h == NULL){
		return;
	}
	struct data *temp = h;
	while(temp != NULL && strcmp(temp->name, name) != 0){
		temp = temp->next;
	}
	if(temp == NULL){
		return;
	}
	if(temp == h){
		h = h->next;
		if(h){
			h->prev = NULL;
		}
		free(temp);
	}else if(temp == t){
		t = t->prev;
		if(t){
			t->next = NULL;
		}
		free(temp);
	}else{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		free(temp);
	}
}

int main(){
	
	return 0;
}
