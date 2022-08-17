using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace chatServer
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("I am Chat Server and listening to 5 clients");
            Socket s = new Socket(AddressFamily.InterNetwork, 
                                   SocketType.Stream, ProtocolType.Tcp);
            IPEndPoint server = new IPEndPoint(IPAddress.Parse("10.50.2.222"), 4444);
            s.Bind(server);
            s.Listen(5);

            for (int i = 0; i < 5; i++)
            {
                Socket c = s.Accept();
                //Receive Message
                byte[] msg_recv = new byte[250];
                int cr = c.Receive(msg_recv);
                string msg = Encoding.ASCII.GetString(msg_recv, 0, cr);
                Console.WriteLine("Message Received from : " + 
                               c.RemoteEndPoint.ToString() + " = " + msg);
                //Send Message
                msg = "Hello I am chatServer : and you are " + c.RemoteEndPoint.ToString();
                byte[] msg_sent = Encoding.ASCII.GetBytes(msg);
                c.Send(msg_sent, 0);
                
                c.Close();
            }
        }
    }
}
