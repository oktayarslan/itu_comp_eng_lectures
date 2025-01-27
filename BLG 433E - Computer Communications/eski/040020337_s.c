/* Beycan Kahraman - 040020337 - beycan@mail.com                   */
/*                               Bilgisayar Haberlesmesi - Odev II */
/*     server.c - code for example server program that uses TCP    */
#ifndef unix
   #define WIN32
   #include <windows.h>
   #include <winsock.h> 
   #include <io.h>
#else
   #define closesocket close
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <netdb.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROTOPORT       1453            /* default protocol port number */
#define QLEN            6               /* size of request queue        */
#define DOSYA           "alinan_bit_dizisi.txt"

int     visits      =   0;              /* counts client connections    */
/*------------------------------------------------------------------------
 * Program:   server
 *
 * Purpose:   allocate a socket and then repeatedly execute the following:
 *              (1) wait for the next connection from a client
 *              (2) send a short message to the client
 *              (3) close the connection
 *              (4) go back to step (1)
 *
 * Syntax:    server [ port ]
 *
 *               port  - protocol port number to use
 *
 * Note:      The port argument is optional.  If no port is specified,
 *            the server uses the default given by PROTOPORT.
 *
 *------------------------------------------------------------------------
 */
main(int argc, char *argv[]) {
        struct  hostent  *ptrh;  /* pointer to a host table entry       */
        struct  protoent *ptrp;  /* pointer to a protocol table entry   */
        struct  sockaddr_in sad; /* structure to hold server's address  */
        struct  sockaddr_in cad; /* structure to hold client's address  */
        int     sd, sd2;         /* socket descriptors                  */
        int     port;            /* protocol port number                */
        int     alen;            /* length of address                   */
        char    buf[1000];       /* buffer for string the server sends  */

        FILE    *f;               /* file to write DOSYA           */
        int     n;                /* received bits                 */
        int     fileEnd = 1;      /* transport end ?               */
        int     totalOnes;        /* to calculate eslik bit        */
        int     i;                /* loops                         */

#ifdef WIN32
        WSADATA wsaData;
        WSAStartup(0x0101, &wsaData);
#endif
        memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure */
        sad.sin_family = AF_INET;         /* set family to Internet     */
        sad.sin_addr.s_addr = INADDR_ANY; /* set the local IP address   */

        /* Check command-line argument for protocol port and extract    */
        /* port number if one is specified.  Otherwise, use the default */
        /* port value given by constant PROTOPORT                       */

        if (argc > 1) {                 /* if argument specified        */
                port = atoi(argv[1]);   /* convert argument to binary   */
        } else {
                port = PROTOPORT;       /* use default port number      */
        }
        if (port > 0)                   /* test for illegal value       */
                sad.sin_port = htons((u_short)port);
        else {                          /* print error message and exit */
                fprintf(stderr,"bad port number %s\n",argv[1]);
                exit(1);
        }

        /* Map TCP transport protocol name to protocol number */

        if ( ((int)(ptrp = getprotobyname("tcp"))) == 0) {
                fprintf(stderr, "cannot map \"tcp\" to protocol number");
                exit(1);
        }

        /* Create a socket */

        sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
        if (sd < 0) {
                fprintf(stderr, "socket creation failed\n");
                exit(1);
        }

        /* Bind a local address to the socket */

        if (bind(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
                fprintf(stderr,"bind failed\n");
                exit(1);
        }

        /* Specify size of request queue */

        if (listen(sd, QLEN) < 0) {
                fprintf(stderr,"listen failed\n");
                exit(1);
        }

        /* Main server loop - accept and handle requests */

        alen = sizeof(cad);
        if ( (sd2=accept(sd, (struct sockaddr *)&cad, &alen)) < 0) {
                fprintf(stderr, "accept failed\n");
                exit(1);
        }


        /*********************** ADDED *******************************/

        f = fopen(DOSYA,"w");                              // open file

        while(fileEnd)
        {
                n = recv(sd2, buf, 8, 0);                  // get bits

                if(n < 8)
                        fileEnd = 0;                       // is file end?

                buf[n] = '\0';
                totalOnes = 0;

                for(i=0; i<n; ++i)
                        if(buf[i] == '1')
                                ++totalOnes;               // calculate eslik bit

                if(totalOnes%2)
                {
                        printf("x");		               // ERROR
                        send(sd2, "1001", 4, 0);           // NACK
                }
                else
                {
                        if(n > 0)
                                buf[n-1] = '\0';           // NO ERROR - write to file
                        fprintf(f, "%s", buf);
						printf("o");		               // NO ERROR
                        send(sd2, "0110", 4, 0);           // ACK
                }
        }

        fclose(f);                                         // close file

        /************************ END ********************************/

        closesocket(sd2);
}
