#include "scaning_effect_label.h"
#include <QPainter>
#include <QCoreApplication>
#include <QDebug>

ScaningEffectLabel::ScaningEffectLabel( QWidget *parent, Qt::WindowFlags f )
{
    setParent( parent );
    setWindowFlags( f );

    m_width = 1;
    m_width_direction = 0;
    m_y = 1;
    m_y_direction = 0;
    m_roration = 0;
    connect( &m_timer, SIGNAL(timeout()), this, SLOT(update()) );

    m_circle.load( QCoreApplication::applicationDirPath() + "/circle.png" );
    m_line.load( QCoreApplication::applicationDirPath() + "/line.png" );
}


int ScaningEffectLabel::cycleSample( const int min, const int max, int *curValue, int *direction, const int step )
{
    if ( (nullptr == curValue) || (nullptr == direction) )
    {
        return 1;
    }

    if ( 0 > *direction )
    {
        *direction = 0;
    }

    if ( 1 < *direction )
    {
        *direction = 1;
    }

    if ( min > *curValue )
    {
        *curValue = min;
        *direction = 1;
    }

    if ( max < *curValue )
    {
        *curValue = max;
        *direction = 0;
    }

    if ( *direction && (max > *curValue) )
    {
        (*curValue) += step;
    }
    else
    {
        (*curValue) -= step;
    }

    if ( (min == *curValue) || (max == *curValue) )
    {
        (*direction) ^= 1;
    }

    return (*curValue);
}


void ScaningEffectLabel::showEvent(QShowEvent *event)
{
    QLabel::showEvent( event );

    update();
    m_timer.start( 5 );

    if ( !m_circle.isNull() )
    {
        m_circle = m_circle.scaled( this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    }

    if ( !m_line.isNull() )
    {
        m_line = m_line.scaled( this->width(), m_line.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    }

    return;
}


void ScaningEffectLabel::hideEvent(QHideEvent *event)
{
    QLabel::hideEvent( event );
    m_timer.stop();

    return;
}


void ScaningEffectLabel::paintEvent( QPaintEvent *event )
{
    QLabel::paintEvent( event );
    QPainter painter( this );

    painter.setRenderHint( QPainter::Antialiasing );

    if ( !m_line.isNull() )
    {
        cycleSample( 1, this->height(), &m_y, &m_y_direction );
        cycleSample( 1, this->width(), &m_width, &m_width_direction, 2 );
        painter.drawPixmap( QRect((this->width() - m_width) / 2, m_y - m_line.height() / 2, m_width, m_line.height()), m_line );
    }

    if ( !m_circle.isNull() )
    {
        if ( 360.0 < m_roration )
        {
            m_roration = 0.0;
        }

        painter.translate( this->width() / 2, this->width() / 2 );
        painter.rotate( m_roration++ );
        painter.translate( -this->width() / 2, -this->width() / 2 );
        painter.drawPixmap( 0, 0, m_circle );
    }

    return;
}
