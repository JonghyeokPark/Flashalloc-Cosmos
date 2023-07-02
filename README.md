# FlashAlloc: Dedicating Flash Blocks By Objects

**FlashAlloc** is a novel interfacee for flash storage,
which is used to the logical address ranges of objects to the underlying flash device 
and thus to enlighten the device to stream writes by objects. See deatil in our paper

[1] Jonghyeok Park, Soyee Choi, Gihwan Oh, Soojum Im, Moon-Wook Oh, Sang-Won Lee, "FlashAlloc: Dedicating Flash Blocks By Objects". VLDB 2023


## Prerequisite

First, you will need the Cosmos+ Board with hynix NAND firmware version. 
You can get more accurate information at [CRZ Technology](https://www.crz-tech.com/)   

![Cosmos+Board](https://www.crz-tech.com/uploads/uploads/2021/01/29/fnn45201781714615.jpg)

```
FPGA: Xilinx XC7Z045-3FFG900 Zynq-7000
- Dual ARM Cortex-A9 1GHz Core
- NEON DSP co-processor for each core
- 350K LCs

1GB DDR3 NAND Modules
1 SD CARD Slot
Dual PCIe Gen2 x8 End-Points (Cabled PCIe Interface)
1 Gigabit Ethernet Interface
1 USB 2.0 (configurable to Host or Device)
JTAG and Debug Interface         
```

Second, You need the software tools and files
- Xilinx ISE design suite 19.1 system edition [Link](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools/archive.html)
- UART terminal emulator software (Xilinx Software Development Kit(SDK) includes UART terminal)
- Download the [USB-to-UART driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
- Check details at [OpenSSD Project hompage](http://www.openssd-project.org/)

## Project Structure
- `Flashalloc` is Cosmos+ OpenSSD firmware source code which implements the Flashalloc interface for flash storages
- `Multistream` is multi-stream prototype for Cosmos+ OpenSSD supporting eight stream-ids
-  More details are illustrated in our paper.

## Build

Please refer to Cosmos+ OpenSSD build guide [document](/doc/Cosmos+ OpenSSD 2017 Tutorial.pdf)

TL;DR
1. Prepare Cosmos+ Open SSD, Window and Linux PC
2. Connect the  Cosmos+ OpenSSD to Window PC (JTAG dilegent module and USB cable for UART) and install the PCIe to connect btw Cosmos+ OpenSSD and Linux PC
3. Open the FlashAlloc projecct in Xilinx SDK
4. Right click on project, and `Run As > 1. Launch on Hardware (GDB)`
5. Click the firmware to execute, and `click OK > wait UART message`
6. Press X to make bad block table (you should do this for the first time)
7. Wait and Turn-on (or reboot) the Linux PC
8. You can check the Cosmos+ OpenSSD using `nvme-cli` or `lspci` command (check the `nvme0nXXXXX` in the device list)
9. Bon appétit! :)

## Refercnes
All guide document for Cosmos+ OpenSSD is provided by [Cosmos Open SSD Project](https://github.com/Cosmos-OpenSSD/Cosmos-OpenSSD/tree/master).
