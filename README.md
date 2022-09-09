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

+ 3*3遮罩乘1/9等於1
```
做法 :
        先建立一個大於512*512的二維陣列，為514*514，初始值全部都放0，將512*512陣列丟入514*514陣列下去做運算最後將
        結果寫回512*512陣列中

    21 19 17 25 28              3*3遮罩數值
    71 76 73 68 59              
    15 13 14 15 65              1 1 1
    20 98 52 77 63              1 1 1  * (1/9)
    45 88 97 55 74              1 1 1      

    21 :(0 + 0 + 0 + 0 + 21 + 19 + 0 + 71 + 76) / 9

    19 :(0 + 0 + 0 + 21 + 19 + 17 + 71 + 76 + 73) / 9

    17 :(0 + 0 + 0 + 19 + 17 + 25 + 76 + 73 + 68) / 9

    25 :(0 + 0 + 0 + 17 + 25 + 28 + 73 + 68 + 59) / 9

    28 :(0 + 0 + 0 + 25 + 28 + 0 + 68 + 59 + 0) / 9
```

### 高通濾波器(High Pass Filters, HPF)

+ 保持高頻率部分，減少或消除低頻率部分的濾波器

+ 特點 

    + 留下影像邊緣，其餘被捨棄

+ 3*3遮罩相加等於0
```
做法 :
        先建立一個大於512*512的二維陣列，為514*514，初始值全部都放0，將512*512陣列丟入514*514陣列下去做運算最後將
        結果寫回512*512陣列中，如果陣列中的值小於0那就等於0


    21 19 17 25 28          3*3遮罩數值
    71 76 73 68 59
    15 13 14 15 65          1   1  1
    20 98 52 77 63          1  -8  1
    45 88 97 55 74          1   1  1

    21 :(1 + 1 + 1 + 1 + 21 * (-8) + 19 + 1 + 71 + 76)

    19 :(1 + 1 + 1 + 21 + 19 * (-8) + 17 + 71 + 76 + 73) 

    17 :(1 + 1 + 1 + 19 + 17 * (-8) + 25 + 76 + 73 + 68)

    25 :(1 + 1 + 1 + 17 + 25 * (-8) + 28 + 73 + 68 + 59)

    28 :(1 + 1 + 1 + 25 + 28 * (-8) + 1 + 68 + 59 + 0)

```

### 中值濾波器

+ 透過中值濾波器能濾除影像上的胡椒鹽雜訊(salt-and-pepper noise)， 同時保留原圖像的畫質

+ 以三乘三遮罩來說，將其排序後取中間值更新數值

+ 以下3種取其中間值遮罩方法

    + 快速排序法 :取其中一個數值，將大於其數值放右邊，小於其數值放左邊，目前快速排序法是公認排序最快的排序法，時間複
    雜度為O(N*logN)，是一種不穩定排序法

    + 泡沫排序法 :將第一個值與其他數值做比較，若比其他數值大，將其swap，比完第一個數值後接下來將第二個數值與其他做比
    較直到完成比較，時間複雜度為O(N^2)，是穩定排序法

    + 分行求中間值 :將第一行數值做比較取中間值A，第二行數值做比較取中間值B，第三行數值取中間值C，再將A和B和C取中間值
    得出答案

```
做法 :
        先建立一個大於512*512的二維陣列，為514*514，初始值全部都放0，將512*512陣列丟入514*514陣列下去做運算最後將
        結果寫回512*512陣列中

    21 19 17 25 28         計算3*3遮罩數值
    71 76 73 68 59
    15 13 14 15 65          0 0 0
    20 98 52 77 63          0 0 0
    45 88 97 55 74          0 0 0


    21 : 0、0、0、0、0、19、21、71、76 = 0

    19 : 0、0、0、17、19、21、71、73、76 = 19

    17 : 0、0、0、17、19、25、68、73、76 = 19

    25 : 0、0、0、17、25、28、59、68、73 = 25

    28 : 0、0、0、0、0、25、28、59、68 = 0
```


### Sobel Filter

+ 在影像處理及電腦視覺領域中常被用來做邊緣檢測，透過Sobel濾波器能提取影像中的邊緣資訊

```
作法 :
        建立兩個遮罩 -1  0  1  和   -1  -2  -1 將數值與遮罩做運算取絕對值後相加更新，若數值大於255則讓該點等於255
                    -2  0  2        0   0   0                                                 
                    -1  0  1        1   2   1


```     

### 邊緣銳利化

+ 圖像的邊緣或線條的細節部分與圖像的高頻分量相對應，因此採用高通濾波讓高頻分量順利通過，並適當抑制中低頻分量，使圖像
的邊緣、輪廓線以及圖像的細節變得清晰

+ 3*3遮罩相加等於1
```
作法 :
        先建立一個大於512*512的二維陣列，為514*514，初始值全部都放0，將512*512陣列丟入514*514陣列下去做運算最後將
        結果寫回512*512陣列中

        自行設定3*3遮罩
        -1 -1 -1                                        
        -1  9 -1 ----->所有邊緣做運算        
        -1 -1 -1                            


        0 -1  0
       -1  5 -1  ----->以中心點上下左右做運算
        0 -1  0

        0  0  0
       -1  3 -1------>以中心點左右做運算
        0  0  0
```

### 直方圖均衡化

+ 主要目的是將**原始圖像的色彩強度均勻地映射到整個色彩範圍內**，得到一個色彩強度分佈均勻的圖像。

```
作法 :

    1. 讀取影像RGB陣列
    
    2. 計算每個亮度數值的總數

    3. 將亮度數值出現次數轉換成機率

    4. 代入公式進行線性分布 [公式 : Y = 255 * (X-Xmin) / (1 - Xmin)]

                                 亮度值   累積值      取百分比            累積百分比        帶入公式
    10 255 7  85  40              0 :       2         2 / 25 = 8%         8%                0         
    40 45  85 125 10              1 :       1         1 / 25 = 4%         12%               11
    45 1   35 40  250             6 :       1         1 / 25 = 4%         16%               22
    78 125 0  6   7               7 :       3         3 / 25 = 12%        28%               55
    85 68  7  0   10              10 :      3         3 / 25 = 12%        40%               88
                                  35 :      1         1 / 25 = 4%         44%               100
                                  40 :      3         3 / 25 = 12%        56%               133
                                  45 :      2         2 / 25 = 8%         64%               155
                                  68 :      1         1 / 25 = 4%         68%               166
                                  78 :      1         1 / 25 = 4%         72%               177
                                  85 :      3         3 / 25 = 12%        84%               211
                                  125 :     2         2 / 25 = 8%         92%               233
                                  250 :     1         1 / 25 = 4%         96%               244
                                  255 :     1         1 / 25 = 4%         100%              255
```
