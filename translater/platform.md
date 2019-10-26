# 平台设备和驱动

      对于平台总 （ 平台设备，平台驱动 ） 的驱动模型接口 ，你能够查看文件 <linux/platform_device.h> ，
    这种虚拟总线以最小的开销来连接总线上的设备 。类似于 SOC 的外部集成总线或是传统 PC 的连接方式 。
    相当于正式指定的 PCI 和 USB 。

## 平台设备

    平台设备是在系统中通常作为自主的实体出现的设备 。 包含了传统基于端口的设备 ，外围总线的北桥 ， 集成
    进 SOC 平台的大部分控制器 。它们最大的相同处是能够通过 CPU 总线进行直接寻址 。 少量情况下 ，平台设备
    会与其他总线的一部分连接 。但是他的寄存器任然是可以直接寻址的.

    平台设备会用一个名称用于驱动的绑定，同样也会有其他的资源，例如地址和中断. 

    struct platform_device {
    const char      *name;
    u32             id;
    struct device   dev;
    u32             num_resources;
    struct resource *resource;
    };


## 平台驱动

    平台驱动遵守标准的驱动模块准则, 驱动的发现和枚举在驱动外部完成, 驱动本身提供 probe() 和 remove() 方法.
    它们使用标准协议来支持电源管理和关机通知.

    struct platform_driver {
    int (*probe)(struct platform_device *);
    int (*remove)(struct platform_device *);
    void (*shutdown)(struct platform_device *);
    int (*suspend)(struct platform_device *, pm_message_t state);
    int (*suspend_late)(struct platform_device *, pm_message_t state);
    int (*resume_early)(struct platform_device *);
    int (*resume)(struct platform_device *);
    struct device_driver driver;
    };

    probe() 应该检测指定的硬件设备的存在状态 ，某些时候平台的配置代码不能确认 ， 能够使用设备资源，包含 时钟，
    和设备的 platform_data.


### 平台驱动注册的普通方法:

    int platform_driver_register(struct platform_driver *drv);

    或者在其他普遍的情况下，当设备不能够热拔插，probe () 能够放置带初始化部分，这样会减小驱动的运动内存。

    int platform_driver_probe(struct platform_driver *drv,
                              int (*probe)(struct platform_device *))


    内核模块可以由数个平台驱动组成, 平台核心提供批量注册和注销.

    int __platform_register_drivers(struct platform_driver * const *drivers,
                unsigned int count, struct module *owner);

    void platform_unregister_drivers(struct platform_driver * const *drivers,
             unsigned int count);

    如果其中一个驱动注册失败，所有已经注册的驱动会以反方向注销。下面是一个便利的宏将 THIS_MODULE 作为所有者参数传递.

    #define platform_register_drivers(drivers, count)


## 设备枚举

    特定于平台（通常是特定于主板）的配置代码将注册平台设备: 

    int platform_device_register(struct platform_device *pdev);

        通常来说，只有是真实存在的设备会被注册。但在一些情况下，额外的设备也有可能被注册。举个例子，内核能够以外部的网络适配
    器工作，而适配器不是所有的板子上都会安装。或者是类似于有些板子是有一些集成控制器工作的，但没有任何外部设备挂载。

        在某些情况下，引导固件会导出描述指定板的设备表。如果没有这张表，系统配置代码配置正确的设备的唯一方法是在编译内核时选择
    特定的目标板。这种板定制的内核在嵌入式和定制开发的系统中非常常见。

    在一些情况下，分配给平台设备的内存和中断资源可能不足以让设备的驱动工作，板载配置代码用 platform_data 数据域来提供额外的信息。

        嵌入式系统通常需要一个多个时钟用于平台设备，在它们被激活前都是关闭的（省电）。但是系统仍然会给设备分配时钟，用函数 clk_get 
    (&pdev->dev, clock_name) 来获取需要的时钟。


## 传统驱动：设备探测

        一些驱动没有完全转换为驱动模型，因为它扮演了非驱动角色: 驱动注册它自己的平台设备，而不是把注册的动作留给系统的基础设施。这样的
    驱动不支持热插拔和冷插拔 ，因为这些机制要求设备创建和驱动位于不同的设备组件 。

        这样做的唯一理由是兼容老旧的系统设计，像老式的 IBM PC，依赖易错的　"硬件探测"来配置硬件。新系统基本放弃了这种模式，支持总线级别的自
    动配置 (PCI, USB) ，或者是引导固件提供的设备表 (X86 上的 PNPACPI ) 。怎么做，以及在哪做有许多冲突的选择，即使操作系统依照经验也会选择错
    误而导致麻烦 。

        这种驱动风格是不被鼓励的 。如果你正在更新这样的一个驱动 ，请尝试将设备枚举放置到一个更为适合的区域 (在驱动之外)　。当驱动将有使用由 
    PNP 或者平台设备配置创建的设备节点的正常的模式后 ，这将被清除.

    仍然有许多 API 来支持传统的驱动 ，避免使用这些除了那些不支持热拔插的驱动　。

    struct platform_device *platform_device_alloc(
                                                  const char *name, int id);

        你能够使用　platform_device_alloc() 来动态的分配设备 ，然后用资源和 platform_device_register ()　函数来初始化分配的设备 ，更好的解决
    方案通常是 :

    dynamically struct platform_device *platform_device_register_simple(
                                                                        const char *name, int id,
                                                                        struct resource *res, unsigned int nres);

    你能够用 platform_device_register_simple () 来代替分配和注册设备.


### 设备命名和驱动绑定

    platform_device.dev.bus_id 　是设备的标准名称, 右下面的两个部分组成:
    * platform_device.name ... 同时也用于驱动匹配

    * platform_device.id ...   设备的实体名　，-1 代表这只有一个


        上面的这些是可以串联的 ，用 name/id 来表示 , "serial"/0　表示 "serial.0" , "serial"/3　表示　bus_id 为　"serial.3"　。前面的收拾使用 
    platform_device "serial"　，　"my_rtc"/-1 表示 bus_id 为 "my_rtc" (没有实例名)　使用的 platform_driver 叫　"my_rtc"

        驱动核心自动执行驱动绑定绑定 ， 在发现一对匹配的驱动和设备后　，调用驱动的 probe() 。当　probe() 成功执行后 ，驱动和设备照常绑定。有
    三种不同方式来发现匹配.

    - 一旦设备完成注册，总线的驱动会检车匹配。平台设备会在系统启动的时候完成注册。

    - 当一个驱动用　platform_driver_register() 来完成注册，总线上没有绑定的设备会检查匹配。驱动通常在引导后或者模块导入中完成注册。

    - 用 platform_driver_probe () 注册一个驱动和使用 platform_driver_register ()相同，但是当其他设备注册的时候就不会在探测了 。(当这个接口只
      是给一个非热拔插的设备)


## 早先的平台设备和驱动

    在系统启动的早期，早先的平台接口提供平台数据和平台设备驱动。该代码构建于命令行解析之上 (early_param ()), 能够在很早的执行.

### 1. 早期的平台设备数据注册 

        架构代码使用 early_platform_add_devices () 来注册平台设备数据 . 在这总情况下串口控制台，这应该用于串口的硬件配置 。此时注册的设备稍后将
    与早期的设备驱动进行匹配。

### 2. 解析内核命令行

        结构代码用 parse_early_param () 来解析内核命令行 。将执行所有匹配early_param () 的回调 。用户指定的早期平台设备将会在此处被注册。对于早先
    的串口控制台的情况 ，用户能够使在内核命令行中使用 "earlyprintk=serial.0"指定端口. "serial" 是平台设备驱动的名称，0 是平台设备的设备 ID. 如果id
    为 -1 , 点和id可以省略。

### 3. 安装属于某一类的平台设备驱动

        架构代码能够使用 early_platform_driver_register_all () 函数来强制注册属于某一类的平台驱动。 对于这些，步骤2中用户所指定的设备有优先
    优先权。串口驱动中这一步应当被忽略，例如，除非用户在内核命令行中指定了端口，早期的串口驱动应当是关闭的。

### 4. 早期的平台驱动注册

        在步骤 2 和步骤 3 中使用 early_platform_init () 来自动注册内建的的平台驱动。串口驱动的例子应当使用  early_platform_init ("earlyprintk", 
    &platform_driver)


### 5. 探测属于某一类的平台驱动

        架构代码调用 early_platform_driver_probe () 来匹配已经注册相关类的平台设备. 已经匹配的设备会获取到 probed()　，这一步能够在启动的早期的任意时
    刻执行 。　对于串口来说，越早越好。

### 6. 早期平台驱动的 probe () 的内部

        在启动的早期，驱动代码应当注意一些特别小心，尤其是涉及到内存分配和中断注册 。probe () 的代码能够调用 is_early_platform_device () 来判断自身
    处于早期平台设备还是常规的平台设备。早期窗口驱动在此时执行  register_console () 

在文件 <linux/platform_device.h> 查看更多的信息

