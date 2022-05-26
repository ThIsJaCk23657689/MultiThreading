# Multi-Threading
程式可以透過多執行緒來提高程式的效率，即使 CPU 一次只能執行一個執行緒，但作業系統可以快速的在不同的執行緒之間進行切換，由於間隔時間很小，所以可以營造出多執行緒同時執行的現象。

* Program（程式）: 指尚未被 Load 到記憶體的 Code
* Process（行程）: 指正在執行的程式，作業系統會分配其所需要的資源，且至少存在有一個執行緒，主要包含：Code、Data、Heap 和 Stack 等。
* Tread（執行緒）: 指 OS 分配 CPU 進行運算的基本單位，存在於 Process 中。
* Multi-Threading（多執行緒）: 指將一個程式中不同的任務分配給多個執行緒運行，並在同一個行程的執行緒共享記憶體。
> 不同的 Process 無法互相共享記憶體。

### Multi-threading vs Hyper Threading
一般 CPU 上講的執行緒數量是指：同一時間電腦能執行的執行緒數量，這是由 Intel 所開發的 Hyper-Threading 技術，在 CPU 內複製必要的資源，讓兩執行緒可以在單一時間執行。

而一個執行中的軟體或是應用程式，可以是一個或是多個 Process；而一個 Process 至少會有一個或是多個 Threads，等待著被執行，所以一個程式所需的 Threads 數量上限跟 CPU 的 Threads 數量沒有太大關係。

## Memory Layout (C Language)
* code (text): 程式碼，基本上這個區塊儲存的是 CPU 的指令（instructions）。
* data: 已初始化靜態變數，例如 global variables or static variables。
* heap: 動態配置變數，例如 C 語言的 `malloc` 和 C++ 的 `new` 時所建立的變數都是儲存於此。
* stack: 用於函數內的區域變數，以及各種函數呼叫時需要儲存的資訊（例如函數回傳記憶體位址或者呼叫函數狀態等），每一次的 function call 都會建立一個 stack frame，來儲存該次呼叫的所有變數與狀態。
* bss: 未初始化靜態變數，在程式執行前會被系統初始化為 `0` 或 `null`；另外 bss 代表的涵義為 block started by symbol。
* system: 命令列參數與環境變數，這部分跟系統有關。

## Concurrency vs Parallelism
Concurrency（並行）指的是程式的架構，將程式拆開成多個可獨立運作的工作，但注意拆開的工作不一定會同時運行。
Parallelism（平行）指的是程式的執行，同時執行多個程式，根據性質又可以分為兩種：

* Data Parallelism: 相同的資料分工給多執行緒同時處理，處理方式相同。
* Task Parallelism: 相同（也可能不相同）的資料分工給多執行緒同時處理，處理方式不同。

### Parallel Computing
除了可以使用 OpenMP 來實現平行運算之外，還可以透過 Nvidia Cuda 和 OpenCL 的平行運算函式庫，透過 GPU 來進行大量資料的平行運算。

### Volatile and Static
https://www.wikiwand.com/zh-hant/Volatile%E5%8F%98%E9%87%8F

## Problems
* Context Switch（上下文切換）: 當 CPU 要切換執行緒時，必須要先儲存當前的狀態等，所以切亂過程會需要花費一些時間。
* Race Condition（競爭危害）: 指一個執行緒修改動做到一半時被切換，且切換後的 Thread 剛好也修改同一個地方，可能會發生記憶體洩漏、違規存取或是變數數值錯誤等不可預期之錯誤，解決方案就是使用 Critical Section。
* Critical Section（臨界區段）: 指存取共享資源的程式碼區域，這些不可被多個 Thread 存取。
* Deadlock（死結）: 兩個以上的 Thread 互相等待對方停止支援並釋放資源，造成循環等待的情況。

### Synchronized Methods
* Mutex（互斥鎖）
* Semaphore（訊號）
* Condition Variable（條件變數）
* Atomic（原子操作）
* Queue（佇列）
* Event（事件）

## Platform
### Unix
Sun Solaris 作業系統就使採用 UNIX International 執行緒。

### POSIX
POSIX Threads，簡稱 PThreads，是執行緒的 POSIX 標準，用於 Unix、Linux 和 Mac OS X 等。
標頭檔為 `<pthread.h>`。

### Windows
Win32 Thread 是 Windows API 的一部分，標頭檔為 `<Windows.h>`。

### Cross-Platform
C++ 11 STL 提供的 `<thread>` ，基本上 Windows、Linux 都有完美支援。

## Reference
https://blog.gtwang.org/programming/memory-layout-of-c-program/
https://hackmd.io/@sysprog/concurrency/
https://jenifers001d.github.io/2020/08/04/%E9%9B%BB%E8%85%A6%E7%9F%A5%E8%AD%98/what-is-core-and-thread/
https://medium.com/ching-i/%E5%A4%9A%E5%9F%B7%E8%A1%8C%E7%B7%92-de16f92944c8
https://zh.wikipedia.org/zh-tw/%E7%BA%BF%E7%A8%8B
https://kheresy.wordpress.com/2012/07/06/multi-thread-programming-in-c-thread-p1/

------------------------------------------------------------
Written by ThIsJaCk.