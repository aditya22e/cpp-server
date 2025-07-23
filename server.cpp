#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <bits/stdc++.h>
#include <string>
#include <winsock2.h>
using namespace std;
int main(){
    std::cout << "Chalo cpp me server banate hai!";

    SOCKET wsocket;
    SOCKET new_wsocket;
    WSADATA wsadata;
    struct sockaddr_in  server;
    int serverlen;
    int BUFFER_SIZE = 30720;

    //server khul ja
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) !=0){
        std::cout << "nhi khula";
    }
    //socket banan padega
    wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(wsocket == INVALID_SOCKET){
        std::cout <<"socket nhi bana";
    }

    //server ki jankari
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverlen = sizeof(servent);

    //server-socket milap
    if (bind(wsocket, (sockaddr *)&server, serverlen) !=0){
        std::cout <<"Tarik(date) cancel";
    }

    //address ki kahani uske jubani
    if (listen(wsocket, 20) !=0){
        std::cout <<"sunai nhi de rha \n";
    }

    std::cout<<"arey sab sunai de rha hai channel 127.0.0.1:8080 pe \n";

    int bytes = 0;
    while (true)
    {
        new_wsocket = accept(wsocket, (sockaddr*)&server, &serverlen);
        if (new_wsocket == INVALID_SOCKET){
            std::cout <<"ye koi or hai \n";
        }

        //suno kya keh rha hai
        char buff[30720] = {0};
        bytes = recv(new_wsocket, buff, BUFFER_SIZE, 0);
        if (bytes < 0){
            std::cout <<"samajh nhi a rha kya bol rha hai";
        }
        string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
        string response = "<html><h1>Lagta hai khud ka ye server ban gaya</h1></html>";
        serverMessage.append(to_string(response.size()));
        serverMessage.append("\n\n");
        serverMessage.append(response);

        int bytesSent = 0;
        int  totalBytesSent = 0;
        while (totalBytesSent < serverMessage.size()){
            bytesSent = send(new_wsocket, serverMessage.c_str(), serverMessage.size(), 0);
            if (bytesSent < 0) {
                std::cout <<"kuch uttar nhi de pa rha";
            }

            totalBytesSent += bytesSent;
        }
        std::cout <<"Uttar upbhogta tak pohoch gaya";

        closesocket(new_wsocket);
    }
    closesocket(wsocket);
    WSACleanup();
    

return 0;
}
