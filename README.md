# 基于两方安全计算的LSTM算法的实现
## 具体功能
本项目实现了智能电网中隐私保护的短期个人负载预测服务，即根据输入的一系列时间点的用户用电量数据，预测用户未来的用电量。
## 项目结构
1. `data`目录：为训练及测试用的明文数据集，一共有5个`csv`文件。
2. `src`目录：项目源码。
## 编译项目
安装依赖：
```bash
sudo apt update
sudo apt install build-essential cmake make git libgmp-dev -y
```
克隆项目：
```bash
git clone https://github.com/qiuqingyun/lstm.git
cd lstm
```
编译：
```bash
mkdir build && cd build
cmake .. && make
```
生成的可执行文件在`lstm/bin`目录中。
