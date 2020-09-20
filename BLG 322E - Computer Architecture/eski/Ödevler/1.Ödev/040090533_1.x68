*-----------------------------------------------------------
* Program    : HeapSort
* Written by : 
*	Name  : Abdullah AYDE�ER 
*	Number: 040090533
* Date       : 23.02.2012
* Description: Build-Max-Heap fonksiyonunun algoritmas�n�n�n MC68000 �zerinde ger�eklenmesi.
*-----------------------------------------------------------
	
	ORG $0400
size 	DC.W $000B

	ORG $0500
array 	DC.B $FF,$11,$13,$12,$14,$15,$16,$17,$18,$1A,$19	


;Functions
	ORG 	$0900
MxHp				*Altprogram ba�lang�c�
	MOVEM.L	D2-D7/A0, -(A7)	*Altprogramda kullan�lan registerlar�n altprogramdan d�n��te i�eri�inin de�i�memesi i�in y���na at�ld�.
	 
	MOVE.L	$20(A7),D7	*Y���ndan parametre olarak gelen indis de�eri okundu.($20 = 32 birim a�a��da)
	MOVE.W	D7, D5		*D5 = i(fonksiyona parametre olarak gelen de�i�ken)'i g�stermek i�in kullan�ld�.
				
	ASL	#1, D7
	MOVE.W	D7, D6		*D6 = l(2*i) de�i�keni i�in
	ADDQ	#1, D7		*D7 = r(2*i+1) de�i�keni i�in
	
	MOVE.L	#array,A0	*A0 = Array'in ba�lang�� adresi 	

	MOVE.B	(A0,D5.W),D3	*D3 = A[i] verisini tutmak i�in kullan�ld�.
		
	CMP	size, D6	*If l(D6)>size -- 
	BGE	LEFT		*�leri dallanma oldu�u i�in algoritmadaki ko�ulun tersi bir ko�ulla, yani l>=heap-size ise dallanma olacak LEFT etiketine
	CMP.B	(A0,D6.W),D3	*Else if A[i]>=A[l]
	BGE	LEFT		*Yine ileri dallanma oldu�u i�in algoritman�n tersi olarak A[i]>=A[l] ise dallanma olacak LEFT etiketine
	MOVE.W	D6, D4		*Else; largest(D4) <- l(D7) atamas� yap�lacak
	
	BRA	LEFTT		*Bu sat�ra inilmi�se ko�ulsuz olarak LEFTT etiketine dallan�lacak
	
LEFT	MOVE.W	D5, D4		*largest(D4) <- i(D5) atamas� yap�l�yor.

LEFTT	
	MOVE.B	(A0,D4.W),D3	*D3 = A[largest] y�klendi.
	
	CMP 	size, D7	*If heap-size>r		-- yukar�dakilere benzer �ekilde ko�ullama ve dallanmalar...
	BGE 	RIGHT		*Branch RIGHT
	CMP.B	(A0, D7.W),D3	*Else if A[largest]>=A[r]
	BGE	RIGHT		*Branch RIGHT
	MOVE.W	D7, D4		*Else; largest(D4) <- r(D6) atamas� yap�ld�
	
	
RIGHT	
	CMP	D4, D5		*If largest = i	E�er birbirine e�itse do�rudan fonksiyon sonlanacak
	BEQ	BITIR		*Branch BITIR
	*Takas...		*Else, yani e�it de�ilse takas i�lemini ger�ekle�tirip, fonksiyonu largest de�eri i�in bir daha �a��racak
	MOVE.B	(A0,D4.W),D3	*A[i]'yi D3 e atad�k
	MOVE.B	(A0,D5.W),D2	*A[largest]'� D2 e atad�k
	MOVE.B	D2,(A0,D4.W)	*D2 A[i] ye yaz�ld�
	MOVE.B	D3,(A0,D5.W)	*D3 A[largest] a yaz�ld�
	
	MOVE.L	D4, -(A7)	*Fonksiyona largest parametresi y���n �zerinden haz�rland�
	JSR	MxHp		*Fonksiyon kendini �a��rd�.
	MOVE.L	(A7)+, D4	*Y���nla yollanan parametre y���ndan geri �ekildi.

BITIR
	MOVEM.L	(A7)+, D2-D7/A0	*Fonksiyonun ba��nda y���na at�lan register'lar, fonksiyon bitiminde y���ndan geri �ekildi.
	
	RTS			*Altprogram�n sonu...



	ORG	$1000
START:				; first instruction of program
	
	MOVE.W 	size, D0	*Size'� rahat�a kullanabilmek i�in D0 data register'�na at�ld�.(D0 <- size)
	ASR	#1, D0		*D0 = D0/2 yap�ld�.
	
	MOVE.W	D0, D1		*D0'dan bir geride saymas� i�in bir sayac gerekliydi, bunun i�in de D1 register'� kullan�ld�.(D1 <- D0)
	
	SUBQ	#1, D1		*D1 D0'dan bir geride saymas� i�in D1 <- D1-1
	
GERI	
	MOVE.L	D0, -(SP)	*�ndis de�eri y���n �zerinden g�nderiliyor.
	JSR	MxHp		*Altprograma dallan�l�yor.
	SUBQ	#1, D0		*D0 elle bir azalt�l�yor.
	DBF	D1, GERI	*D1 '-1' den b�y�kse D1 <- D1-1 yap�l�p GERI etiketine dallan�l�yor.
	

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source




*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
