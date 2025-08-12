#ifndef BALLWINDOW_H
#define BALLWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include "ball.h"
#include <QWidget>

class BallWindow : public QWidget {
    Q_OBJECT
public:
    explicit BallWindow(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override; // <-- Add this line

    void paintEvent(QPaintEvent *event) override;
    void updateBalls();

private:
    std::vector<Ball> balls;
    QTimer *timer;

    void checkCollisions();
};

#endif // BALLWINDOW_H