#include <SFML/Graphics.hpp> // 引入SFML圖形函式庫
#include "Block.h" // 引入Block類別

using namespace sf; // 使用sf命名空間

const int M = 20; // 遊戲場地高度
const int N = 10; // 遊戲場地寬度

int field[M][N] = {0}; // 代表場地的二維陣列

// 檢查方塊是否在有效範圍內且不與既有方塊衝突
bool check(const Block &b)
{
    for (int i = 0; i < 4; ++i) // 檢查四個方塊
    {
        int x = b.points[i].x; // 取得x
        int y = b.points[i].y; // 取得y
        if (x < 0 || x >= N || y >= M) // 超出邊界
            return false; // 回傳失敗
        if (field[y][x]) // 該處已有方塊
            return false; // 回傳失敗
    }
    return true; // 檢查通過
}

int main()
{
    RenderWindow window(VideoMode(320, 480), "Tetris"); // 建立視窗
    Texture t; // 宣告材質
    t.loadFromFile("tiles.png"); // 讀取方塊圖片
    Sprite s(t); // 建立精靈
    s.setTextureRect(IntRect(0, 0, 18, 18)); // 設定紋理範圍

    Block current; // 目前操控的方塊
    Block backup; // 備份方塊用來測試
    float timer = 0; // 計時器
    float delay = 0.3f; // 下降間隔
    Clock clock; // 時鐘

    int dx = 0; // 水平位移值
    bool rotateFlag = false; // 是否旋轉

    while (window.isOpen()) // 主迴圈
    {
        float time = clock.getElapsedTime().asSeconds(); // 取得經過時間
        clock.restart(); // 重啟時鐘
        timer += time; // 累計時間

        Event e; // 宣告事件
        while (window.pollEvent(e)) // 處理事件
        {
            if (e.type == Event::Closed) // 關閉視窗事件
                window.close(); // 關閉視窗
            if (e.type == Event::KeyPressed) // 有按鍵被按下
            {
                if (e.key.code == Keyboard::Up) // 上鍵旋轉
                    rotateFlag = true; // 設定旋轉
                else if (e.key.code == Keyboard::Left) // 左鍵
                    dx = -1; // 往左移動
                else if (e.key.code == Keyboard::Right) // 右鍵
                    dx = 1; // 往右移動
            }
        }

        if (Keyboard::Down.isPressed) // 按住下鍵
            delay = 0.05f; // 加快下降
        else
            delay = 0.3f; // 回到正常速度

        backup = current; // 備份方塊
        current.move(dx); // 移動方塊
        if (!check(current)) // 檢查是否可移動
            current = backup; // 無效則還原

        if (rotateFlag) // 若需要旋轉
        {
            backup = current; // 備份
            current.rotate(); // 嘗試旋轉
            if (!check(current)) // 失敗則還原
                current = backup; // 還原
        }

        if (timer > delay) // 到達下降時間
        {
            backup = current; // 備份
            current.drop(); // 方塊下降
            if (!check(current)) // 檢查是否可下降
            {
                for (int i = 0; i < 4; ++i) // 將方塊固定到場地
                {
                    int x = backup.points[i].x; // 取得x
                    int y = backup.points[i].y; // 取得y
                    field[y][x] = 1; // 標記場地
                }
                current.setShape(rand() % 7); // 產生新的方塊
            }
            timer = 0; // 重設計時器
        }

        dx = 0; // 重設水平移動
        rotateFlag = false; // 重設旋轉旗標

        window.clear(Color::White); // 清空畫面

        for (int i = 0; i < M; ++i) // 繪製已固定的方塊
            for (int j = 0; j < N; ++j)
                if (field[i][j])
                {
                    s.setPosition(j * 18, i * 18); // 設定位置
                    window.draw(s); // 畫出方塊
                }

        for (int i = 0; i < 4; ++i) // 繪製目前方塊
        {
            s.setPosition(current.points[i].x * 18, current.points[i].y * 18); // 設定位置
            window.draw(s); // 畫出方塊
        }

        window.display(); // 顯示畫面
    }

    return 0; // 程式結束
}

