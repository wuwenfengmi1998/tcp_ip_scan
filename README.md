# IP端口扫描工具

> 可以批量对IP的端口进行扫描，如果端口是开放的就会展示出来。

支持多种IP列表示方式，例如：
1. 127.0.0.1
2. 192.168.0.1-192.168.0.255
3. 192.168.0.0/24
4. domain.com
支持单个IPv6地址，暂不支持IPv6的批量扫描。

支持多种端口表达方式，例如：
1. 22
2. 80;443
3. 1-65525

## 使用指南

从以下仓库clone项目，由于github在内地无法使用，可在备用仓库clone
* [备用仓库][3]
* [github][4]



### 项目使用条件

Windows下QT版本：
```
Qt5.14.2 mingw73_64
```
目前仅在Windows下开发。

### 打包
cd 到debug输出目录下执行
```
windeployqt ip_sacaner.exe
```

### 使用示例

![tu1](/img/tu1.png)


## 关于作者

* **Kevin Ng** - *Blog* - [Wnfed](https://Wnfed.com)

## License 授权协议

这个项目 MIT 协议， 请点击 [LICENSE.md](LICENSE.md) 了解更多细节。



  [3]: https://git.lmve.net/kevin/tcp_ip_scan
  [4]: https://github.com/wuwenfengmi1998/tcp_ip_scan
