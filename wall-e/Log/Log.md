Log

- ##### 20191202

  - `GPIOB_Pin3`、`GPIOB_Pin4` 模拟I2C无法输出波形：
  
    - `GPIOB_Pin3`、`GPIOB_Pin4` 默认为 `JTDO`、`JNTRST `功能，作为普通 GPIO 输出需要使用 Remap 功能做重定向。
    - 使用 Remap 功能：
      - (1) 开启 RCC_APB2Periph_AFIO 时钟。
        - `RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);`
      - (2)  开启  Remap 的目标端口。此处为失能掉 JTAG。
        - `GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); `
    
  - **ARM GCC 压缩编译生成的固件大小的编译参数**：
  
    - 编译参数 `-ffunction-sections` 、` -fdata-sections` 和链接参数 `--gc-sections`：
  
      - 使用`-ffunction-sections`, `-fdata-sections` 使 compiler 为每个 function 和 data item 分配独立的 section。
      - `--gc-sections` 会使 ld 删除没有被使用的 section。
  
    - 编译参数 `-fno-rtti`、` -fno-exceptions`：
  
      - `-fno-rtti`： Don't generate runtime type idertification (RTTI)。 
      - `-fno-exceptions`：Don't catch exceptions。
  
    - 编译参数 `-Os`：
  
      - Optimize gennerated code(for size) [-Os]。
      - 除了 `-Os` 外，还有 `-O0`  、`-O1`、  `-O2`、 `-O3`、 `-Ofast`。
  
    - 链接参数`--specs=nano.specs`：
  
      - 使用静态库 `libc_nano.a` 、`libstdc++_nano.a`、 `libsupc++_nano.a`  替换默认的静态库 `libc.a`、   `libstdc++.a`、 `libsupc++.a` ，这样可以大大减小固件。
  
    - `-g`  、`-g1`、 `-g2`、 `-g3` ：
  
      - 调试信息，也会影响生成固件的大小。
  
      - [待考证]：
  
        > .debug 是一些调试信息的段 (section)，这些段会链接到目标文件 (.elf) 中，但它们的段标志为 0（不分配地址空间，不执行），并且这些段也不包含在程序头（program header）中，就不会写入 hex 以及单片机中。这些段就相当于文件附加的说明，它们的作用，就仅仅限于被调试程序读取并展现给你。





- ##### 20191127

  - 修复使用JLink-RTT作为`printf`输出调试日志问题。
    - `JLink_Linux_V654c_x86_64/Samples/RTT/SEGGER_RTT_V654c/RTT/`
    - `JLink_Linux_V654c_x86_64/Samples/RTT/SEGGER_RTT_V654c/Syscalls/`
      - `SEGGER_RTT_Syscalls_SES.c`
      - `SEGGER_RTT_Syscalls_GCC.c`



- ##### 20191126

  - Atom 在国内无法安装 Package 的解决方案。
  - 以goto-definition为例：
      - 到[Atom官方插件库](https://atom.io/packages)中搜索出goto-definition；
      - 点击插件详情页中的Repo，进入该插件的Github仓库；
      - clone该项目到你的Atom插件目录（Ubuntu： `~/.atom/packages`）；
      - cd到该插件目录下，执行 `npm install`，安装完成。
        - 安装过程中，npm install 报错`still pacote range manifest xxx` 的解决方法：
          - `npm config set registry https://registry.npm.taobao.org`
          - 验证：`npm config get registry`
  - Atom 安装插件记录：
    - `goto-definition`：跳转到定义处
    
    - `highlight-selected`：选中内容高亮
    
    - `minimap`：代码缩略图
    
    - `minimap-highlight-selected`：minimap 中高亮选择内容
    
    - `script`：在 atom 下运行脚本
    
      - `ctrl + shift + p`：
    
    - `convert-to-utf8`：自动转换为 utf-8
    
    - `copy-filename`：复制文件名
    
    - `sync-settings`：备份插件
    
      - 参考：https://www.jianshu.com/p/bd006b349d03
    
      - 修改 host 解决无法访问 gist 问题。
    
        - (1) `ping 192.30.253.119` 测试可以访问；
    
        - (2) `sudo vi /etc/hosts` 添加如下语句：
    
          ```shell
          192.30.253.118 gist.github.com
          192.30.253.119 gist.github.com
          ```
    
          



- ##### 20191125

  - 1）github 忽略已经提交的文件 (.gitignore文件无效) 方法。

    -  ① 删除track的文件 (**已经commit的文件**)
      - ` git rm 要忽略的文件 `
      - ` git commit -a -m "删除不需要的文件"`
    - ②  在`.gitignore`文件中添加忽略规则
      -  在`.gitignore`文件中添加ignore条目, 如: `some/path/some-file.ext`
      -  提交`.gitignore`文件: `git commit -a -m "添加ignore规则"`
    - ③  推送到远程仓库使 ignore 规则对其他开发者也能生效
    - 建议：**初始化git项目时就创建`.gitignore`文件**

  - 2）处理 git push 报错。

    > git Could not read from remote repository.Please make sure you have the correct access rights

    - ① `ssh-keygen -t rsa -C mail@mail.com`
    - ② `less ~/.ssh/id_rsa.pub` 并添加 github
    - ③ 连接确认：`ssh -T git@github.com`



- ##### 20191124

  - 1）串口3一直进入中断问题。

    ```c
    USART_ClearITPendingBit(USART3,USART_IT_RXNE);
    uart_receive=USART_ReceiveData(USART3);
    ```






- ##### 20191123

  - 1）Windows 开发环境：~~openOCD~~ + JLink-OB + Atom 搭建。

    - ① 代码编写：Atom

      - 设置Atom `Tab`键转换为`Space`键，统一格式。
        - `File` > `Settings` > `Editor`取消勾选` Atomic Soft Tabs`
        - 勾选 ` Soft Tabs`
        -  `Tab Type`下选择`soft`，并设置`Tab Length`的值为`4 `

    - ② 编译工具：

      - gcc-arm-none-eabi-5_4-2016q3-20160926-win32.exe
      - 使用Cygwin安装Unix兼容环境：
        - Cygwin更换阿里云源：  http://mirrors.aliyun.com/cygwin/   
        - 安装软件包： make / sed / subversion / automake/ binutils / diffutils / gdb
        -  添加环境变量：C:\cygwin64\bin

    - ③ 下载工具：JLink-OB

      - 驱动安装：JLink_Windows_V654c.exe
      - 连接到目标板：`JLink -device stm32f103c8 -if swd -speed 100 -autoconnect 1`
      - 下载 bin 到目标板：`loadbin demo.bin 0x08000000  `
        - 可将命令写入脚本，然后` JLinkExe -commanderscript xxxxxx `来运行脚本
        - 举例：`JLink -device stm32f103c8 -if swd -speed 100 -autoconnect 1 -CommanderScript .\JLinkCommandFile.jlink`
      - 命令：
        - `r`，即reset，复位板子
        - `g`，即go，代码继续运行
        - `h`，即halt，暂停运行
        - `regs`，查看寄存器。看寄存器用处挺大的，看PC、LR、PSR值，会知道此时CPU到底正常与否，到底发生了什么fault。
        - `mem8`、`mem16`、`mem32`，查看对应内存地址的值。比方说出现了hardfault，这时候查看NVIC的hardfault寄存器，看看哪个fault上访；比方说出现了bus fault，查看是哪种总线错误，查看出错的地址等等。用处相当大。
        - `w1`、`w2`、`w4`，将值写入对应的内存地址。写脚本时候可以用这些命令来初始化外设寄存器。这时就要老老实实翻手册，计算哪个寄存器应该写哪些值。
        - `erase`，擦除整个片内flash
        - `loadbin`，烧写程序，格式是`loadbin 哪个bin 哪个地址`。蛋疼的是，它只认.bin后缀的文件
      - 参考：
        -  https://wiki.segger.com/J-Link_Commander#Command_specifics
        -  [https://hhuysqt.github.io/gdb%E8%B0%83%E8%AF%95%E6%8A%80%E5%B7%A7/](https://hhuysqt.github.io/gdb调试技巧/)

    - 至此，编译、下载工具链已搭建完成。

    - ④ 调试工具：~~Open-OCD~~

      > OpenOCD 是一款开源调试软件，支持 JLink 等多种调试器，同时支持 Cortex 等多种嵌入式处理器，另外还提供一个GDB Server 接口。

      - Open-OCD 下载： http://www.freddiechopin.info/en/download/category/4-openocd
      - 使用工具 zadig 安装仿真器驱动程序：
        - jlink > winUSB
        - Open-OCD 只把 JLink 仿真器当作普通的USB设备来使用，不能使用 JLink 自带的仿真器驱动程序。如果已安装了JLink 仿真器驱动程序，zadig 把原先的驱动程序换掉。更换驱动程序后，JLinkExe 将无法识别 JLink-OB 设备(测试时，JLink-v9 在插入时，zadig 无法识别其为 `jlink` ，因此在更换驱动后，仍然能够被 JLinkExe 识别)。
          - 参考： https://blog.csdn.net/qingwufeiyang12346/article/details/45954595
      - 测试连接成功：`openocd -f interface/jlink.cfg -f target/stm32f1x.cfg `
        - Open-OCD  默认的使用`jtag`接口 ，如果使用`swd`接口，会报`Error:JTAG scan chain interrogation failed: all zeroes`，需调整 jlink.cfg：+` transport select swd` 。
      - 卸载 zadig 替换的驱动程序：
        - 设备管理器中，右键点击对应的设备后选择`卸载驱动`，然后重新插拔设备，此时会重新匹配并选择原有驱动。
        - 参考：https://github.com/pbatard/libwdi/wiki/FAQ#Zadig  

  - 2）修复使用 JLink-OB 调试器，在运行 JLinkExe 时弹窗 `The connected J-Link is defective `问题。

    - JLink Version：JLink_V654c
    - Ultra edit 打开 JLinkExe.dll：`85 C0 75 75 6A 01 ` -> ` 85 C0 EB 75 6A 01 E8 `





- ##### 20191122

  - 1）解决使用 RTT 作为 `printf` 调试输出时，不支持浮点数类型问题。

    - 使用`JLink_Linux_V654c_x86_64/Samples/RTT/SEGGER_RTT_V654c/RTT/`、`JLink_Linux_V654c_x86_64/Samples/RTT/SEGGER_RTT_V654c/Syscalls/`解决。

      - 编译报错：`conflicting types for '_write_r'`：注释即可。
    
    - ~~方式1：添加~~
    
      ```c
  signed int RTT_printf(unsigned BufferIndex,const char * pFormat, ...){
          char pStr[50] = {'\0'};
          va_list ap;
          signed int result;
      
      	// Forward call to vprintf
          va_start(ap, pFormat);
      	result = vsprintf((char * )pStr, pFormat, ap);
          va_end(ap);
      
          SEGGER_RTT_WriteString(BufferIndex,(char * )pStr);
  
          return result;
  }
      ```
      
    - ~~方式2：添加~~
      
      ```c
      int printf(const char * fmt,...) {
      
        char buffer[128];
        va_list args;
        va_start (args, fmt);
        int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
        SEGGER_RTT_Write(0, buffer, n);
        va_end(args);
        return n;
      }
      ```
      
      
    
    





- ##### 20191121

  - 1) 使用 Open-OCD 进行 GDB 调试时出现 `Don't know how to run` 问题。

    >(gdb) b 152
    >
    >Breakpoint 1 at 0x80006b0: file ../User/main.c, line 152.
    >
    >(gdb) r
    >
    >Don ‘t know how to run.

- 2) 使用 JLink-RTT 用作 `printf` 输出调试信息。
    - JLink version：JLink-v654
    - 源码目录：`jlink/Samples/RTT/SEGGER_RTT_V654c/`
    - 使用：
      - `SEGGER_RTT_Init();`
    - enjoy
    - 参考：https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/
