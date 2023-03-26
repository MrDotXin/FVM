<style> body {background-color : rgb(30, 32, 50) !important} </style>

## <font face= "楷体" size=5 color=white>FVM Beta0.1 design</font>
#### <font face= "楷体" size=4 color=white>流程模板的实现</font>
- <font face= "楷体" size=3 color=white>主流程模板</font>
    <font face= "楷体" size=3 color=white>
    <pre><font face= "楷体" size=5 color=white>场景流程(scene)</font>
        [1]. 加载动画
        [2]. 美味镇(地图)
        [3]. 其他场景(暂时仅美味岛， 火山岛, 以及战斗场景等) 
    </font>
-----------------------------
- <font face= "楷体" size=3 color=white>控件设计</font>
    <font face= "楷体" size=3 color=white>
    <pre><font face= "楷体" size=5 color=white>控件(FVMPolyCtrl)</font>
        [1]. 加载框
        [2]. 物品获取框
        [3]. 场景切换机关
        [4]. 物品存储框
        [5]. 功能性按钮
        [6]. 主窗口框
    </font>
-----------------------------
- <font face= "楷体" size=3 color=white>场景模板</font>
    <font face= "楷体" size=3 color=white>
    <pre><font face= "楷体" size=5 color=white>场景类(scene)</font>
        [1].状态
            <font face= "楷体" size=2 color=white>[1]. 载入时</font>
                <font face= "楷体" size=1 color=white>载入的切换动画, 获取必要状态信息</font>
            <font face= "楷体" size=2 color=white>[2]. 运行中</font>
                <font face= "楷体" size=2 color=white>利用状态函数</font>
            <font face= "楷体" size=2 color=white>[3]. 结束时</font>
                <font face= "楷体" size=2 color=white>结束后一些物品状态，一些析构工作</font>
        [2].场景包含控件与动画
    </font>
---------------------------
- <font face= "楷体" size=3 color=white>初始场景/美味镇</font>
- ![美味镇一览](../../FVM%20Tool/Resource_Accumulation/metaPic/1.png)
 