# Lab4_Harry_Joseph_N00881767

## Course Information
- Course: CPAN-226 (Networking & Telecommunications)
- Lab: 04
- Student Name: Harry Joseph
- Student ID: N00881767
- Date: February 20, 2026

## Lab Objective
Explore the tangible impact of multithreading on server performance by transitioning from a sequential server (handling requests one-by-one) to a multithreaded server using the pthread library. Identify performance bottlenecks and measure how concurrency can drastically reduce total elapsed time in network scenarios.

## Files Used
- [`timedDelayThreadsM.c`](timedDelayThreadsM.c) — multithreaded server (Task 2) ← click to view code
- `timedDelayNothreads.c` — sequential server (Task 1)
- `client.c` — parallel test client (Task 1)
- `clientM.c` — parallel test client (Task 2)
- `implementation.md` — detailed implementation + technical notes

## Tools / Environment
- OS: Windows
- Compiler: GCC 15.2.0 (Rev11, Built by MSYS2 project)
- Terminal: MSYS2 MinGW64 bash
- Packet Analyzer: Wireshark

---

<br>

# TASK 1: Establish a Baseline (Sequential)

> Measure the "slow" version — server handles one client at a time with a 5-second delay each.

---

## Task 1 — Screenshots

### Setup & Compilation

**Screenshot 1 — `01_compiler_version.png` — Output of `gcc --version` command**

![Compiler Version](screenshots/01_compiler_version.png)

---

**Screenshots 2 & 3 — `02_Server03_Client_compilation.png` — Successful compilation of server (left) and client (right) side by side**

![Server & Client Compilation](screenshots/02_Server03_Client_compilation.png)

---

**Screenshot 4 — `04_directory_listing.png` — Directory showing `server.exe` and `client.exe`**

![Directory Listing](screenshots/04_directory_listing.png)

---

### Wireshark Setup

**Screenshot 5 — `05_wireshark_setup.png` — Interface selection and capture filter `tcp port 8080`**

![Wireshark Setup](screenshots/05_wireshark_setup.png)

---

**Screenshot 6 — `06_wireshark_capture_started.png` — Wireshark capturing with start time visible**

![Wireshark Capture Started](screenshots/06_wireshark_capture_started.png)

---

### Execution

**Screenshots 8 & 9 — `08_Server09_Client_mid_execution.png` — Server processing sequentially (left) and all 5 client requests connected and waiting (right)**

![Mid-Execution Side by Side](screenshots/08_Server09_Client_mid_execution.png)

---

**Screenshots 10 & 11 — `08_Server09_Client_mid_executionF.png` — Completed run: server all 5 clients handled (left) + final elapsed time (right)** ⚠️ CRITICAL

![Completed Run Side by Side](screenshots/08_Server09_Client_mid_executionF.png)

---

### Wireshark Analysis

**Screenshot 12 — `12_wireshark_stopped.png` — Capture stopped with end time visible**

![Wireshark Stopped](screenshots/12_wireshark_stopped.png)

---

**Screenshot 14 — `14_http_response.png` — HTTP response packet with `Hello Client!` content visible in detail pane**

![HTTP Response](screenshots/14_http_response.png)

---

**Screenshot 16 — `16_tcp_termination.png` — FIN/ACK connection close sequence**

![TCP Termination](screenshots/16_tcp_termination.png)

---

**Screenshot 17 — `17_tcp_conversations.png` — Statistics → Conversations → TCP showing all 5 connections**

![TCP Conversations](screenshots/17_tcp_conversations.png)

---

## Task 1 — Wireshark Capture Evidence

| Field | Value | Reference |
|---|---|---|
| Capture Filter | `tcp port 8080` | Screenshot 5 |
| Display Filter | `tcp.port == 8080` | — |
| Interface | Adapter for loopback traffic capture | Screenshot 5 |
| Capture Start Time | 0.000000 s (Packet 1) | Screenshot 6 |
| Capture End Time | 25.131800 s (Packet 45) | Screenshot 12 |

### Wireshark Proof Provided

| Status | File | Description |
|---|---|---|
| ✅ | `screenshots/14_http_response.png` | HTTP response with "Hello Client!" content |
| ✅ | `screenshots/16_tcp_termination.png` | Connection close sequence (FIN/ACK) |
| ✅ | `screenshots/17_tcp_conversations.png` | Statistics showing all 5 TCP conversations |

---

## Task 1 — Results

| Metric | Value |
|---|---|
| Number of client requests (`NUM_REQUESTS`) | 5 |
| Artificial server delay per request | 5 seconds |
| Expected total time (sequential) | ~25 seconds |
| **Sequential Execution Time (measured)** | **25.00 seconds** |

> Measured time taken from `08_Server09_Client_mid_executionF.png`

<br>

---

<br>

---

<br>

# TASK 2: Implement the Solution (Multithreaded)

> Modify the server to handle connections concurrently using `pthread_create` + `pthread_detach`.
> Expected total time: ~5 seconds (all 5 clients handled simultaneously).

---

## Task 2 — Screenshots

### Compilation

**Screenshot T2-1 — `20_ThreadedM_compilation.png` — Successful compilation of `timedDelayThreadsM.c` (left) and `clientM.c` (right) side by side**

![Threaded Compilation](screenshots/20_ThreadedM_compilation.png)

---

### Execution

**Screenshot T2-2 — `21_22_ThreadedM_execution.png` — Combined: server + client side by side showing all 5 clients connected simultaneously mid-run AND final elapsed time ~5s** ⚠️ CRITICAL

![Threaded Execution](screenshots/21_22_ThreadedM_execution.png)

---

### Wireshark Analysis

**Screenshot T2-3 — `23_ThreadedM_wireshark.png` — Wireshark capture showing all 5 HTTP `200 OK` responses arriving within ~0.1 seconds of each other (~5s mark), proving concurrent handling**

![Threaded Wireshark](screenshots/23_ThreadedM_wireshark.png)

---

**Screenshot T2-4 — `24_ThreadedM_conversations.png` — Statistics → Conversations → TCP showing all 5 connections started within 0.07 seconds of each other, each lasting ~5 seconds simultaneously**

![Threaded Conversations](screenshots/24_ThreadedM_conversations.png)

> Compare to Task 1 `17_tcp_conversations.png` where connections started ~5 seconds apart — here all 5 Rel Start times are nearly 0, proving the server handled them all at once

---

## Task 2 — Results

| Metric | Value |
|---|---|
| Number of client requests | 5 |
| Server type | Multithreaded (`pthread_create` + `pthread_detach`) |
| Expected total time | ~5 seconds |
| **Multithreaded Execution Time (measured)** | **5.00 seconds** |

> Measured time taken from `21_22_ThreadedM_execution.png`

<br>

---

<br>

---

<br>

# LAB REPORT

## 1. Performance Data

| Metric | Value |
|---|---|
| Sequential Execution Time | **25.00 seconds** |
| Multithreaded Execution Time | **5.00 seconds** |
| Percentage Reduction | **(25.00 − 5.00) / 25.00 × 100 = 80%** |

**Formula:** Reduction % = (Sequential Time − Threaded Time) / Sequential Time × 100

*Example: if threaded = 5.00s → (25.00 − 5.00) / 25.00 × 100 = **80%***

<br>

---

<br>

## 2. Analysis

### 2a. Sequential Bottleneck (Task 1)

The server is single-threaded so it can only deal with one client at a time. No matter how many connect, they all have to wait in line.

- Inside `handle_client()` there is a 5-second sleep that freezes the entire server while it runs
- The client launches 5 threads at once and they all connect fine, but the server queues them and handles them one by one
- Request 1 finishes at ~5s, request 2 at ~10s, request 3 at ~15s — it is simply 5 × 5 seconds
- Total comes to ~25 seconds even though the client side was trying to do everything in parallel

---

### 2b. Code Changes Made for Task 2

- Added `#include <pthread.h>`
- Added `client_args_t` struct to bundle `client_socket` + `client_id` for passing to the thread
- Changed `handle_client()` signature to `void* handle_client(void* arg)` to be pthread-compatible
- Replaced the direct `handle_client(client_socket, client_count)` call in `main()` with:

```c
pthread_create(&thread, NULL, handle_client, args);
pthread_detach(thread);  // auto-reclaim thread resources on exit
```

---

### 2c. Why Did Time Improve Even Though `sleep(5)` Didn't Change?

- In the sequential version, `sleep(5)` blocks the one and only thread — nothing else can run during that time
- In the multithreaded version, each client connection gets its own thread, so all 5 run `sleep(5)` **at the same time**
- Instead of waiting 5+5+5+5+5 seconds in a line, all 5 sleeps overlap — total wall-clock time drops to ~5s
- The work per client did not change at all, but the server can now do it in parallel

---

### 2d. Wireshark Evidence Summary (Task 1)

- The Conversations tab (Screenshot 17) clearly shows 5 separate TCP connections all going to port 8080
- The HTTP responses came in one at a time, roughly 5 seconds apart from each other (Screenshot 14)
- Each connection only got its response after the server finished the sleep for that client
- The FIN/ACK sequences happen individually per connection (Screenshot 16), not all at once

---

### 2e. Expected vs Actual Timing

| | Value |
|---|---|
| **Expected** | 5 clients × 5 seconds = 25.00 seconds |
| **Actual measured** | 25.00 seconds |
| **Difference** | ~0 — loopback network overhead is negligible |

---

### 2f. Scaling Scenarios

| Requests | Sequential Server | Multithreaded Server |
|---|---|---|
| 5 | 25 seconds *(measured)* | ~5 seconds *(expected)* |
| 10 | 10 × 5s = **50 seconds** | ~5 seconds (all concurrent) |
| 150 | 150 × 5s = **750 seconds (~12.5 min)** | ~5–8 seconds (OS scheduling overhead starts showing) |
| 1,000 | 1,000 × 5s = **5,000 seconds (~83 min)** | likely **crashes or degrades badly** — 1,000 threads hits OS limits, memory spikes, context-switching overhead kills performance |

The sequential server scales linearly in the worst possible way — every extra client adds 5 more seconds to the total wait. With 150 requests the last client waits over 12 minutes, which is completely unusable. The multithreaded version handles 10 or 150 requests just as fast as 5, but at 1,000 simultaneous threads it starts to fall apart too. That is where a thread pool or async I/O with `select()`/`epoll()` would be the right solution instead of spawning a new thread per client.

<br>

---

<br>

## 3. Conclusion

This lab demonstrated the real-world difference between a server that handles clients one at a time versus one that handles them concurrently. Running it yourself makes the impact of threading immediately obvious.

---

### 3a. Server-Side Bottlenecks

Even with 5 clients connecting at the exact same time, the sequential server queued them all up. The `sleep(5)` call simulates something slow — a database query, a file read — and you can see how badly that affects every client waiting behind the first. Total time went from what could have been 5 seconds to 25 seconds purely because of that single-threaded design choice.

---

### 3b. Concurrency Limits of a Non-Threaded Design

This design tops out at one request every 5 seconds. With 20 clients, the last one waits almost 2 minutes. That is not acceptable for any real application. The server has no way to overlap work, so every additional client just increases the total wait time linearly.

---

### 3c. Benefits of Multithreading in I/O-Bound Network Applications

**With threads (`timedDelayThreadsM.c`):** the server spawns a new thread per client connection. All 5 run `handle_client()` simultaneously, finish around the 5-second mark, and total time drops from 25s to ~5s. That is a 5× speedup from a small code change — replacing a direct function call with `pthread_create` and adding `pthread_detach` for automatic cleanup.

**With async I/O:** using `select()` or `epoll()` to monitor multiple sockets at once without blocking scales even further — no thread-per-client overhead — but is more complex to implement.

The core lesson is clear: blocking everything on a single thread is fine for trivial workloads but collapses quickly under concurrent users. Concurrency — whether via threads or async I/O — is essential for any serious network server.

<br>

---

<br>

## Submission Checklist

### Task 1 — Sequential Baseline
- [x] `timedDelayNothreads.c` included ✅
- [x] `client.c` included ✅
- [x] Sequential time recorded: **25.00 seconds** ✅

### Task 2 — Multithreaded Implementation
- [x] `timedDelayThreadsM.c` included *(with authorship comment at top)* ✅
- [x] GitHub public repository link: https://github.com/hjoseph777/CPAN226-Lab4 ✅
- [x] Multithreaded time recorded: **5.00 seconds** ✅
- [x] % reduction calculated: **80%** ✅

### Screenshots in `screenshots/` folder

**Task 1 screenshots:**
- [x] `01_compiler_version.png` ✅
- [x] `02_Server03_Client_compilation.png` ✅
- [x] `04_directory_listing.png` ✅
- [x] `05_wireshark_setup.png` ✅
- [x] `06_wireshark_capture_started.png` ✅
- [x] `08_Server09_Client_mid_execution.png` ✅
- [x] `08_Server09_Client_mid_executionF.png` ✅ ⭐ CRITICAL
- [x] `12_wireshark_stopped.png` ✅
- [x] `14_http_response.png` ✅
- [x] `16_tcp_termination.png` ✅
- [x] `17_tcp_conversations.png` ✅

**Task 2 screenshots:**
- [x] `20_ThreadedM_compilation.png` ✅
- [x] `21_22_ThreadedM_execution.png` ✅ ⭐ CRITICAL
- [x] `23_ThreadedM_wireshark.png` ✅
- [x] `24_ThreadedM_conversations.png` ✅

### Other
- [x] `implementation.md` included ✅
- [ ] `README.md` fully completed (all placeholders filled)
- [ ] Performance Data table filled in
- [ ] GitHub link added
