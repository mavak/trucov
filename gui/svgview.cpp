    #include "svgview.h"

    #include <QSvgRenderer>

    #include <QApplication>
    #include <QPainter>
    #include <QImage>
    #include <QWheelEvent>
    #include <QtDebug>

    SvgRasterView::SvgRasterView(const QString &file, QWidget *parent)
        : QWidget(parent)
    {
        doc = new QSvgRenderer(file, this);
        connect(doc, SIGNAL(repaintNeeded()),
                this, SLOT(poluteImage()));
    }

    void SvgRasterView::paintEvent(QPaintEvent *)
    {
        if (buffer.size() != size() ||
            m_dirty) {
            buffer = QImage(size(), QImage::Format_ARGB32_Premultiplied);
            QPainter p(&buffer);
            p.setViewport(0, 0, width(), height());
            p.eraseRect(0, 0, width(), height());
            doc->render(&p);
        }
        QPainter pt(this);
        pt.drawImage(0, 0, buffer);
    }

    QSize SvgRasterView::sizeHint() const
    {
        if (doc)
            return doc->defaultSize();
        return QWidget::sizeHint();
    }

    void SvgRasterView::poluteImage()
    {
        m_dirty = true;
        update();
    }

    void SvgRasterView::wheelEvent(QWheelEvent *e)
    {
        const double diff = 0.1;
        QSize size = doc->defaultSize();
        int width  = size.width();
        int height = size.height();
        if (e->delta() > 0) {
            width = int(this->width()+this->width()*diff);
            height = int(this->height()+this->height()*diff);
        } else {
            width  = int(this->width()-this->width()*diff);
            height = int(this->height()-this->height()*diff);
        }

        resize(width, height);
    }

    SvgNativeView::SvgNativeView(const QString &file, QWidget *parent)
        : QWidget(parent)
    {
        doc = new QSvgRenderer(file, this);
        connect(doc, SIGNAL(repaintNeeded()),
                this, SLOT(update()));
    }

    void SvgNativeView::paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        p.setViewport(0, 0, width(), height());
        doc->render(&p);
    }

    QSize SvgNativeView::sizeHint() const
    {
        if (doc)
            return doc->defaultSize();
        return QWidget::sizeHint();
    }

    void SvgNativeView::wheelEvent(QWheelEvent *e)
    {
        const double diff = 0.1;
        QSize size = doc->defaultSize();
        int width  = size.width();
        int height = size.height();
        if (e->delta() > 0) {
            width = int(this->width()+this->width()*diff);
            height = int(this->height()+this->height()*diff);
        } else {
            width  = int(this->width()-this->width()*diff);
            height = int(this->height()-this->height()*diff);
        }
        resize(width, height);
    }

    #ifndef QT_NO_OPENGL
    SvgGLView::SvgGLView(const QString &file, QWidget *parent)
        : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
    {
        doc = new QSvgRenderer(file, this);
        connect(doc, SIGNAL(repaintNeeded()),
                this, SLOT(update()));
    }

    void SvgGLView::paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        doc->render(&p);
    }

    QSize SvgGLView::sizeHint() const
    {
        if (doc)
            return doc->defaultSize();
        return QGLWidget::sizeHint();
    }

    void SvgGLView::wheelEvent(QWheelEvent *e)
    {
        const double diff = 0.1;
        QSize size = doc->defaultSize();
        int width  = size.width();
        int height = size.height();
        if (e->delta() > 0) {
            width = int(this->width()+this->width()*diff);
            height = int(this->height()+this->height()*diff);
        } else {
            width  = int(this->width()-this->width()*diff);
            height = int(this->height()-this->height()*diff);
        }
        resize(width, height);
    }
    #endif

