# Features

* 實作 Camera 與 CamShift 結合，達到即時測試 MeanShift algorithm 的即時效果

* 先將影像轉換成 HSV 顏色域後，抽取 Hue channel 以及以 calcbackproject 方式算出機率圖後，
利用 MeanShift algorithm 追蹤機率最密集的區域，並回傳 Rectangle(追蹤位置)


# Screenshots

![image](https://github.com/Chien-Mu/MeanShift-tracking/blob/master/resource/1.gif)


# Usage

先按 Ctrl + S 就會出現截除視窗，讓使用者以滑鼠左鍵垃取 ROI，選取追蹤物體



***

# What is MeanShift algorithm ?

>mean shift 主要用於 cluster analysis(集群分析)
>但並非一次到位，會有個 kernel 在移動
>
>一開始 kernel 位於一個大概位置(有白點的位置，但不需要太多)
>若一開始的位置處於沒有任何白點，將無法移動
>
>移動方向為，往 kernel 中 density(密度)最高的地方移動
>就這樣重複步驟 計算密度 > 移動 > 計算密度 > 移動
>
![image](https://github.com/Chien-Mu/MeanShift-tracking/blob/master/resource/meanshift%20algorithm.png)
