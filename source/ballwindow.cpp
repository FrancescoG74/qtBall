#include "../include/ballwindow.h"
#include "../include/ball.h"
#include <QTimer>
#include <QPainter>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QColor>
#include <QApplication>

BallWindow::BallWindow(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this))
{
    setWindowTitle("Moving Balls");
    setFixedSize(800, 600);

    // Create 8 balls with different colors, positions, velocities, and radii
    static const QVector<QColor> ballColors = {
        Qt::red, Qt::blue, Qt::green, Qt::magenta,
        Qt::cyan, Qt::yellow, Qt::gray, Qt::darkRed
    };
    static const QVector<qreal> radii = {40, 20, 60, 25, 30, 18, 22, 28};

    for (int i = 0; i < 8; ++i) {
        qreal x = 100 + 70 * (i % 4);
        qreal y = 100 + 90 * (i / 4);
        qreal vx = (i % 2 == 0) ? 2 + i : -2 - i;
        qreal vy = (i % 2 == 0) ? 3 - i : -3 + i;
        balls.push_back(Ball(x, y, vx, vy, radii[i]));
    }

    connect(timer, &QTimer::timeout, this, &BallWindow::updateBalls);
    timer->start(16); // Approximately 60 FPS
}

void BallWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    static const QVector<QColor> ballColors = {
        Qt::red, Qt::blue, Qt::green, Qt::magenta,
        Qt::cyan, Qt::yellow, Qt::gray, Qt::darkRed
    };

    for (size_t i = 0; i < balls.size(); ++i) {
        painter.setBrush(ballColors[i % ballColors.size()]);
        qreal r = balls[i].boundingRect().width() / 2.0;
        painter.drawEllipse(balls[i].position(), r, r);
    }
}

void BallWindow::updateBalls()
{
    // const qreal gravity = 0.5; // Adjust gravity strength as needed

    for (size_t i = 0; i < balls.size(); ++i) {
        qreal radius = balls[i].boundingRect().width() / 2.0;
        balls[i].setRadius(radius);

        balls[i].updatePosition(width(), height());

        // --- Simpler boundary check and response ---
        QPointF pos = balls[i].position();
        QPointF vel = balls[i].velocity();

        // Left or right wall
        if (pos.x() - radius < 0) {
            pos.setX(radius);
            if (vel.x() < 0) vel.setX(-vel.x());
        } else if (pos.x() + radius > width()) {
            pos.setX(width() - radius);
            if (vel.x() > 0) vel.setX(-vel.x());
        }

        // Top or bottom wall
        if (pos.y() - radius < 0) {
            pos.setY(radius);
            if (vel.y() < 0) vel.setY(-vel.y());
        } else if (pos.y() + radius > height()) {
            pos.setY(height() - radius);
            if (vel.y() > 0) vel.setY(-vel.y());
        }

        balls[i].setPosition(pos);
        balls[i].setVelocity(vel);
    }
    checkCollisions();
    update(); // Trigger a repaint
}

void BallWindow::checkCollisions()
{
    for (size_t i = 0; i < balls.size(); ++i) {
        qreal radius_i = balls[i].boundingRect().width() / 2.0;
        balls[i].setRadius(radius_i);
        for (size_t j = i + 1; j < balls.size(); ++j) {
            qreal radius_j = balls[j].boundingRect().width() / 2.0;
            balls[j].setRadius(radius_j);

            QPointF pos_i = balls[i].position();
            QPointF pos_j = balls[j].position();
            qreal dx = pos_i.x() - pos_j.x();
            qreal dy = pos_i.y() - pos_j.y();
            qreal distance = std::sqrt(dx * dx + dy * dy);

            if (distance < (radius_i + radius_j)) {
                // Calculate the normal and tangent unit vectors
                QPointF normal = (pos_j - pos_i) / distance;
                QPointF tangent(-normal.y(), normal.x());

                // Project velocities onto the normal and tangent directions
                qreal vi_n = QPointF::dotProduct(balls[i].velocity(), normal);
                qreal vj_n = QPointF::dotProduct(balls[j].velocity(), normal);
                qreal vi_t = QPointF::dotProduct(balls[i].velocity(), tangent);
                qreal vj_t = QPointF::dotProduct(balls[j].velocity(), tangent);

                // For equal mass, swap normal components, keep tangential
                qreal vi_n_after = vj_n;
                qreal vj_n_after = vi_n;

                QPointF vi_after = vi_n_after * normal + vi_t * tangent;
                QPointF vj_after = vj_n_after * normal + vj_t * tangent;

                balls[i].setVelocity(vi_after);
                balls[j].setVelocity(vj_after);

                // Optional: separate balls to prevent sticking
                qreal overlap = (radius_i + radius_j) - distance;
                QPointF correction = normal * (overlap / 2.0);
                balls[i].setPosition(pos_i - correction);
                balls[j].setPosition(pos_j + correction);
            }
        }
    }
}

void BallWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}

void BallWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Q) {
        qApp->quit();
    } else {
        QWidget::keyPressEvent(event);
    }
}