# Qt-AeroplaneChess

## 基本信息
### 关于游戏顺序
绿色为1
黄色为2
蓝色为3
红色为4
正常情况下为顺时针

### 关于棋盘的划分

棋盘被我们划分为了三个区域

#### 区域I：飞机场
对应编号：
201-216（绿色）
221-236（黄色）
241-256（蓝色）
261-276（红色）

特性：
1. 扔到六才可以起飞
2. 有序性


####区域II：环形轨道
对应编号：
1-52

划分为三类
1. 同色加四格点（包含3. 转折点（同色由环形轨道转向胜利区的点））
2. 同色加十二格点


#### 区域III：胜利区
对应编号：
61-66（绿色）
71-76（黄色）
81-86（蓝色）
91-96（红色）

特性：
1. 棋子不论方向改变改变与否，都不会退出这个区域，做取模运动

## 游戏基本逻辑设计（基本功能板块）
### 棋子的移动
以知识库的方式，保存了所有的棋子在所有的点上在各种方向下的下一步的移动位置。
### 游戏流程
1. 扔骰子
2. 选择合法的飞机进行移动
3. 判断是否有飞机被吃
4. 判断是否有飞机抵达终点
5. 判断是否有玩家获胜
循环往复直至分出胜负。



