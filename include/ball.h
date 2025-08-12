#ifndef BALL_H
#define BALL_H

#include <QPointF>
#include <QRectF>

class Ball {
public:
    Ball(qreal x, qreal y, qreal vx, qreal vy, qreal radius);

    void updatePosition(int width, int height);
    bool checkCollision(const Ball& other) const;
    void invertVelocity();
    void invertVelocity(const QPointF& normal, qreal n1, qreal n2);
    QRectF boundingRect() const;

    QPointF position() const;
    QPointF velocity() const;
    void setRadius(qreal radius);
    void setVelocity(const QPointF& v);
    void setPosition(const QPointF& p);

    void handleCollision(Ball& other, qreal n1, qreal n2);

private:
    QPointF m_position;
    QPointF m_velocity;
    qreal m_radius;
};

#endif // BALL_H