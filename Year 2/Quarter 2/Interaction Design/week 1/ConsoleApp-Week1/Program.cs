using System;
using System.IO.Ports;

class Program {
    const int BAUDRATE = 115200;
    private SerialPort _serialPort;
    private int _lastValue = -1;
    private int _minValue = int.MaxValue;
    private int _maxValue = int.MinValue;

    static void Main(string[] args) {
        var program = new Program();

        Console.WriteLine("Available Serial Ports:");
        var portNames = program.PortNames; //get list of port names
        foreach (var port in portNames) {
            Console.WriteLine(port);
        } 
        if (portNames.Length > 0) {
            var latestPort = portNames[portNames.Length - 1]; //get last port cuz new usb from pico usually be the last port
            Console.WriteLine($"Opening port \"{latestPort}\"");

            try
            {
                program.OpenConnection(latestPort, BAUDRATE);

                program.PrintHelp();

                bool stop = false;
                while (!stop) {
                    stop = !program.Run();

                    if (!stop && Console.KeyAvailable) {
                        ConsoleKeyInfo keyInfo = Console.ReadKey(true);
                        char key = keyInfo.KeyChar;

                        if (key == 'o') {
                            program.Send("LedOn");
                        } else if (key == 'f') {
                            program.Send("LedOff");
                        } else if (key == 'h') {
                            program.PrintHelp();
                        } else if (key == 'q' || key == 'Q') {
                            stop = true;
                        }

                        if (keyInfo.Key == ConsoleKey.Escape)
                            stop = true;
                    }
                }
            }
            catch (Exception ex) {
                Console.WriteLine($"Exception: {ex.Message}");
            }
        }
        else 
            Console.WriteLine("No serial ports found.");
        
    }

    Program(){
        _serialPort = new SerialPort();
    }

    ~Program(){
        CloseConnection();
    }

    public string[] PortNames{
        get { return SerialPort.GetPortNames(); } // Get list of port names
    }

    public void OpenConnection(string portName, int baudRate){
        CloseConnection();// Close it, in case it was open.

        _serialPort.PortName = portName;
        _serialPort.BaudRate = baudRate;
        _serialPort.DtrEnable = true;  // Data Terminal Ready
        _serialPort.RtsEnable = true;// Request to Send

        _serialPort.Open();

        if (_serialPort.BytesToRead > 0){
            // Clear the buffer to prevent reading old data.
            _serialPort.DiscardInBuffer();
        }
    }

    public void CloseConnection(){
        if (_serialPort != null && _serialPort.IsOpen)
            _serialPort.Close();
    }

    public bool Run(){
        if (_serialPort.BytesToRead > 0){
            // Data is available to read
            string message = _serialPort.ReadLine().Trim();// Remove any trailing newline or whitespace

            int value;
            if (int.TryParse(message, out value)){ // string -> int
                if (value != _lastValue){
                    _lastValue = value;

                    if (value < _minValue) _minValue = value;
                    if (value > _maxValue) _maxValue = value;

                    Console.WriteLine($"Data = {value}, Min = {_minValue}, Max = {_maxValue}");
                }
            } else {
                // Just print the text, do NOT stop the program
                Console.WriteLine(message);
            }
        }
        return true;
    }

    public void Send(string text){
        if (_serialPort.IsOpen)
            _serialPort.WriteLine(text);
    }

    public void PrintHelp(){
        Console.WriteLine("Commands:");
        Console.WriteLine("  o = LED on");
        Console.WriteLine("  f = LED off");
        Console.WriteLine("  h = help");
        Console.WriteLine("  q, Q, ESC = quit");
    }
}
