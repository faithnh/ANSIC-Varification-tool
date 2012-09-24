/*PROGRAM_START*///#xinclude<stdio.h>

int main(void){
	int a[10];
	int b[10];
	int i = 0, j = 0;
	/*
	ŒŸØ®
	if(a[i][j] == 0){
		ŒŸØ®
		if(a[i][j] == 0){
		}
		else{
			ŒŸØ®
			if(b[a[i][j]] == 0){
				ŒŸØ®
				if(b[a[i][j]] == 0){

				}
			}
		}
	}else{
		ŒŸØ®
		if(b[a[i][j]] == 0){
			ŒŸØ®
			if(b[a[i][j]] == 0){

			}
		}
	}
	if ( b [ 1 ] ) {
		if ( b [ 2 ] == 0 ) {
			if ( b [ 3 ] == 0 ) {
			}else{
				if ( b [ 4 ] == 0 ) {
					if ( b [ 5 ] == 0 ) {
					}
				}
			}
		}else{
			if ( b [ 4 ] == 0 ) {
				if ( b [ 5 ] == 0 ) {
				}
			}
		}
	}else{
		if ( b [ 4 ] == 0 ) {
			if ( b [ 5 ] == 0 ) {
			}
		}
	}
	*/
	i = 9;
	do{
		i--;
	}while(i > 0 || b[i] == 0);
	i = 9;
	while(1 / i == 0 || i / i == 1){
		if( b[i] == 0){
			b[i] = i;
		}else{
			b[i] = 0;
		}
		i--;
	} 
	/*
		log_or_expr
			log_and_expr
				log_and_expr
					expr
					expr
				expr
			log_and_expr
				expr
				expr
	*/
	/*
	if(i1){
	}
	else{
		if(j1){
		}
		else{
			if(j2){
			}
			else{
				if(i3){

				}else{
					if(j3){

					}
				}
			}
		}
	}
	*/
	/*if( ((i1 || j1) || j2) || (i3 || j3)){

	}*/
	/*
	log_or_expr
		log_or_expr
			log_or_expr
				expr
				expr
			expr
		log_or_expr
			expr
			expr
	*/
	/*
	if(i1){
		if(j1){
		
		}else{
			if(j2){}
			else{
				if(i3){

				}else{
					if(j3){

					}
				}
			}
		}
	}else{
		if(j2){}
		else{
			if(i3){

			}else{
				if(j3){

				}
			}
		}
	}
	*/
	/*if( ((i1 && j1) || j2) || (i3 || j3)){

	}*/
	/*
	log_or_expr
		log_or_expr
			log_and_expr
				expr
				expr
				if(i1){
					if(j1){
					}
				}
			expr
			if(i1){
				if(j1){
				}else{
					if(j2){}
				}
			}else{
				if(j2){}
			}
		log_or_expr
			expr
			expr
			if(i1){
				if(j1){
				}else{
					if(j2){}
					else{
						if(i3){}
						else{
							if(j3){}
						}
					}
				}
			}else{
				if(j2){}
				else{
					if(i3){}
					else{
						if(j3){}
					}
				}
			}
	*/
	/*
		if(i1 || j1 && j2){
		}else{
			if(i3 || j3){
			}
		}
   
		if(i1){

		}else{
			if(j1 && j2){
			}else{
				if(i3 || j3){
				}
			}
		}
		
		if(i1){

		}else{
			if(j1){
				if(j2){}
				else{
					if(i3 || j3){
					}
				}
			}else{
				if(i3 || j3){
				}
			}
		}

		if(i1){

		}else{
			if(j1){
				if(j2){}
				else{
					if(i3){}
					else{
						if(j3){
					}
				}
			}else{
				if(i3){}
				else{
					if(j3){
				}
			}
		}
	*/
	/*if( (i1 || (j1 && j2)) || (i3 || j3)){

	}*/
	/*
		log_or_expr
			()
			else{
				()
			}
			log_or_expr
				expr
				if(i1){
				
				}else{
					()
				}
				log_and_expr
					expr
					expr
				if(j1){
					if(j2){
					}
				}
			log_or_expr
				expr
				expr
			if(i3){
			}else{
				if(j3){}
			}
	*/
	return 0;
}

/*
	or
		or
			1
			2
		3
	if(1){
	}else{
		if(2){
		}else{
			if(3){}
		}
	}
*/

/*
	or
		and
			1
			2
		3
	if(1){
		if(2){
		}else{
			if(3){}
		}
	}else{
		if(3){}
	}
*/
/*
	and
		or
			1
			2
		3
	if(1){
		if(3){}
	}else{
		if(2){
			if(3){}
		}
	}
*/
/*
	or
		and
			or
				1
				2
			3
		4
	if(1){
		if(3){
		}else{
			if(4){
			}
		}
	}else{
		if(2){
			if(3){
			}else{
				if(4){
				}
			}
		}
	}
	‡@
	if(1){
		‡A
	}else{
		if(2){
			‡A
		}
	}
	‡A
	if(3){
	}‡B
	‡B
	if(4){
	}
	if(((1 || 2) && 3) || 4)
*/
/*
	and
		or
			and
				1
				2
			and
				3
				4
		5

	if(1){
		if(2){
			if(5){}
		}else{
			if(3){
				if(4){
					if(5){}
				}
			}
		}
	}else{
		if(3){
			if(4){
				if(5){}
			}
		}
	}
	‡@
	if(1){
		if(2){
			‡B
		}‡A
	}‡A
	‡A
	if(3){
		if(4){
			‡B
		}
	}
	‡B
	if(5){}
*/

/*
	and
		or
			1
			or
				2
				3
		and
			or
				4
				5
			or
				6
				or
					7
					8
	‡@
	if(1){
		‡B
	}else{
		‡A
	}
	‡A
	if(2){
		‡B
	}else{
		if(3){
			‡B
		}
	}
	‡B
	if(4){
		‡C
	}else{
		if(5){
			‡C
		}
	}
	‡C
	if(6){
	}else{
		‡D
	}
	‡D
	if(7){
		if(8){
		}
	}

	if(1){
		‡C
	}else{
		‡A
	}
	if(2){
		‡C
	}else{
		‡B
	}
	if(3){
		‡C
	}else{
	}
	if(4){
		‡E
	}else{
		‡D
	}
	if(5){
		‡E
	}else{
	}
	if(6){
	}else{
		‡F
	}
	if(7){
	}else{
		‡G
	}
	if(8){
	}else{
	}
*/

/*
	and(1,2,3)
		or(1)
			1
			and(2)
				2
				3
		and
			or
				4
				5
			or
				6
				and
					7
					8
	if(1){
		4
	}else{
		2
	}
	if(2){
		3
	}else{
	}
	if(3){
		4
	}else{
	}
	if(4){
		6
	}else{
		5
	}
	if(5){
		6
	}else{
	}
	if(6){
	}else{
		7
	}
	if(7){
		8
	}else{
	}
	if(8){
	}else{
	}
*/
/*
	typedef struct logical{
		struct logical *yes;
		struct logical *no;
		CSTLString *expr;
		CSTLString *validation;
	} LOGICAL;

	U‚é•‘‚¢
	//or‚Ìê‡
		//®”Ô†‚ğ‰Šú‰»
		//‚P‚Â–Ú‚Ì®‚ğ‚İ‚é
		//®”Ô†‚ÌŠeX‚Ì”Û’è‚µ‚Ä‚¢‚é‚Æ‚±‚ë‚ÉŸ‚Ì”Ô†‚ğ’Ç‰Á‚·‚éB
		//‚Q‚Â–Ú‚Ì®‚ğ‚İ‚é
	//and‚Ìê‡
		//‚P‚Â–Ú‚Ì®‚ğ‚İ‚é
		//®”Ô†‚ÌŠeX‚Ìm’è‚µ‚Ä‚¢‚é‚Æ‚±‚ë‚ÉŸ‚Ì”Ô†‚ğ’Ç‰Á‚·‚éB
		//‚Q‚Â–Ú‚Ì®‚ğ‚İ‚é
	//®‚Ìê‡
		//®ƒf[ƒ^‚ğì¬‚µAƒŠƒXƒg‚ÉŠi”[‚·‚é
	//ã‹LˆÈŠO
		//Ä‹A“I‚ÉƒAƒNƒZƒX‚·‚é
*/