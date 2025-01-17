#include "puzzlewidget.h"
#include <QtWidgets>

PuzzleWidget::PuzzleWidget(int imageSize, QWidget *parent) : QWidget(parent), m_ImageSize(imageSize)
{
    setAcceptDrops(true);
    setMinimumSize(m_ImageSize, m_ImageSize);
    setMaximumSize(m_ImageSize, m_ImageSize);
}

void PuzzleWidget::clear()
{
    pieces.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void PuzzleWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void PuzzleWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void PuzzleWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {

        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
    update(updateRect);
}

void PuzzleWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {

        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        Piece piece;
        piece.rect = targetSquare(event->pos());
        dataStream >> piece.pixmap >> piece.location;
        pieces.append(piece);
        highlightedRect = QRect();
        update(piece.rect);

        event->setDropAction(Qt::MoveAction);
        event->accept();

        if (piece.location == piece.rect.topLeft() / pieceSize1()) {
            inPlace++;
            if (inPlace == 25)
                emit puzzleCompleted();
        }
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

int PuzzleWidget::findPiece(const QRect &pieceRect) const
{
    for (int i = 0, size = pieces.size(); i < size; ++i) {
        if (pieces.at(i).rect == pieceRect)
            return i;
    }
    return -1;
}

void PuzzleWidget::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);
    if (found == -1)
        return;

    Piece piece = pieces.takeAt(found);
    if (piece.location == square.topLeft() / pieceSize1())
        inPlace--;

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << piece.pixmap << piece.location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(piece.pixmap);

    if (drag->start(Qt::MoveAction) == Qt::IgnoreAction) {
        pieces.insert(found, piece);
        update(targetSquare(event->pos()));

        if (piece.location == QPoint(square.x() / pieceSize1(), square.y() / pieceSize1()))
            inPlace++;
    }
}

void PuzzleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    static QPixmap backgroundImage(":/images/malbert.jpg");
    painter.drawPixmap(rect(), backgroundImage);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }
    for (const Piece &piece : pieces)
        painter.drawPixmap(piece.rect, piece.pixmap);
}

const QRect PuzzleWidget::targetSquare(const QPoint &position) const
{
    return QRect(position / pieceSize1() * pieceSize1(),
                 QSize(pieceSize1(), pieceSize1()));
}

int PuzzleWidget::pieceSize1() const
{
    return m_ImageSize / 5;
}

int PuzzleWidget::imageSize() const
{
    return m_ImageSize;
}
