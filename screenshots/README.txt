SCREENSHOT NAMING GUIDE FOR LAB 4
===================================

Save all screenshots in this directory with the exact names below:

SETUP & COMPILATION (4 screenshots)
-----------------------------------
01_compiler_version.png          - Run "gcc --version" in terminal
02_server_compilation.png        - Successful server compilation output
03_client_compilation.png        - Successful client compilation output
04_directory_listing.png         - "dir" showing server.exe and client.exe

WIRESHARK SETUP (2 screenshots)
--------------------------------
05_wireshark_setup.png           - Interface selection + capture filter "tcp port 8080"
06_wireshark_capture_started.png - Wireshark capturing with start time visible

EXECUTION (5 screenshots)
-------------------------
07_server_started.png            - Server showing "listening on port 8080" message
08_server_processing_mid.png     - Server processing client 2 or 3 (mid-execution)
09_client_waiting_mid.png        - Client showing multiple connections waiting
10_client_final_output.png       - **CRITICAL** Final output with elapsed time
11_server_complete.png           - Server showing all 5 clients handled

WIRESHARK ANALYSIS (6 screenshots)
-----------------------------------
12_wireshark_stopped.png         - Capture stopped with end time visible
13_tcp_handshake.png             - First 3 packets: SYN, SYN-ACK, ACK
14_http_response.png             - HTTP response packet with "Hello Client!" content
15_multiple_tcp_streams.png      - Packet list showing multiple connections
16_tcp_termination.png           - FIN/ACK connection close sequence
17_tcp_conversations.png         - Statistics → Conversations → TCP (all 5 connections)

TIPS
----
- Use Windows Snipping Tool (Win + Shift + S) for quick screenshots
- Make sure text is readable (don't resize too small)
- In Wireshark, use Edit → Mark Packet to highlight important packets
- Screenshot 10 is CRITICAL - it contains the elapsed time you need for analysis
