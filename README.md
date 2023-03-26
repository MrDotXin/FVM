<style>body { background-color: rgb(30, 32, 36) !important}</style>
## <font face="微软雅黑" color=white>Food Versus Mouse Project</font>

-------------------------
<font face="微软雅黑" size=4 style="color: rgb(255,85,85)">Basic info generalization :</font>
<table><tr><td>
<font face="楷体" size=4 
    style="color: lightyellow">
    <pre>
    项目名称 : 美食大战老鼠模板性开发与重置
    开发平台 : windows              |         目前仅支持Windows未来可进入安卓系统                        
    开发工具 : cmake                |         基本利用cmake构建项目
    工程周期 : 1.31 - INFINITY
</font></table></tr></td>

#### <font face = "黑体" color=white>功能需求</font>
##### <font face = "微软雅黑" style="color: rgb(224,108,108)" >v0.1beta版本信息</font>

<table><tbody>
    <tr>
        <th><font face="楷体" color=white size=4>要点</font></th>
        <th><font face="楷体" color=white size=4>具体版本实现Beta0.1</font></th>
    </tr>
    <tr>
        <td bgcolor=""><font face="楷体" color=white size=4>游戏内行为</font></td>
        <td></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>流程模板</font></td>
        <td><font face="楷体" color=white size=4>状态机模型:包括主流程，关卡流程，玩家交互流程</font></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>系统</font></td>
        <td><font face="楷体" color=white size=4>包括货币系统, 关卡内物体回收系统, 等级系统(包括物品，人物等级等)</font></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>场景模板</font></td>
        <td><font face="楷体" color=white size=4>包括场景行为，场景可获取物, 场景交互行为，场景样式</font></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>关卡模板</font></td>
        <td><font face="楷体" color=white size=4>包括关卡开始提供状态，结束提供状态，中间提供状态</font></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>物品设计模板</font></td>
        <td><font face="楷体" color=white size=4>包括物品可交互性，可联动状态，具体属性</font></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>物体设计模板</font></td>
        <td><font face="楷体" color=white size=4>包括物体行为，物体属性，物体各状态样式，物体可交互性，可联动状态</font></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>游戏控件</font></td>
        <td></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>图像类</font></td>
        <td></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>Ai与识别模板</font></td>
        <td><font face="楷体" color=white size=4>包括操纵物体行为训练集, 素材获取， 游戏内识别</font></td>
    </tr>
    <tr>
        <td><font face="楷体" color=white size=4>图像处理</font></td>
        <td><font face="楷体" color=white size=4>包括游戏内图像处理及外部导入图像处理</font></td>
    </tr>

</table>

------------------------

#### <font face="华文中宋" size=4 color=white >1.2 ：非功能性场景的一般设计 </font>

<table><tr><td>
    <font face="华文中宋" size=3 color=white>基本应用</font>
        <font face = "楷体" size=3 color=white>
            <pre>
            后台类  
            <font face = "楷体" size=3 color=lightyellow>          
                [1]. 收集器(FVMItemCollector)
                [2]. 对象内存管理池[内存池](FVMMemoryPool)
                [3]. 并发任务管理器[线程池](FVMThreaPool)
                [4]. 进度(process_manager)
                [5]. 状态机模型(FVMStateMechine) 
                [6]. 对象数据管理(FVMObjectHeap)
                [7]. 
            </font>
            交互类
            <font face = "楷体" size=3 color=lightyellow>
                [1]. "下棋"操作(FVMCheckerBoardEvent)
                [2]. "选棋"操作(FVMPiecesSelector)
                [3]. "撤棋"操作(FVMItemCollector)
            </font>
        </font>
</table><tr><td>
