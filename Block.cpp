#include "Block.h" // 引入方塊標頭

using namespace sf; // 使用sf命名空間

// 所有七種方塊的定義
static const int figures[7][4] = {
    {1,3,5,7}, // I 形狀
    {2,4,5,7}, // Z 形狀
    {3,5,4,6}, // S 形狀
    {3,5,4,7}, // T 形狀
    {2,3,5,7}, // L 形狀
    {3,5,7,6}, // J 形狀
    {2,3,4,5}  // O 形狀
};

Block::Block() // 建構子實作
{
    setShape(0); // 預設設定為第一種形狀
}

void Block::setShape(int shape) // 設定方塊形狀
{
    shapeIndex = shape; // 儲存形狀索引
    for (int i = 0; i < 4; ++i) // 依序設定四個方塊的位置
    {
        points[i].x = figures[shapeIndex][i] % 2; // 由索引計算x座標
        points[i].y = figures[shapeIndex][i] / 2; // 由索引計算y座標
    }
}

void Block::rotate() // 旋轉方塊
{
    Point p = points[1]; // 以第二個方塊為中心點
    for (int i = 0; i < 4; ++i) // 處理四個方塊
    {
        int x = points[i].y - p.y; // 旋轉公式計算x
        int y = points[i].x - p.x; // 旋轉公式計算y
        points[i].x = p.x - x; // 更新x座標
        points[i].y = p.y + y; // 更新y座標
    }
}

void Block::move(int dx) // 水平移動
{
    for (int i = 0; i < 4; ++i) // 逐一處理四個方塊
    {
        points[i].x += dx; // x座標加上偏移量
    }
}

void Block::drop() // 讓方塊下降一格
{
    for (int i = 0; i < 4; ++i) // 逐一處理四個方塊
    {
        points[i].y += 1; // y座標加一
    }
}

