#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

class PuzzleWidget;
class PiecesModel;
QT_BEGIN_NAMESPACE
class QListView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
      bool level1Started;
      bool level2Started=false;
      bool level3Started=false;
      bool level4Started=false;

public slots:
    void openImage();
    void loadImage(const QString &path);
    void setupPuzzle1();
    void setupPuzzle2();
    void setupPuzzle3();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void setCompleted1();
    void setCompleted2();
    void setCompleted3();
    void setCompleted4();
    void showHelp();
    void startGame();
    void startcustomGame();
    void startlevel1Game();
    void startlevel2Game();
    void startlevel3Game();
    void showHelp2();

private:
    void setupWidgets();
    void showPuzzleWidget();

    QPushButton* helpButton;
    QPushButton* playButton;
    QPushButton* outButton;
    QPushButton* playcustomButton;
    QPushButton* playlevel1Button;
    QPushButton* playlevel2Button;
    QPushButton* playlevel3Button;

    QPushButton* buttonExit;
    QVBoxLayout* buttonsLayout;
    QVBoxLayout* layout;

    QSize initialWindowSize;
    QPixmap puzzleImage;
    QListView *piecesList;
    PuzzleWidget *puzzleWidget;
    PiecesModel *model;
};

#endif // MAINWINDOW_H
