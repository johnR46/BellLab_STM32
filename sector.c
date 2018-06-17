#include<stdio.h>
#include<string.h>
  
char strn[] = "The Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or more The Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or more The Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or moreThe Events Database is a compiled listing of major U.S. events and hotel performance data for 2016. Updated annually, this dataset includes detailed information on events over a two-year period with a minimum estimated attendance of 10,000 or more";

int k_str = sizeof(strn); // k/4096
int n_sector = 0;
int n = 0;
int status  = 0;

int cursor  = 0;
char sector[0][4096];  
void Sector(){
	
	
	if(status == 1){
		int i,j;
		for(i = 0; i < 1; i++){
			for(j = 0; j < 20; j++){
				printf("%c",sector[n][cursor +=1]);
			}
		}
		
		if(cursor == 4096){
			n+=1;
			cursor = 0;
		}
	}
	if(status == 0){
			int i,j;
		for(i = 0; i < 1; i++){
			for(j = 0; j < 20; j++){
				printf("%c",sector[n][cursor -=1]);
			}
		}
		
		if(cursor == 0){
			n-=1;
			cursor = 4096;
		}
	}
	
}

void setsector(){
	n_sector = k_str/4096;
	printf("n_sector = %d",n_sector);
	sector[n_sector][4096];

	
	
}


void main(){
	
	printf("status is 0 and 1 only \n");
	
	printf("Enter input is : ");
	scanf("%d",&status);
	printf("process ... \n");
	setsector();
}

