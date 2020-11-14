# P2P-Image-Sharing
A Distributed Application that uses P2P Archeticture for the Purpose of Image Sharing.<br/><br/>
It implements a centralized service through which new users can register and current users can update their status, and connect to other peers.<br/><br/>
It relies on RPC for sending and receving messages between different peers, and between peers and the centralized service.<br/><br/>
It uses steganography techniques for specifying the number of views that each peer can give to the other.<br/><br/>
All processes are done using multithreading to boost the performance.<br/><br/>
The application makes use of the fast performance of UDP packets, and adds fault tolerance and reliability enhancements to make reliable connections.<br/><br/>
**For more Information on the implementation specifications, please refer to the Documentation file included inside the repo.**
