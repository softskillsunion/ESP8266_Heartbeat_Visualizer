# 物聯網遠端記錄心率血氧濃度儀
## 外殼組裝
[![](https://i.imgur.com/0jMqmDA.jpg)](https://i.imgur.com/0jMqmDA.jpg)

[![](https://i.imgur.com/UTE4DWT.jpg)](https://i.imgur.com/UTE4DWT.jpg)

竹籤稍作打磨後切 6.5~7mm * 3
![](https://i.imgur.com/4v7WX2T.jpg)

竹籤切 7mm * 3
![](https://i.imgur.com/yCDntEf.jpg)

## SSU Mini 開發板製作
[![](https://i.imgur.com/mIsI2On.jpg)](https://i.imgur.com/mIsI2On.jpg)

[![](https://i.imgur.com/cKUMcde.jpg)](https://i.imgur.com/cKUMcde.jpg)

[![](https://i.imgur.com/ZzKuhG1.png)](https://i.imgur.com/ZzKuhG1.png)

## 韌體上傳晶片 CH340C 驅動程式
[windows :link:](http://www.wch.cn/downloads/CH341SER_EXE.html)； [MAC :link:](http://www.wch.cn/downloads/CH341SER_MAC_ZIP.html)

## Arduino IDE 設置
### [增加 ESP8266 開發板](http://blog.s2u4o.com/?p=2119)

### 上傳測試
[![](https://i.imgur.com/cwfDk0o.png)](https://i.imgur.com/cwfDk0o.png)

檔案 → 範例 → 01.Basics → Blink

## 電路銲接
### 線路圖
![](https://i.imgur.com/Kusr4LU.jpg)

### 將 SG90 定位至 90 度後，鎖上撥桿
![](https://i.imgur.com/nFrLAkj.jpg)

程式碼
```c=
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
    myservo.attach(15);  // attaches the servo on D8 to the servo object
}

void loop() {
    myservo.write(90);
}
```

## MAX30100 測試
安裝函式庫
草稿碼 → 匯入程式庫 → 管理程式庫 → 輸入 MAX30100lib

上傳函式庫範例
檔案 → 範例 → MAX30100lib → MAX30100_Minimal

## 物聯網三層架構
![](https://i.imgur.com/tTjSoJ5.png)

## 應用程式
### Blynk
* 後端架構
![](https://i.imgur.com/yAQGqrZ.jpg)
* 前端畫面
![](https://i.imgur.com/PaSOgQv.jpg)
* 安裝函式庫
草稿碼 → 匯入程式庫 → 管理程式庫 → 輸入 [Blynk](https://github.com/blynkkk/blynk-library)
* 程式碼
    * GitHub
[setServoDegrees](https://github.com/softskillsunion/setServoDegrees)
    * Git 指令
`git clone https://github.com/softskillsunion/setServoDegrees.git`
    * [下載 rar](https://drive.google.com/file/d/1YkGmGTbp9HG7weS8qql7qDdZapJPsdg4/view?usp=sharing)

## Visual Studio Code & GitHub
1. GitHub 申請
2. Git 安裝
3. Visual Studio Code 設定
    - Git 使用者名稱和信箱
	    - `git config --global user.name "你的帳號"`
	    - `git config --global user.email "你的電子郵件地址"`
    - 查看設定
	    - `git config --list`
	- 建議模組
    ![](https://i.imgur.com/vfsFRm6.png)
    - Git 顯示狀態
        - A - Added (This is a new file that has been added to the repository)
        - M - Modified (An existing file has been changed)
        - D - Deleted (a file has been deleted)
        - U - Untracked (The file is new or has been changed but has not been added to the repository yet)
        - C - Conflict (There is a conflict in the file)
        - R - Renamed (The file has been renamed)
        - S - Submodule (In repository exists another subrepository)

## 組裝完成
