using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;

namespace CAL_WeatherMonitoringSystem_FINALPROJ
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort;

        public Form1()
        {
            InitializeComponent();
            timer1.Interval = 1000;
            timer1.Start();
            timer2.Tick += Timer_Tick;

            serialPort = new SerialPort("COM7", 9600);

            try
            {
                serialPort.Open();
            }
            catch
            {
                Console.WriteLine("Unable to open COM");
            }
            DisplayDateWithoutYear();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            // Update the label text with the current time
            clock.Text = DateTime.Now.ToString("hh:mm:ss tt"); // Format the time as desired
        }
        private void DisplayDateWithoutYear()
        {
            // Get the current date or any specific date
            DateTime currentDate = DateTime.Now;

            // Format the date without the year
            string formattedDate = currentDate.ToString("MMM dd");

            // Display the formatted date in a label
            date.Text = formattedDate;
        }


        private void DisplayTemperature(string temperature)
        {
            TempTB.Text = temperature + " °C";
        }

        private void DisplayHumidity(string humidity)
        {
            HumidityTB.Text = humidity + "%";
        }

        private void DisplayPressure(string pressure)
        {
            BrightnessTB.Text = pressure + "";
        }

        private void DisplayMotor(string motor)
        {
            motorstatTB.Text = motor + "";
        }

        private void ClearTextBoxes()
        {
            TempTB.Clear();
            HumidityTB.Clear();
            BrightnessTB.Clear();
            motorstatTB.Clear();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            string humidity = string.Empty;
            string temperature = string.Empty;
            string light = string.Empty;
            string motor = string.Empty;

            while (serialPort.BytesToRead > 0)
            {
                string data = serialPort.ReadLine();

                // Assuming the data is sent in the format: temperature humidity pressure
                string[] values = data.Split(' ');

                if (values.Length >= 4)
                {
                    humidity = values[0];
                    temperature = values[1];
                    light = values[2];
                    motor = values[3];
                }
            }

            if (!string.IsNullOrEmpty(temperature) && !string.IsNullOrEmpty(humidity) && !string.IsNullOrEmpty(light) && !string.IsNullOrEmpty(motor))
            {
                ClearTextBoxes();
                DisplayTemperature(temperature);
                DisplayHumidity(humidity);
                DisplayPressure(light);
                DisplayMotor(motor);
            }
        }

        // Remember to close the serial port when your application closes
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.Close();
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}