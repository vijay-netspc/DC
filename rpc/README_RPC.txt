RPC Addition Program - README

Overview

This project demonstrates a simple RPC (Remote Procedure Call) program
using ONC RPC in C. It performs addition of two integers on the server
side and returns the result to the client.

------------------------------------------------------------------------

Files Included

-   add.x -> RPC interface definition
-   addserver.c -> Server-side implementation
-   addclient.c -> Client-side program

------------------------------------------------------------------------

Step-by-Step Instructions

1. Generate RPC files

Run: rpcgen add.x

This generates: - add.h - add_clnt.c - add_svc.c - add_xdr.c

------------------------------------------------------------------------

2. Compile the Server

Run: gcc addserver.c add_svc.c add_xdr.c -o server

------------------------------------------------------------------------

3. Compile the Client

Run: gcc addclient.c add_clnt.c add_xdr.c -o client

------------------------------------------------------------------------

4. Run the Server

In terminal 1: ./server

------------------------------------------------------------------------

5. Run the Client

In terminal 2: ./client localhost

------------------------------------------------------------------------

Expected Output

Sum = 30

------------------------------------------------------------------------

Notes

-   Ensure rpcbind (or portmap) service is running: sudo systemctl start
    rpcbind

-   Use ‘localhost’ if running on the same machine.

-   Make sure firewall does not block RPC communication.

------------------------------------------------------------------------

Author

RPC Example for academic use.
