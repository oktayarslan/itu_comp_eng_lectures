*
*-----------------------------------------------------------------
* Program    : Prime Number Testing
* Written By : Ar. G�r. G. Selda KURUOGLU (kuruoglug@itu.edu.tr)
*              Ar. G�r. Deniz DEM�RAY     (demirayde@itu.edu.tr)
* Date       : 18.02.2010
* Description: Bilgisayar Mimarisi 2009-2010 ODEV - I:
*-----------------------------------------------------------------

;Veriler:
		
; K�s�m 2 icin:

 ORG $0502
sayiDizisiKaynak	DC.W	87,92,7,84,65,32,11,83,103,287
N 			DC.W 	10

 ORG $0602 
sayiDizisiHedef		DS.W	N
		

					
							
; ANA PROGRAM
	ORG	$1000
	
start		MOVEA.L	    #$4000,SP			; Yigin $4000 adresinden baslatilmistir
		
		; KISIM 2 : sayiDizisiKaynak'ta yer alan asal say�lar sayiDizisiHedef adresinden ba�lanarak kopyalanmali
                ; sayiDizisiHedef adresinde ILK ELEMAN: kaynak dizisinde ka� adet asal say� oldugunu belirtmeli 

;-----------------------------------------------KODUNUZU BU ALANA YAZINIZ -------------------------------------------------


;--------------------------------------------------------------------------------------------------------------------------
   						
  
		MOVEA.L     #$4000,SP			; yiginin bosaltilmasi
		
		
;------------------------------------- asalmi ALTPROGRAMI: KODUNUZU BU ALANA KOPYALAYINIZ ---------------------------------


; -------------------------------------------------------------------------------------------------------------------------

		END	START					; last line of source









*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
