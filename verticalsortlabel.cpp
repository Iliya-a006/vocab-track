#include "verticalsortlabel.h"
#include <QPainter>
#include <QFont>
#include <QPolygon>

VerticalSortLabel::VerticalSortLabel(const QString& text, QWidget* parent)
    : QWidget(parent)
    , labelText(text)
    , textColor("#cfe3ee")
    , arrowColor("#5aa9d6")
    , backgroundColor("#16232f")
    , borderColor("#5aa9d6")
{
    setFixedWidth(44);
}

void VerticalSortLabel::setText(const QString& text)
{
    labelText = text;
    update();
}

QSize VerticalSortLabel::sizeHint() const
{
    return QSize(44, 300);
}

void VerticalSortLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // --- background card, matching the scrollArea's styling ---
    QRectF bgRect(1, 1, width() - 2, height() - 2);
    painter.setPen(QPen(borderColor, 2));
    painter.setBrush(backgroundColor);
    painter.drawRoundedRect(bgRect, 10, 10);

    const int bottomPadding = 14;
    const int arrowAreaHeight = 44;
    const int textTopPadding = 16;
    const int gapBeforeArrow = 14;
    const int cx = width() / 2;

    // --- downward arrow, pinned near the bottom of the widget ---
    const int lineBottom = height() - bottomPadding;
    const int lineTop = lineBottom - arrowAreaHeight;

    painter.setPen(QPen(arrowColor, 2));
    painter.drawLine(cx, lineTop, cx, lineBottom - 8);

    QPolygon arrowHead;
    arrowHead << QPoint(cx - 6, lineBottom - 10)
              << QPoint(cx + 6, lineBottom - 10)
              << QPoint(cx, lineBottom);
    painter.setPen(Qt::NoPen);
    painter.setBrush(arrowColor);
    painter.drawPolygon(arrowHead);

    // --- rotated text, filling the space above the arrow ---
    QFont f = painter.font();
    f.setBold(true);
    f.setPointSize(10);
    f.setLetterSpacing(QFont::AbsoluteSpacing, 1.2);
    painter.setFont(f);
    painter.setPen(textColor);

    painter.save();
    const int textPivotY = lineTop - gapBeforeArrow;
    painter.translate(cx, textPivotY);
    painter.rotate(-90);
    int textAreaLength = textPivotY - textTopPadding;
    QRect textRect(0, -width() / 2, textAreaLength, width());
    painter.drawText(textRect, Qt::AlignCenter, labelText);
    painter.restore();
}