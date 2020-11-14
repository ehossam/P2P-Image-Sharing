# P2P-Image-Sharing
A distributed Application that uses P2P archeticture for the Purpose of Image sharing<br/><br/>
It implements a centralized service through which new users register and current users update their status, and connect to other peers.<br/><br/>
It relies on RPC for sending an receving messages between different peers and between peers and the centralized service.<br/><br/>
It uses steganography techniques for specifying the number of views that each user can give to the other.<br/><br/>
All processes are done using multithreading to boost the performance.<br/><br/>
The application makes use of the fast performance of UDP packets, and adds fault tolerance and reliability enhancements to make reliable connections.<br/><br/>
**For more Information on the implementation specifications, please refer to the Documentation file included inside the repo.**
