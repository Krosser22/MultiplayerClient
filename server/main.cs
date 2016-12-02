/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

using System;
using System.Data.SQLite;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

// State object for reading client data asynchronously
public class StateObject {
  // Client  socket.
  public Socket workSocket = null;

  // Size of receive buffer.
  public const int BufferSize = 1024;

  // Receive buffer.
  public byte[] buffer = new byte[BufferSize];

  // Received data string.
  public StringBuilder sb = new StringBuilder();
}

public class AsynchronousSocketListener {
  // Thread signal.
  public static ManualResetEvent allDone = new ManualResetEvent(false);
  
  public static void StartSQLite() {
    // Holds our connection with the database
    SQLiteConnection dbConnection;

    // Creates an empty database file
    SQLiteConnection.CreateFile("DB.sqlite");

    // Creates a connection with our database file.
    dbConnection = new SQLiteConnection("Data Source=DB.sqlite;Version=3;");
    dbConnection.Open();
    
    // Creates a table
    string sql = "create table Users (Nick varchar(20), Password varchar(20))";
    SQLiteCommand command = new SQLiteCommand(sql, dbConnection);
    command.ExecuteNonQuery();

    // Inserts some values in the highscores table.
    // As you can see, there is quite some duplicate code here, we'll solve this in part two.
    sql = "insert into Users (Nick, Password) values ('Admin', 'Password')";
    command = new SQLiteCommand(sql, dbConnection);
    command.ExecuteNonQuery();
    sql = "insert into Users (Nick, Password) values ('Krosser22', 'MIAU')";
    command = new SQLiteCommand(sql, dbConnection);
    command.ExecuteNonQuery();
    sql = "insert into Users (Nick, Password) values ('Charmander', 'RAWR')";
    command = new SQLiteCommand(sql, dbConnection);
    command.ExecuteNonQuery();

    // Writes the highscores to the console sorted on score in descending order.
    sql = "select * from Users order by Nick asc";
    command = new SQLiteCommand(sql, dbConnection);
    SQLiteDataReader reader = command.ExecuteReader();
    while (reader.Read()) {
      Console.WriteLine("Nick: " + reader["Nick"] + "\nPassword: " + reader["Password"] + "\n");
    }
    Console.ReadLine();
  }

  public static void StartListening() {
    // Data buffer for incoming data.
    byte[] bytes = new Byte[StateObject.BufferSize];

    // Establish the local endpoint for the socket.
    // The DNS name of the computer
    // running the listener is "host.contoso.com".
    IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
    IPAddress ipAddress = ipHostInfo.AddressList[0];
    ipAddress = IPAddress.Parse("127.0.0.1");
    IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 8080);
    Console.WriteLine("http://{0}:8080", ipAddress);

    // Create a TCP/IP socket.
    Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

    // Bind the socket to the local endpoint and listen for incoming connections.
    try {
      listener.Bind(localEndPoint);
      listener.Listen(100);

      while (true) {
        // Set the event to nonsignaled state.
        allDone.Reset();

        // Start an asynchronous socket to listen for connections.
        Console.WriteLine("Waiting for a connection...");
        listener.BeginAccept(new AsyncCallback(AcceptCallback), listener);

        // Wait until a connection is made before continuing.
        allDone.WaitOne();
      }
    } catch (Exception e) {
      Console.WriteLine(e.ToString());
    }

    Console.WriteLine("\nPress ENTER to continue...");
    Console.Read();
  }

  public static void AcceptCallback(IAsyncResult ar) {
    // Signal the main thread to continue.
    allDone.Set();

    // Get the socket that handles the client request.
    Socket listener = (Socket)ar.AsyncState;
    Socket handler = listener.EndAccept(ar);

    // Create the state object.
    StateObject state = new StateObject();
    state.workSocket = handler;
    handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);
  }

  public static void ReadCallback(IAsyncResult ar) {
    String content = String.Empty;

    // Retrieve the state object and the handler socket
    // from the asynchronous state object.
    StateObject state = (StateObject)ar.AsyncState;
    Socket handler = state.workSocket;

    // Read data from the client socket. 
    int bytesRead = handler.EndReceive(ar);
    if (bytesRead > 0) {
      // There  might be more data, so store the data received so far.
      state.sb.Clear();
      state.sb.Append(Encoding.ASCII.GetString(state.buffer, 4, bytesRead));

      // Check for end-of-file tag. If it is not there, read 
      // more data.
      content = state.sb.ToString().Substring(0, state.sb.ToString().IndexOf('\0'));
      Console.WriteLine("{0}", content.ToString());
      //if (content.IndexOf("<EOF>") > -1) {
      // All the data has been read from the 
      // client. Display it on the console.
      //Console.WriteLine("Read {0} bytes from socket.\n Data : {1}", content.Length, content);
      Console.WriteLine("{0}\n", content);

      // Echo the data back to the client.
      //Send(handler, content);
      //} else {
      // Not all data received. Get more.
      handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);
      //}
    } else {
      Console.WriteLine("HHHH");
    }
  }

  private static void Send(Socket handler, String data) {
    // Convert the string data to byte data using ASCII encoding.
    byte[] byteData = Encoding.ASCII.GetBytes(data);

    // Begin sending the data to the remote device.
    handler.BeginSend(byteData, 0, byteData.Length, 0, new AsyncCallback(SendCallback), handler);
  }

  private static void SendCallback(IAsyncResult ar) {
    try {
      // Retrieve the socket from the state object.
      Socket handler = (Socket)ar.AsyncState;

      // Complete sending the data to the remote device.
      int bytesSent = handler.EndSend(ar);
      Console.WriteLine("Sent {0} bytes to client.", bytesSent);
      
      //handler.Shutdown(SocketShutdown.Both);
      //handler.Close();
    } catch (Exception e) {
      Console.WriteLine(e.ToString());
    }
  }
  
  public static int Main(String[] args) {
    StartSQLite();
    StartListening();
    return 0;
  }
}