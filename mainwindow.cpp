#include "mainwindow.h"
#include "piecesmodel.h"
#include "puzzlewidget.h"
#include "custombutton.h"
#include <stdlib.h>
#include <QtWidgets>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupWidgets();
    model = new PiecesModel(puzzleWidget->pieceSize1(), this);
    piecesList->setModel(model);
    setWindowTitle(tr("Puzzle It"));
    setWindowState(Qt::WindowFullScreen);
    QPixmap background(":/images/background1.jpg");
    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    centralWidget()->setPalette(palette);
    centralWidget()->setAutoFillBackground(true);
}

void MainWindow::openImage()
{
    const QString directory = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).value(0, QDir::homePath());
    QFileDialog dialog(this, tr("Выбор изображения"), directory);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList mimeTypeFilters;
    for (const QByteArray &mimeTypeName : QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (dialog.exec() == QDialog::Accepted)
        loadImage(dialog.selectedFiles().constFirst());
}

void MainWindow::loadImage(const QString &fileName)
{
    QPixmap newImage;
    if (!newImage.load(fileName)) {
        QMessageBox::warning(this, tr("Выбор изображения"), tr("Изображение невозможно загрузить."),
                             QMessageBox::Close);
        return;
    }
    puzzleImage = newImage;
    setupPuzzle1();
    setupPuzzle2();
    setupPuzzle3();
}

class CustomDialog : public QDialog {
public:
    CustomDialog(const QString &imagePath, QWidget *parent = nullptr) : QDialog(parent) {
      setStyleSheet("CustomDialog { background-repeat: no-repeat; background-position: center; background-size: cover; }");
      QLabel *label = new QLabel(this);
      QPixmap iconPixmap(":/images/icon.png"); // Replace with the path to your icon
      label->setPixmap(iconPixmap);

        QPixmap pixmap(imagePath);
                pixmap = pixmap.scaled(QSize(830,620), Qt::KeepAspectRatio);
                label->setPixmap(pixmap);
        QPushButton *okButton = new QPushButton(tr("OK"), this);
        connect(okButton, &QPushButton::clicked, this, &CustomDialog::accept);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(okButton);
        setFixedSize(800, 600);
        }
};

void MainWindow::setCompleted1()
{
    CustomDialog dialog (":/images/examplecomplete1.jpg");
    int ret = dialog.exec();

    if (ret == QDialog::Accepted) {
        setupPuzzle1();
    }
    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted1, Qt::QueuedConnection);
}

void MainWindow::setCompleted2()
{
    CustomDialog dialog (":/images/examplecomplete2.jpg");
    int ret = dialog.exec();

    if (ret == QDialog::Accepted) {
        setupPuzzle2();
    }
}
void MainWindow::setCompleted3()
{
    CustomDialog dialog (":/images/examplecomplete3.jpg");
    int ret = dialog.exec();

    if (ret == QDialog::Accepted) {
        setupPuzzle3();
}
    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3, Qt::QueuedConnection);
}

void MainWindow::setCompleted4()
{
        QMessageBox::information(this, tr("Пазл собран"), tr("Ура! Вы собрали пазл!\n"
                                                             "Нажмите OK чтобы начать заново."), QMessageBox::Ok);
        setupPuzzle1();
}

void MainWindow::setupPuzzle1()
{
    int size = qMin(puzzleImage.width(), puzzleImage.height());
    puzzleImage = puzzleImage.copy((puzzleImage.width() - size) / 2,
        (puzzleImage.height() - size) / 2, size, size).scaled(puzzleWidget->imageSize(),
            puzzleWidget->imageSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    model->addPieces(puzzleImage);
    puzzleWidget->clear();
}

void MainWindow::setupPuzzle2()
{
    int size = qMin(puzzleImage.width(), puzzleImage.height());
       puzzleImage = puzzleImage.copy((puzzleImage.width() - size) / 2,
           (puzzleImage.height() - size) / 2, size, size).scaled(puzzleWidget->imageSize(),
               puzzleWidget->imageSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
       model->addPieces(puzzleImage);
       puzzleWidget->clear();
}

void MainWindow::setupPuzzle3()
{
    int size = qMin(puzzleImage.width(), puzzleImage.height());
    puzzleImage = puzzleImage.copy((puzzleImage.width() - size) / 2,
        (puzzleImage.height() - size) / 2, size, size).scaled(puzzleWidget->imageSize(),
            puzzleWidget->imageSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    model->addPieces(puzzleImage);
    puzzleWidget->clear();
}

void MainWindow::setupWidgets()
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(20, 50, 50, 70);
    puzzleWidget = new PuzzleWidget(800);
    piecesList = new QListView;
    piecesList->setDragEnabled(true);
    piecesList->setViewMode(QListView::IconMode);
    piecesList->setIconSize(QSize(puzzleWidget->pieceSize1() - 20, puzzleWidget->pieceSize1() - 20));
    piecesList->setMovement(QListView::Snap);
    piecesList->setAcceptDrops(true);
    piecesList->setDropIndicatorShown(true);
    piecesList->setDragDropMode(QListView::DragDrop);
    piecesList->setDefaultDropAction(Qt::MoveAction);
    piecesList->hide();
    piecesList->setFixedWidth(350);  // Set the fixed width for piecesList
    piecesList->setFixedHeight(800);
    puzzleWidget->hide();

    layout->addWidget(puzzleWidget);
    layout->addSpacing(30);
    layout->addWidget(piecesList);

    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addSpacing(430);
    QPushButton *playButton = new QPushButton(tr(" "));
    QPushButton *helpButton = new QPushButton(tr(" "));
    QPushButton *outButton = new QPushButton(tr(" "));

    playButton->setFixedHeight(112);
    playButton->setFixedWidth(645);
    helpButton->setFixedHeight(112);
    helpButton->setFixedWidth(645);
    outButton->setFixedHeight(112);
    outButton->setFixedWidth(500);

    playButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.0);}");
    helpButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.0);}");
    outButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.0);}");

    connect(playButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(helpButton, &QPushButton::clicked, this, &MainWindow::showHelp);
    connect(outButton, &QPushButton::clicked, this, &MainWindow::close);

    buttonsLayout->addWidget(playButton);
    buttonsLayout->addWidget(helpButton);
    buttonsLayout->addWidget(outButton);
    buttonsLayout->addSpacing(50);

    playButton->setObjectName("playButton");
    helpButton->setObjectName("helpButton");
    outButton->setObjectName("outButton");

    layout->addLayout(buttonsLayout);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    QPixmap icon(":/images/icon.png");
    setWindowIcon(QIcon(icon));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        setupWidgets();
        model = new PiecesModel(puzzleWidget->pieceSize1(), this);
        piecesList->setModel(model);
        setWindowTitle(tr("Puzzle It"));
        setWindowState(Qt::WindowFullScreen);
        QPixmap background(":/images/background1.jpg");
        background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Background, background);
        centralWidget()->setPalette(palette);
        centralWidget()->setAutoFillBackground(true);
    }
}

void MainWindow::startGame()
{

        QPixmap background(":/images/background3.jpg");
        background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Background, background);
        centralWidget()->setPalette(palette);
        centralWidget()->setAutoFillBackground(true);

        puzzleWidget->show();
        piecesList->show();
        setupPuzzle1();

        QPushButton* playcustomButton = new QPushButton(tr(" "));
        QPushButton* level1Button = new QPushButton(tr(" "));
        QPushButton* level2Button = new QPushButton(tr(" "));
        QPushButton* level3Button = new QPushButton(tr(" "));

        playcustomButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.2);}");
        level1Button->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.2);}");
        level2Button->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.2);}");
        level3Button->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.2);}");

        connect(playcustomButton, &QPushButton::clicked, this, &MainWindow::startcustomGame);
        connect(level1Button, &QPushButton::clicked, this, &MainWindow::startlevel1Game);
        connect(level2Button, &QPushButton::clicked, this, &MainWindow::startlevel2Game);
        connect(level3Button, &QPushButton::clicked, this, &MainWindow::startlevel3Game);

        level1Button->setFixedHeight(112);
        level1Button->setFixedWidth(345);
        level2Button->setFixedHeight(112);
        level2Button->setFixedWidth(345);
        level3Button->setFixedHeight(112);
        level3Button->setFixedWidth(345);
        playcustomButton->setFixedHeight(112);
        playcustomButton->setFixedWidth(345);

        QVBoxLayout* buttonsLayout = new QVBoxLayout;
           buttonsLayout->addSpacing(13);
           QVBoxLayout* level1Layout = new QVBoxLayout;
           level1Layout->addWidget(level1Button);
           level1Layout->setContentsMargins(0, 9, 16, 10);
           buttonsLayout->addLayout(level1Layout);
           buttonsLayout->addSpacing(120);

           QVBoxLayout* level2Layout = new QVBoxLayout;
           level2Layout->addWidget(level2Button);
           level2Layout->setContentsMargins(0, 0, 0, 0);
           buttonsLayout->addLayout(level2Layout);
           buttonsLayout->addSpacing(120);

           QVBoxLayout* level3Layout = new QVBoxLayout;
           level3Layout->addWidget(level3Button);
           level3Layout->setContentsMargins(0, 0, 0, 0);
           buttonsLayout->addLayout(level3Layout);
           buttonsLayout->addSpacing(120);

           QVBoxLayout* playcustomLayout = new QVBoxLayout;
           playcustomLayout->addWidget(playcustomButton);
           playcustomLayout->setContentsMargins(0, 0, 0, 0);
           buttonsLayout->addLayout(playcustomLayout);
           buttonsLayout->setAlignment(Qt::AlignCenter);

        QHBoxLayout* mainLayout = qobject_cast<QHBoxLayout*>(centralWidget()->layout());
        mainLayout->insertLayout(0, buttonsLayout);

        QPushButton *playButton = centralWidget()->findChild<QPushButton*>("playButton");
        if (playButton)
            playButton->hide();
        QPushButton *helpButton = centralWidget()->findChild<QPushButton*>("helpButton");
        if (helpButton)
            helpButton->hide();
        QPushButton *outButton = centralWidget()->findChild<QPushButton*>("outButton");
        if (outButton)
            outButton->hide();

        if (level1Started){
            disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted4);
            disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3);
            disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted2);
            connect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted1, Qt::QueuedConnection);
            level1Started=true;
        }
}

void MainWindow::startlevel1Game()
{
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted4);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted2);
        level1Started=true;
    loadImage(QStringLiteral(":/images/example.jpg"));
    setupPuzzle1();
}

void MainWindow::startlevel2Game()
{
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted4);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted1);
    level2Started=true;
    loadImage(QStringLiteral(":/images/example2.jpg"));
    setupPuzzle2();
    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted2, Qt::QueuedConnection);
}

void MainWindow::startlevel3Game()
{
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted4);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted2);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted1);

    level3Started=true;
    loadImage(QStringLiteral(":/images/example3.jpg"));
    setupPuzzle3();
    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3, Qt::QueuedConnection);
    }

void MainWindow::startcustomGame()
{
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted3);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted2);
    disconnect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted1);

    level4Started=true;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QString(), tr("Изображения (*.png *.jpg *.jpeg)"));
    if (!fileName.isEmpty())
    {
        loadImage(fileName);
    }
    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted, this, &MainWindow::setCompleted4, Qt::QueuedConnection);
}

void MainWindow::showHelp()
{
    QPixmap background(":/images/backgroundhelp1.jpg");
    background = background.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    centralWidget()->setPalette(palette);
    centralWidget()->setAutoFillBackground(true);

    QPushButton* buttonHelp2 = new QPushButton(" ");
    buttonHelp2->setObjectName("buttonHelp2");
    buttonHelp2->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0.0);}");
    connect(buttonHelp2, SIGNAL(clicked()), this, SLOT(showHelp2()));
    buttonHelp2->setFixedHeight(112);
    buttonHelp2->setFixedWidth(1050);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(820);
    layout->addWidget(buttonHelp2);

    centralWidget()->setLayout(layout);
    QHBoxLayout* mainLayout = qobject_cast<QHBoxLayout*>(centralWidget()->layout());
        mainLayout->insertLayout(0, layout);

    QPushButton *playButton = centralWidget()->findChild<QPushButton*>("playButton");
    if (playButton)
        playButton->hide();
    QPushButton *helpButton = centralWidget()->findChild<QPushButton*>("helpButton");
    if (helpButton)
        helpButton->hide();
    QPushButton *outButton = centralWidget()->findChild<QPushButton*>("outButton");
    if (outButton)
        outButton->hide();
}

void MainWindow::showHelp2()
{
    QPixmap background(":/images/backgroundhelp2.jpg");
    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    centralWidget()->setPalette(palette);
    centralWidget()->setAutoFillBackground(true);
}
