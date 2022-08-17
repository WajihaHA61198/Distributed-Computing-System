using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace chatClient
{
    class Program
    {

        static void Main(string[] args)
        {
            Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            s.Connect(IPAddress.Parse("10.50.2.222"),4444);

            Random rn = new Random();
            string msg = "Hello I am chatClient " + rn.Next(100).ToString();
            byte[] msg_sent = Encoding.ASCII.GetBytes(msg);
            s.Send(msg_sent, 0);

            //now receive in the same buffer
            byte[] msg_recv = new byte[250];
            int cr = s.Receive(msg_recv);
            msg = Encoding.ASCII.GetString(msg_recv, 0, cr);
            Console.Write(msg);
        }
    }
}
