#ifndef SCANING_EFFECT_LABEL_H
#define SCANING_EFFECT_LABEL_H

#include <QLabel>
#include <QShowEvent>
#include <QHideEvent>
#include <QPaintEvent>
#include <QTimer>

class ScaningEffectLabel : public QLabel
{
public:
    ScaningEffectLabel( QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags() );

protected:
    void showEvent( QShowEvent *event );
    void hideEvent( QHideEvent *event );
    void paintEvent( QPaintEvent *event );

private:
    int cycleSample( const int min, const int max, int *curValue, int *direction, const int step = 1 );

private:
    int m_width, m_width_direction;
    int m_y, m_y_direction;
    qreal m_roration;
    QTimer m_timer;
    QPixmap m_circle, m_line;
};

#endif // SCANING_EFFECT_LABEL_H
