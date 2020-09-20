	ORG $0
DIZI:
	DCINT	3
	DCINT	66
	DCINT	-2
	DCINT	75
	DCINT	125

;DS S�zde komutu kullan�m �rne�i (10 sekizli yer ay�r�r)
DIZI1	DS 10

;Bu altprogram R31 ve R30 saklay�c�lar�nda ald��� tamsay�lar� �arparak
;sonucu 64 bitlik bir de�er olarak R29(Y�ksek anlaml�) ve R28 saklay�c�lar�nda 
;d�nd�r�r. D�n�� adresinin R27 saklay�c�s�nda verilmesi gerekir
;Russian gibi daha verimli bir algoritma kullan�labilirdi ama benzetim a��s�ndan 
;daha uzun i�lem gerektiren ard���l toplama tercih edildi

CARPIM:	ADD R0,R0,R28	;R28 ve R29 u s�f�rla
	ADD R30,R0,R25	;�arpan say�y� R25 e al (R30 u de�i�tirmiyoruz)
	JMPR BMI,NEGATIF
	ADD R0,0,R24	;Negatif �arpan i�in bayrak
	ADD R0,R0,R29
GERI:	JMPR BEQ,BITTI	
DEVAM:	ADD R31,R28,R28
	ADDC R0,R29,R29
	JMPR BR,GERI
	NOP
	SUB R25,1,R25
BITTI:	ADD R0,R24,R24
	JMPR BEQ,PZTF
	SUB R28,R31,R28
	SUBC R29,R0,R29		;Sonraki NOP veri ba��ml�l���n� ��zmek i�in
	NOP			
	SUBR R28,0,R28
	SUBCR R29,0,R29 
PZTF:	RET (R27)0
	NOP
	NOP

NEGATIF: JMPR BR,DEVAM
	SUB R0,R25,R25
	ADD R0,1,R24	

;Bu altprogram R31 saklay�c�s�nda ba�lang�� adresini ve R30 saklay�c�s�nda eleman say�s�n� ald��� 
;tamsay� dizisinin en b�y�k eleman�n� bularak R29 saklay�c�s�nda geri d�nd�r�r. D�n�� adresi 
;R28 saklay�c�s�nan okunur. R30 saklay�c�s�nda gelen parametrenin 0 dan b�y�k oldu�u varsay�lm��t�r

MAX:	ADD R0,4,R23		;Her eleman�m�z 4 sekizli boyutunda
	ADD R0,1,R25		;Saya� olarak kullan�lacak saklay�c�ya 1 yazd�k 
	LDL (R31)0,R29		;En b�y�k eleman dizinin ilk eleman�
DONGU1:	LDL (R31)R23,R24	;Dizinin s�radaki eleman� R24 de
	SUB R30,R25,R0		;Sonucu bir yere yazm�yoruz, R0 donan�msal olarak s�f�rda
	JMPR BEQ,SON
	ADD R23,4,R23		;Bir sonraki eleman adresi i�in
	SUB R29,R24,R0		;Kar��la�t�rma i�in... sonucu bir yere yazm�yoruz
	JMPR BGE,DONGU1
	ADD R25,1,R25		;Sayac� bir art�r, dallanma ger�ekle�se de ger�ekle�mese de yap�lacak
	NOP
	JMP BR,DONGU1(R0)
	ADD R0,R24,R29		;Daha b�y�k olan eleman� R29 a al
	NOP
SON:	RET (R28)0
	NOP
	NOP
	

;Bu altprogram R31 saklay�c�s�nda ba�lang�� adresini ve R30 saklay�c�s�nda eleman say�s�n� ald��� 
;tamsay� dizisinin en k���k eleman�n� bularak R29 saklay�c�s�nda geri d�nd�r�r. D�n�� adresi 
;R28 saklay�c�s�nan okunur. R30 saklay�c�s�nda gelen parametrenin 0 dan b�y�k oldu�u varsay�lm��t�r

MIN:	ADD R0,4,R23		;Her eleman�m�z 4 sekizli boyutunda
	ADD R0,1,R25		;Saya� olarak kullan�lacak saklay�c�ya 1 yazd�k 
	LDL (R31)0,R29		;En k���k eleman dizinin ilk eleman�
DONGU2:	LDL (R31)R23,R24	;Dizinin s�radaki eleman� R24 de
	SUB R30,R25,R0		;Sonucu bir yere yazm�yoruz, R0 donan�msal olarak s�f�rda
	JMPR BEQ,SON1
	ADD R23,4,R23		;Bir sonraki eleman adresi i�in
	SUB R29,R24,R0		;Kar��la�t�rma i�in... sonucu bir yere yazm�yoruz
	JMPR BLE,DONGU2
	ADD R25,1,R25		;Sayac� bir art�r, dallanma ger�ekle�se de ger�ekle�mese de yap�lacak
	NOP
	JMP BR,DONGU2(R0)
	ADD R0,R24,R29		;Daha k���k olan eleman� R29 a al
	NOP
SON1:	RET (R28)0
	NOP
	NOP

;Ana program, bir tamsay�(32 bitlik) dizisinin en b�y�k ve en k���k elemanlar�n� bularak �arp�mlar�n� (64 bit)
;hesaplay�p sonucu bellekte $200(y�ksek anlaml�) ve $201 adresli g�zlere yazar
;(�rnek, Prof.Dr. E�ref Adal� ve Yrd.Do�.Dr.�ule G�nd�z ���d�c� 2005 y�l� Mikroi�lemci Sistemleri y�li�i s�nav sorusudur)

START:	ADD R0,START,R13	;Sadece saklay�c� dosyas� de�i�imini g�rmek i�in yap�lan bir y�kleme
	SLL R13,3,R30		;Veri ba��ml�l��� olu�turmak i�in eklendi
	ADD R0,$66,R8		;Sadece saklay�c� dosyas� de�i�imini g�rmek i�in yap�lan bir y�kleme
	ADD R0,-20,R18		;Sadece saklay�c� dosyas� de�i�imini g�rmek i�in yap�lan bir y�kleme	
	SUB& R0,R0,R19		;Etkilenmeyen durum k�t��� bayraklar�n� g�stermek i�in eklendi

	CALLR MAX,R12		;D�n�� adresi �a�r�lan altprogram�n R28 saklay�c�s�nda (bu pencerede R12)
	ADD R0,DIZI,R31		;Dikkat !!! Okunan ve yaz�lan saklay�c�lar farkl� pencerelerde
	ADD R0,5,R30
	ADD R0,R13,R5		;MAX altprogram�ndan R28=R13 saklay�c�s�nda d�nen de�er yerel saklay�c�ya al�nd�
	CALL MIN(R0),R12	;Altprogram parametreleri zaten ilgili saklay�c�larda y�kl� NOP		
	NOP
	NOP
	ADD R0,R13,R14		;Altprogram�n R31 saklay�c�s�na MAX,  R30 saklay�c�s�na MIN altprogramlar�ndan gelen de�erler yaz�l�yor
	CALL CARPIM(R0),R11
	ADD R0,R5,R31		;Dikkat !!! Okunan ve yaz�lan saklay�c�lar farkl� pencerelerde
	NOP
	STL (R0)$200,R13
	STL (R0)$204,R12
	

	
	
