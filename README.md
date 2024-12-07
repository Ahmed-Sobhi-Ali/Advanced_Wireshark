# Advanced Wireshark - Linux Kernel Module for Packet Sniffing

This repository contains an advanced **Linux Kernel Module (LKM)** designed for packet sniffing. Unlike traditional packet sniffing tools, this module operates at the kernel level, allowing it to intercept network traffic directly. It captures the source and destination IP addresses of IP packets in real-time and logs them for analysis.

## Requirements

To use this module, you need the following:

- **Linux Kernel 6.x or higher** – Ensure that you are using a kernel that supports the necessary features for loading and working with kernel modules.
- **Basic understanding of kernel programming and networking** – Familiarity with how the Linux kernel interacts with network traffic will be helpful.
- **Root privileges** – You need superuser access to load and manage kernel modules on your system.

## Setup Instructions

Follow the steps below to clone the repository, build, load, and test the kernel module:

### 1. Clone the repository:
   First, clone the repository to your local machine

### 2. Build the module:

To compile the kernel module, run the `make` command in the repository directory. This will compile the source code into a loadable kernel object (`.ko` file):

```bash
make
```

### 3. Load the kernel module:

After compiling the module, you can load it into the Linux kernel using the `insmod` command:

```bash
sudo insmod kernel_module.ko
```

### 4. Verify that the module is loaded:

To check if the module has been successfully loaded, use the `dmesg` command to view the kernel log messages:

```bash
dmesg | grep "Packet Sniffer module"
```

This should confirm that the module is active.

### 5. Check captured packets:

After loading the module, you will begin seeing logs that indicate the source and destination IP addresses for the captured packets. You can view these logs using the following command:

```bash
dmesg | grep "Packet captured"
```

You can also check the logs in `/var/log/kern.log` or other log files depending on your system's configuration.

### 6. Unload the module:

Once you're done testing, you can unload the module from the kernel with the `rmmod` command:

```bash
sudo rmmod kernel_module
```

### 7. Clean up the build files:

If you want to clean up the compiled files (i.e., remove the `.ko` file and other build artifacts), run:

```bash
make clean
```

## How It Works

The kernel module utilizes the **Netfilter** framework to intercept network packets at the kernel level. Netfilter is a framework built into the Linux kernel that provides an interface for packet filtering, network address translation (NAT), and other packet manipulation. By tapping into this framework, the module can efficiently capture network traffic in real-time. Here's a detailed breakdown of how the module works:

### 1. **Netfilter Hook Registration**

The kernel module registers a **Netfilter hook** at the `NF_INET_PRE_ROUTING` point in the kernel. Netfilter hooks are used to define specific points where packets can be intercepted in the network stack. The `NF_INET_PRE_ROUTING` hook is triggered before the kernel makes routing decisions, which allows the module to inspect incoming packets right when they enter the system. This is crucial for sniffing traffic before any routing or processing happens, ensuring that the packet is captured early.

### 2. **Packet Inspection**

Once the packet is intercepted, the module performs a check to determine if the packet is an **IP packet**. If it is, the module extracts the **source** and **destination IP addresses** from the packet header. This information is vital for identifying the origin and destination of the network traffic. The module can be extended to capture additional packet details such as the protocol type, source/destination ports, and more, but in this implementation, the focus is on IP addresses for simplicity and effectiveness.

### 3. **Logging the Information**

After extracting the relevant data, the module logs the **source** and **destination IP addresses** into the kernel log. This is done using the `printk` function, which is similar to `printf` but is used within kernel space to output messages to the kernel log. These log messages can then be viewed using tools like `dmesg` or other system logging utilities (such as `syslog` or `kern.log`). The log entries typically include the packet capture timestamp, source IP, destination IP, and an indication of a captured packet.

### 4. **Real-time Packet Sniffing**

By operating at the kernel level, this module captures packets in **real-time**, allowing for minimal delay between packet arrival and logging. The kernel space operates with high efficiency, making it an ideal environment for capturing network traffic with minimal impact on system performance. Unlike user-space packet sniffers, which can suffer from higher latency and may miss packets under heavy network load, kernel-based sniffing can provide a more reliable, low-latency alternative. The data is immediately available in the kernel log, where it can be monitored or saved for further analysis.

### Additional Considerations

- **Efficiency**: Since the module operates directly in the kernel space, it doesn't have the overhead of user-space applications. This results in a more efficient packet-sniffing process, with lower latency and higher throughput.
- **Packet Filtering**: The module can be further enhanced to filter specific types of packets or analyze additional fields of the packet, such as TCP/UDP ports, flags, etc.
- **Security**: While powerful, kernel modules have significant control over the system. It’s important to understand the potential risks and ensure the module is used in a secure and controlled environment (e.g., testing environments).

### How to Implement and Use It

1. **Prerequisites**: Ensure that you have a compatible Linux system with kernel version 4.x or higher. You need root privileges to load and unload kernel modules.
2. **Clone and Build the Module**: Follow the setup instructions to clone the repository, build the module using `make`, and load it into the kernel with `insmod`.
3. **Monitor Traffic**: Once the module is loaded, use `dmesg` or check kernel logs to see captured packets in real-time.
4. **Unload and Clean Up**: After testing, unload the module with `rmmod` and clean up build files using `make clean`.

By using this approach, you can directly tap into network traffic without relying on user-space tools, making this method highly effective for deep-level traffic analysis.

## Important Notes

- **Proof of Concept**: This module is a proof-of-concept and should not be used in production environments.
- **Test on Non-Production Systems**: It is recommended to test this module on a non-production system to avoid any unintended consequences.
- **Backup Your Data**: Always back up important data before testing kernel modules, as loading and unloading kernel code can sometimes lead to system instability.
- **Kernel Modules**: Make sure you have a good understanding of kernel programming and your system’s architecture before loading kernel modules. Incorrect module usage can cause crashes or other issues.

## Conclusion

Thank you for exploring this project! This **Linux Kernel Module for Packet Sniffing** provides a powerful way to intercept and analyze network traffic at the kernel level, offering a more efficient and low-latency approach compared to traditional user-space sniffing tools.

While this module serves as a proof of concept, it demonstrates the potential of kernel-level packet analysis, which can be further extended to include advanced filtering, traffic monitoring, and custom packet processing features.

If you have any questions or suggestions for improvements, feel free to open an issue or contribute to the project. Happy coding, and always be cautious when working with kernel modules—ensure you’re testing in a controlled environment!
