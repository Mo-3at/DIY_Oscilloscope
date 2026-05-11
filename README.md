# DIY_Oscilloscope

This project is a simple DIY_Oscilloscope for students who want to learn using it but cant afford one 

* HARDWARE 


<img width="1307" height="592" alt="Osilloscope_schematic" src="https://github.com/user-attachments/assets/98641d0d-c606-4084-856c-8f1cfb1cbb10" />




The schematic is divided into four sections:

1- The MCU: I selected the ESP-32 due to its affordability and processing power compared to other MCUs in this price range 
the ESP-32 will allow us to reach frequencies up to 100KHz. (I USED THE ESP-32 38 PIN NOT THE S2 AS IN THE SCHEMATIC)

2- The Front-ends: We have two front ends for providing a two channel input, each front end is responsibble for loweing the input voltage to a safe value for the ESP-32 
this is done using the voltage divider (you can have the voltage divider at whatever ration you want I chose to have this ratio and calibrate it to a max reading of 12Vac), 
the next feature the front end circuit provides is the coupling capacitor designed to block the sensing of dc signals or allowing them to pass.

3- The Clamping Circuit: This circuit is responsibble for raising the zero voltage to a value of 1.65V to make it safe for the esp to measure AC,
the op-amp is used to prevent higher voltages from passing to the clamper line (A 100Kohm RESISTOR MUST BE USED BETWEEN THE CLAMPER AND THE INPUT LINE) (USE TWO DIFFERENT CLAMPERS TO AVOID SIGNALS MIXING)

4- Low Pass Filters: We use simple low pass filter to filter the excess noise out 


* SOFTWARE

The code provides many features I will just mention the most important ones:

1- The code provides a digital filter which filters the noise and makes the plot appear smoother 

the filterAlpha variable controls how strong the filter is if the signal is to laggy raise it if it is too noisy lower it 

2- The code uses a buffer to store a set of data to proccess and then passes them to the plotter 

3- A mathematical eqation has been appleid to restore the original voltage (The math here was built according to the voltage divider values i used) 

* PLOTTER

I used Serial Studio for the plotting u coul learn how to use it or just use the plotter file i provided download serial studio and open the provided (plot) file 

