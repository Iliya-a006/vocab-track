#ifndef VERTICALSORTLABEL_H
#define VERTICALSORTLABEL_H

#include <QWidget>
#include <QString>
#include <QColor>

// Narrow vertical strip: rotated text (read bottom-to-top) with a small
// downward arrow drawn beneath it. Used to indicate "this list is sorted
// top-to-bottom in such-and-such order" next to a scroll area.
class VerticalSortLabel : public QWidget
{
    Q_OBJECT
public:
    explicit VerticalSortLabel(const QString& text, QWidget* parent = nullptr);

    void setText(const QString& text);

protected:
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;

private:
    QString labelText;
    QColor textColor;
    QColor arrowColor;
    QColor backgroundColor;
    QColor borderColor;
};

#endif // VERTICALSORTLABEL_H