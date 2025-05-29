#pragma once // 確保檔案只被包含一次

#include <SFML/Graphics.hpp> // 引入SFML圖形函式庫

// 定義座標結構
struct Point
{
    int x; // x座標
    int y; // y座標
};

// 定義方塊類別
class Block
{
public:
    Block(); // 建構子
    void setShape(int shape); // 設定方塊形狀
    void rotate(); // 旋轉方塊
    void move(int dx); // 水平移動
    void drop(); // 下降一格
    Point points[4]; // 方塊目前的四個方塊位置
private:
    int shapeIndex; // 目前形狀索引
};

