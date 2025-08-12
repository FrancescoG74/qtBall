#include "../include/ball.h"
#include <QtMath>
#include <QVector2D>

Ball::Ball(qreal x, qreal y, qreal vx, qreal vy, qreal radius)
    : m_position(x, y), m_velocity(vx, vy), m_radius(radius) {}

void Ball::updatePosition(int width, int height) {
    m_position += m_velocity;
    // Example boundary check:
    if (m_position.x() - m_radius < 0 || m_position.x() + m_radius > width)
        m_velocity.setX(-m_velocity.x());
    if (m_position.y() - m_radius < 0 || m_position.y() + m_radius > height)
        m_velocity.setY(-m_velocity.y());
}

QPointF Ball::position() const {
    return m_position;
}

QPointF Ball::velocity() const {
    return m_velocity;
}

void Ball::invertVelocity() {
    m_velocity = -m_velocity;
}

void Ball::invertVelocity(const QPointF& normal, qreal n1, qreal n2) {
    // Convert velocity and normal to QVector2D for easier math
    QVector2D v(m_velocity);
    QVector2D n(normal);
    n.normalize();

    // Snell's law: n1 * sin(theta1) = n2 * sin(theta2)
    // We'll scale the normal component by n1/n2 to simulate refraction
    qreal v_dot_n = QVector2D::dotProduct(v, n);
    QVector2D v_n = v_dot_n * n;         // normal component
    QVector2D v_t = v - v_n;             // tangential component

    QVector2D v_n_new = (n1 / n2) * v_n; // scale normal component
    QVector2D v_new = v_t + v_n_new;

    m_velocity = v_new.toPointF();
}

bool Ball::checkCollision(const Ball& other) const {
    qreal dx = m_position.x() - other.m_position.x();
    qreal dy = m_position.y() - other.m_position.y();
    qreal distance = qSqrt(dx * dx + dy * dy);
    return distance < (m_radius + other.m_radius);
}

QRectF Ball::boundingRect() const {
    return QRectF(m_position.x() - m_radius,
                  m_position.y() - m_radius,
                  2 * m_radius,
                  2 * m_radius);
}

void Ball::setRadius(qreal radius) {
    m_radius = radius;
}

void Ball::setVelocity(const QPointF& v) { m_velocity = v; }
void Ball::setPosition(const QPointF& p) { m_position = p; }

// Added code based on user prompt
void Ball::handleCollision(Ball& other, qreal n1, qreal n2) {
    QPointF normal = m_position - other.m_position;
    invertVelocity(normal, n1, n2);
    other.invertVelocity(-normal, n2, n1);
}