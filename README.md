數位影像處理(RGB)
======

### 目錄

```
數位影像種類 :                            影像基本概念 :                    基礎影像處理 :

1. 灰階影像                                1. 二維轉一維                    1. 低通濾波

2. 全彩圖象                                2. 平面格式                      2. 高通濾波

3. 二值影像                                3. 交錯格式                      3. 中值濾波

4. 負片影像                                4. 陣列暫存器                    4. Sobel

                                                                           5. 邊緣銳利化

                                                                           6. 值方圖均衡化

```

### 灰階影像(Gray-Level-Image)

+ 以8bit的數值代表一個像素(Pixel)，其中黑色為0，白色為255

+ 不過人眼對於三種色彩亮度都感受不同，感受度大到小分別為紅(R)、綠(G)、藍(B)

+ 為了得到適合人眼灰階相片，在影像辨識有了彩色轉灰階標準，分別將顏色乘上不同權重

```
R * 0.299 + G * 0.587 + B * 0.114

```

### 全彩影像

+ 顏色亮度可以由0 ~ 255表示，有R、G、B三種色光，依照三原色色光不同比例相加，可產生多種色光

### 二值影像(Binary Image)

+ 只會有兩個顏色(黑跟白)，0代表黑，1代表白

+ 目的在區分前景與背景或是簡化處理運算

+ 使用1bit紀錄每個灰階值

### 負片影像(Invert Image)

+ 實際上即為明亮與色調皆為和原來物景相反負像影像

+ 影像反轉(將原始影像數值利用255去做三原色相減，可使顏色反轉)

### 二維轉一維

+ 一維 = X + Y*寬度

### 平面格式

+ 分別將R、G、B放入不同陣列，針對三種元素用3個矩陣儲存

```
EX : 512 * 512 pixel

R[512][512]
G[512][512]
B[512][512]
```

### 交錯格式

+ 將R、G、B交錯存放一起

```
EX : 512 * 512 pixel

RGB[512][512*3]

R、G、B、R、G、B、R、G、B、R、G、B、R、G、B延續下去
```

### 低通濾波器(Low Pass Filters, LPF)

+ 保持低頻率部分，減少或消除高頻率部分的濾波器，又稱為平均濾波器(averaging filters)

+ 特點 :

    + 消除高頻雜訊

    + 柔化影像

    + 缺點使影像變模糊

```
    21 19 17 25 28          計算3*3遮罩數值
    71 76 73 68 59
    15 13 14 15 65
    20 98 52 77 63
    45 88 97 55 74

    21 :(21 + 19 + 17 + 71 + 76 + 73 + 15 + 13 + 14) / 9

    19 :(19 + 17 + 25 + 76 + 73 + 68 + 13 + 14 + 15) / 9

    17 :(17 + 25 + 28 + 73 + 68 + 59 + 14 + 15 + 65) / 9

    25 :不足的數直接補0，或直接忽略做下一行
```

### 高通濾波器(High Pass Filters, HPF)

+ 保持高頻率部分，減少或消除低頻率部分的濾波器

+ 特點 

    + 留下影像邊緣，其餘被捨棄

+ 將隔壁兩數數值相減取得顏色變化

```
    21 19 17 25 28         
    71 76 73 68 59
    15 13 14 15 65
    20 98 52 77 63
    45 88 97 55 74

    21 :abs(19-0)
    
    19 :abs(17-21)

    17 :abs(25-19)

    25 :abs(28-17)

    28 :abs(0-25)
```