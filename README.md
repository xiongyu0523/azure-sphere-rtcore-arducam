# ArduCAM mini 2MP Plus SPI camera on RTCore

This sample demonstrates capturing a JPEG picture using [ArduCAM mini 2MP PLUS]() SPI camera on Azure Sphere RTCore using [Codethink MT3260 driver](https://github.com/CodethinkLabs/mt3620-m4-drivers). 


## To build and run the sample

### Prep your device

1. Ensure that your Azure Sphere device is connected to your PC, and your PC is connected to the internet.
2. Even if you've performed this set up previously, ensure that you have Azure Sphere SDK version 19.11 or above. In an Azure Sphere Developer Command Prompt, run **azsphere show-version** to check. Download and install the [latest SDK](https://aka.ms/AzureSphereSDKDownload) as needed.

3. Right-click the Azure Sphere Developer Command Prompt shortcut and select **More > Run as administrator**.
4. At the command prompt issue the following command:

   ```
   azsphere dev edv --enablertcoredebugging
   ```

   This command must be run as administrator when you enable real-time core debugging because it installs USB drivers for the debugger.
5. Close the window after the command completes because administrator privilege is no longer required. 

3. The demo is tested on RDB, connect SPI to ISU1 on Header 4 and I2C to ISU0 on Header 2. Detailed connections are:
   
    |  ArduCAM mini 2MP Plus | RDB  | MT3620 |
    |  ----  | ----  | ---- | 
    | SCL  | H2-7 | GPIO27_MOSI0_RTS0_CLK0 |
    | SDA  | H2-1 | GPIO28_MISO0_RXD0_DATA0 | 
    | VCC  | H3-3 | 3V3 |
    | GND  | H3-2 | GND |
    | SCK  | H4-7 | GPIO31_SCLK1_TXD1 |
    | MISO  | H4-5 | GPIO33_MISO1_RXD1_DATA1 |
    | MOSI  | H4-11 | GPIO32_MOSI1_RTS1_CLK1 |
    | CS  | H1-10 | GPIO3 |
  
### Build and deploy the application

1. Start Visual Studio.
2. From the **File** menu, select **Open > CMake...** and navigate to the folder that contains the sample.
3. Select the file CMakeLists.txt and then click **Open**. 
4. In Solution Explorer, right-click the CMakeLists.txt file, and select **Generate Cache for azure-sphere-rtcore-arducam**. This step performs the cmake build process to generate the native ninja build files. 
5. In Solution Explorer, right-click the *CMakeLists.txt* file, and select **Build** to build the project and generate .imagepackage target.
6. Double click *CMakeLists.txt* file and press F5 to start the application with debugging. 
7. The code will stop at the end of main() and ImageBuffer[] contains the JPEG data.