tudos-loongson
==============

tudos port to loongson1b

tudos from svn version r49(P-MKLS232-001-20130211).

既然无法完全读懂tudos的构建系统，那么从一个空白的结构开始逐文件添加，也许是一个可
行的方案。


尝试构建TUDOS内核FIASCO的MIPS移植（T-MKLS232-002-20130314）
----------------------------------------------------------

1. 准备
tudos源目录 ： src-dir= ~/Code/tudos
测试目录    ： dst-dir=~/Code/github/tudos-loongson

2. 根据tudos的说明，最初的构建是从fiasco开始的。首先将最基本的Makefile拷贝过去。
$ cp ${src-dir}/src/kernel/fiasco/Makefile ${dst-dir}/src/kernel/fiasco/Makefile
$ cd ${dst-dir}/src/kernel/fiasco
$ make BUILDDIR=${dst-dir}/build
这时提示需要template。继续拷贝
$ cp ${src-dir}/src/kernel/fiasco/src/templates/Makefile.builddir.templ src/templates/Makefile.builddir.templ
$ make BUILDDIR=${dst-dir}/build
Creating build directory "/home/loongson/Code/github/tudos-loongson/build/"...
done.
好，转入build目录，下一步。

3. 根据tudos的说明，这一步要对内核进行配置。
$ make menuconfig
提示缺少bsp和Kconfig。另外，由于不需要这些bsp，所以要修改Makefile。

4. 添加bsp。修改Makefile
以原始版本中的ppc32/bsp为范本，创建mips/bsp/loongson1b
$ vim src/kernel/fiasco/src/Makefile
182行
BSP_DIR            := $(srcdir)/kern/arm/bsp $(srcdir)/kern/ppc32/bsp $(srcdir)/kern/sparc/bsp
修改为
BSP_DIR            := $(srcdir)/kern/mips/bsp

5. 添加Kconfig，修改Kconfig
**make menuconfig会根据Kconfig生成配置菜单，然后在设置相应的配置变量。**
仿照PPC32添加MIPS配置

6. 再次配置
$ INCLUDE_MIPS=y make menuconfig
配置菜单中选中：
[*] Prompt for experimental features
会开启MIPS处理器选项。_
在Debugging部分，取消
[ ]   JDB disassembler
将处理器及平台选好。保存，退出配置。

7. 开始编译
$ make
提示缺少Makeconf。

8. 添加Makeconf，按照Makeconf.ppc32添加Makeconf.mips。
**Makeconf以及体系相关的Makeconf.xxx用来配置工具链及库。**
关于LD_EMULATION_CHOICE，可以根据ld -V查看工具链（当然是MIPS工具链）支持的emulation。

9. 再次编译
$ make
提示缺少Modules.mips和Modules.generic

10. 添加Modules.generic和Modules.mips
**Modules.xxx是模块配置文件。构建内核的必备文件。此处模块与Linux的内核模块概念不同。**
根据Modules.ppc32添加Modules.mips。其中内容涉及到抽象对象的具体实现的问题，由于移植只针对Loongson1B，所以实现的后缀不用mips而用loongson1b。

11. 再次编译
$ make
提示缺少Makefile.sub1和Makefile.sub2

12. 添加Makefile.sub1和Makefile.sub2
**据信，Makefile.sub1用来创建源文件**
**据信，Makefile.sub2用来创建其他的文件（文档什么的）**

13. 再次编译
$ make
提示缺少Makerules.global

14. 添加Makerules.global和Makerules.xxx
**Makerules.xxx是某模块的具体构造说明**
将所有的Makerules.xxx添加进来。

15. 再次编译
$ make
提示缺少lib/uart
看来已经进入实质的构建了。

16. 添加lib
**${src-dir}/src/kernel/fiasco/src/lib中全部是各种库的源代码。miniglibc、gzip、uart等等**
将lib全部拷贝

17. 再次编译
$ make
提示没有构建kip.cpp的规则。

18. 添加abi
**${src-dir}/src/kernel/fiasco/src/abi定义了abi，也是实现l4基本对象的所在，fpage，kip，msg都在这里**
将abi全部拷贝。
仿照ppc32添加mips目录，并添加kip-mips.cpp

19. 再次编译
$ make
提示没有构建cpu_mask.cpp的规则。_

20. 添加kern
**${src-dir}/src/kernel/fiasco/src/kern在abi的基础上，kern中的代码具有相对宽松的环境，此处实现了全部的内核对象**
将kern全部拷贝。
注意，bsp也在这里。

21. 再次编译
$ make
提示没有构建startup-mips.cpp的规则。

22. 添加startup-mips.cpp
**${src-dir}/src/kernel/fiasco/src/kern/xxx/startup-xxx.cpp**
根据ppc32添加startup-mips.cpp。startup分为两步。

23. 再次编译
$ make
提示没有构建boot_info-mips.cpp的规则。

24. 添加boot_info-mips.cpp
**${src-dir}/src/kernel/fiasco/src/kern/xxx/boot_info-xxx.cpp**
根据ppc32添加。

25. 再次编译
$ make
提示没有构建boot_info-loongson1b.cpp的规则。

26. 添加boot_info-loongson1b.cpp
**${src-dir}/src/kernel/fiasco/src/kern/xxx/bsp/yyy/boot_info-yyy.cpp**
根据ppc32/mpc52xx添加。

27. 再次编译
$ make
提示没有构建mappint-mips.cpp的规则。

肩宽35
胸围75
袖长25
身长47
腿长17

