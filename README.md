notepad

	< 4096, 20 =  204 > .. ok
1. add text
	- add First shiftpoint is n 
		- add left to right 
			- 20 character to 1 line (20 to newline by /r/n auto)  .. > (ok)
				(fix  18 character  to /r/n)
					- cut to rom  ... ok  EndDisplay  (ok)

			- by enter keycode is now newline it's add --------- to 20 character and newline ..> (ok)  buttomnewline + EndDisplay
			
		
		- insert mid  to left mid right
			- in now line edit to 18 character add \r\n remmove last character to newline .. > (ok ) 

				


	- add middle shiftpoint is  1 <-> n-1
		- 20 character to 1 line (20 to newline by /r/n auto)  .. > 
				(fix  18 character  to /r/n)
					- cut to rom  ... 

			- by enter keycode is now newline it's add --------- to 20 character and newline ..> 
			
		
		- insert mid  to left mid right
			- in now line edit to 18 character add \r\n remmove last character to newline .. > 
				


	- add last shiftpoint  is 0
		- 20 character to 1 line (20 to newline by /r/n auto)  .. > (now fix)
				(fix  18 character  to /r/n)
					- cut to rom  ...  

			- by enter keycode is now newline it's add --------- to 20 character and newline ..> 
			
		
		- insert mid  to left mid right
			- in now line edit to 18 character add \r\n remmove last character to newline .. > 
				
	
		


fun ... 
  newline 
	-newline = 	AAAA ------------ (ok )

 convertArrayStr_2D_to_1D
	in - str1[notepad_max_X][notepad_max_y] = {"john nonphala\r\n","sursak sinjlern\r\n","omg\r\n"};
	out = 	john nonphala
		sursak sinjlern
		omg


solution  add newline in insert character (* = new addstr)
	- solution (1 line  = AB     \r\n 2 line =      C\r\n)
		->   if in fun newline call by notepad ( (note.setcursor < note.cursor ) && (note.cursor > 18)    ) call fun insertNewline ?
			- (* = add newstr) in str  = john nonphala Sura* is cursor = 18 + 1  = 19 setcursor = 17+1 = 18 
				-  "John nonphala Sur||a*|" 
				- add r\n is cursor 19 - 20 = "john nonphala Sur*\r\n"
			
			- if(cursor >= 18 && setcursor < cursor )

			-> insertNewline (int setcursor)
				 - "john ||*nonphala Sura|" << ?? 
					-copynstr(note.str_buff,note.str_ram+setcursor,20); new = "nonphala Sura"  old =  "john ||**nonphala Sura|"
					
				
			*** cancle  befor shifleft right edit 	   
				
				
				 	
			
		
		
			  
			
 




	

